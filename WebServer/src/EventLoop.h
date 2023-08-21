#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

class ThreadPool;
class Channel;
class Epoll;

class EventLoop
{
public:
    EventLoop(Epoll* ep_,ThreadPool* threadpool_);

    void upChannel(Channel*);

    void loop();

    int getEP();

private:
    Epoll*  EP;
    ThreadPool* threadpool;
};


#endif