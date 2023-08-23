#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <list>
#include "Channel.h"


class Sem
{
public:
    Sem();

    ~Sem();
    
    bool wait();

    bool post();

private:
    sem_t m_sem;
};

class Lock
{
public:
    Lock();

    ~Lock();

    bool lock();

    bool unlock();

private:
    pthread_mutex_t m_mutex;
};

class Channel;

class ThreadPool
{
public:
    ThreadPool(int _thread_number = 2,int max_requests = 1000);
    ~ThreadPool();

    bool append(Channel* ch);
private:
    static void* work(void*);

    void run();

private:
    int  thread_number;                         //线程池中的线程数量
    int  max_requests;                          //请求队列中允许的最大请求数
    pthread_t*               threads;           //线程数组
    std::list<Channel*>  request_queue;          //请求队列
    Lock m_lock;                                //互斥锁
    Sem  sem;                                   //信号量    
    bool stop;                                  //结束线程
};

#endif



































// class ThreadPool
// {
//     friend class Acceptor;

// public:
//     ThreadPool();
//     ThreadPool(int sum);

//     static void* work(void* args);

// private:
//     int thread_number = 100;                             //线程池内线程最大数量                  
//     static std::queue<pthread_t> threads;                //线程池
//     static std::queue<Channel>   request_queue;          //请求队列
//     pthread_mutex_t              mutex;                  
//     pthread_cond_t               cond;
// };


// ThreadPool::ThreadPool()
// {
//     mutex = PTHREAD_MUTEX_INITIALIZER;

//     pthread_mutex_lock(&mutex);
//     for(int i = 0;i < thread_number; ++i)
//     {
//         pthread_t n;
//         pthread_create(&n,NULL,work,NULL);
//         threads.push(n);
//     }
//     pthread_mutex_unlock(&mutex);
// }

// void* ThreadPool::work(void* args)
// {
//     pthread_mutex_lock(&mutex);
    
//     Channel ch = request_queue.front();
//     request_queue.pop();
    
//     pthread_mutex_unlock(&mutex);
    
//     ch.cb();
// }


// ThreadPool::ThreadPool(int sum):thread_number(sum)
// {
//     mutex = PTHREAD_MUTEX_INITIALIZER;

//     pthread_mutex_lock(&mutex);
//     for(int i = 0;i < thread_number; ++i)
//     {
//         pthread_t n;
//         pthread_create(&n,NULL,work,NULL);
//         threads.push(n);
//     }
//     pthread_mutex_unlock(&mutex);
// }


















