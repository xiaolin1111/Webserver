#include "EventLoop.h"
#include "Channel.h"
#include <vector>
#include "ThreadPool.h"
#include "Epoll.h"
void EventLoop::upChannel(Channel* ch)
{
    EP->upChannel(ch);

}



EventLoop::EventLoop(Epoll* ep_,ThreadPool* threadpool_):EP(ep_),threadpool(threadpool_){}

void EventLoop::loop()
{
    while(true)
    {
        std::vector<Channel*> vec = EP->poll();
        for(int i = 0;i < vec.size();++i)
        {
            threadpool->append(vec[i]);
        }
    }
}

int EventLoop::getEP()
{
    return EP->getEpoll();
}
