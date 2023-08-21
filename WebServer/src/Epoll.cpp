#include "Epoll.h"
#include <unistd.h>

#include "util.h"
#include "Channel.h"
#include <string.h>

Epoll::Epoll()
{
    evs = new epoll_event[MAXEVENTS];
    ep = epoll_create1(0);
    check(ep == -1,"epoll create error");
}

Epoll::~Epoll()
{
    if(ep != -1)
    {
        close(ep);
        ep = -1;
    }
    delete [] evs;
}

void Epoll::add(Channel* ch)
{
    struct epoll_event ev_;
    bzero(&ev_,sizeof(ev_));
    ev_.data.ptr = ch;
    ev_.events = ch->getev();
    check(epoll_ctl(ep,EPOLL_CTL_ADD,ch->getFd(),&ev_) == -1,"epoll add error");
}

void Epoll::mod(Channel* ch)
{
    struct epoll_event ev_;
    bzero(&ev_,sizeof(ev_));
    ev_.data.ptr = ch;
    ev_.events = ch->getev();
    check(epoll_ctl(ep,EPOLL_CTL_MOD,ch->getFd(),&ev_),"epoll mod error");
}

void Epoll::del(Channel* ch)
{
    struct epoll_event ev_;
    bzero(&ev_,sizeof(ev_));
    ev_.data.fd = ch->getFd();
    check(epoll_ctl(ep,EPOLL_CTL_DEL,ch->getFd(),&ev_),"epoll del error");
}

std::vector<Channel> Epoll::poll()
{
    std::vector<Channel> vec;
    int nfds = epoll_wait(ep,evs,MAXEVENTS,TIMEOUT);
    for(int i = 0;i < nfds; ++i)
    {
        Channel* tmp = (Channel*)evs[i].data.ptr;
        vec.push_back(*tmp);
    }
    return vec;
}

void Epoll::upChannel(Channel *channel)
{
    int fd = channel->getFd();
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = channel;
    ev.events = channel->getev();
    if(!channel->getInpoll())
    {
        check(epoll_ctl(channel->getEP(), EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add error");
        channel->setInpoll(true);
    } else
    {
        check(epoll_ctl(channel->getEP(), EPOLL_CTL_MOD, fd, &ev) == -1, "epoll modify error");
        
    }
}