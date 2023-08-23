#include "ThreadPool.h"
#include "util.h"

Sem::Sem()
{
    check(sem_init(&m_sem,0,0) != 0,"sem init error"); 
}

Sem::~Sem()
{
    sem_destroy(&m_sem);
}

bool Sem::wait()
{
    return sem_wait(&m_sem) == 0;
}

bool Sem::post()
{
    return sem_post(&m_sem) == 0;
}

Lock::Lock()
{
    check(pthread_mutex_init(&m_mutex,NULL) != 0,"Lock init error");
}

Lock::~Lock()
{
    pthread_mutex_destroy(&m_mutex);
}

bool Lock::lock()
{
    return pthread_mutex_lock(&m_mutex) == 0;
}

bool Lock::unlock()
{
    return pthread_mutex_unlock(&m_mutex) == 0;
}


ThreadPool::ThreadPool(int _thread_number,int _max_requests)
                    :thread_number(_thread_number),max_requests(_max_requests),stop(false),threads(nullptr)
{
    if(thread_number <= 0 || max_requests <= 0) check(true,"ThreadPool init error");

    threads = new pthread_t[thread_number];

    for(int i = 0; i < thread_number; ++i)
    {
        check(pthread_create(threads+i,NULL,work,this) != 0,"pthread create error");

        check(pthread_detach(threads[i]) != 0,"pthread detach error");
    }
}

ThreadPool::~ThreadPool()
{
    delete [] threads;
}

bool ThreadPool::append(Channel* ch)
{
    m_lock.lock();
    if(request_queue.size() > max_requests)
    {
        m_lock.unlock();
        return false;
    }
    request_queue.push_back(ch);
    m_lock.unlock();
    sem.post();
    return true;
}   

void* ThreadPool::work(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    pool->run();
    return pool; 
}


void ThreadPool::run()
{
    while(!stop)
    {
        sem.wait();
        m_lock.lock();
        if(request_queue.empty())
        {
            m_lock.unlock();
            continue;
        }
        Channel* ch = request_queue.front();
        request_queue.pop_front();
        m_lock.unlock();
    
        ch->handleEvent();
    }
}