#include "Channel.h"
#include "sys/epoll.h"
#include "EventLoop.h"

Channel::Channel(int fd_,EventLoop* loop_):fd(fd_),loop(loop_),ev(0),rev(0),Inpoll(false)
{
}

void Channel::setev(int op)
{
    ev = op;
}

void Channel::setrev(int op)
{
    rev = op;
}

int Channel::getev()
{
    return ev;
}

int Channel::getrev()
{
    return rev;
}

int Channel::getFd()
{
    return fd;
}

void Channel::handleEvent(){
    callback();
}

void Channel::enableReading(){
    ev |= EPOLLIN | EPOLLET;
    loop->upChannel(this);
}

void Channel::setCallback(std::function<void()> cb_)
{
    callback = cb_;
}

void Channel::setInpoll(bool b)
{
    Inpoll = b;
}

bool Channel::getInpoll()
{
    return Inpoll;
}

int Channel::getEP()
{
    return loop->getEP();
}