#ifndef EPOLL_H_
#define EPOLL_H_

#include "sys/epoll.h"
#include <vector>


#define MAXEVENTS 1000
#define TIMEOUT   1


class Channel;

class Epoll
{
public:
    Epoll();
    ~Epoll();

    void add(Channel*);

    void mod(Channel*);

    void del(Channel*);

    std::vector<Channel*> poll();

    void upChannel(Channel*);

    int getEpoll(){ return ep; }

private:
    int  ep;
    epoll_event* evs;
};


#endif