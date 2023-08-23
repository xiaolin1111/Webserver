#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <functional>

class Socket;
class Epoll;
class ThreadPool;
class EventLoop;

class Channel
{ 
public:
    Channel(){}
    Channel(int fd_,EventLoop* loop);

    ~Channel(){}

    void setrev(int op);

    void setev(int op);

    int getev();

    int getrev();

    int getFd();

    int getEP();

    void handleEvent();

    void enableReading();

    void setCallback(std::function<void()> cb_);

    void setInpoll(bool);

    bool getInpoll();
    
    std::function<void()> callback;
protected:
    int     ev;
    int     rev;
    bool    Inpoll;
    int     fd;
    EventLoop*  loop;
};




#endif