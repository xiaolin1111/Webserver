#include "Acceptor.h"

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "functional"
#include "Sockaddr_in.h"

Acceptor::Acceptor(EventLoop* l):m_sock_fd(nullptr),Loop(l),acceptchannel(nullptr)
{
    m_sock_fd = new Socket();
    Sockaddr *addr = new Sockaddr("127.0.0.1", 8888);
    m_sock_fd->Bind(addr);
    m_sock_fd->Listen();
    m_sock_fd->setnonblocking();


    acceptchannel = new Channel(m_sock_fd->getFd(),Loop);

    acceptchannel->setInpoll(false);
    auto cb_ = std::bind(&Acceptor::acceptconn,this);
    acceptchannel->setCallback(cb_);
    acceptchannel->enableReading();
    delete addr;
}


Acceptor::~Acceptor()
{
    delete m_sock_fd;
    delete acceptchannel;
    delete Loop;
}

void Acceptor::setfunc(std::function<void(Socket*)> cb_)
{
    Callback = cb_;
}


void Acceptor::acceptconn()
{
    Callback(m_sock_fd);
}