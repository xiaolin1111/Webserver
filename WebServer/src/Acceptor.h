#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include <functional>

class AcceptorChannel;
class ThreadPool;
class Socket;
class Epoll;
class Channel;
class EventLoop;

class Acceptor
{
    friend class Server;
public:
    Acceptor(){}
    Acceptor(EventLoop*);

    ~Acceptor();

    void setfunc(std::function<void(Socket*)>);

    void acceptconn();

    std::function<void(Socket*)> Callback;
private:
    Socket*        m_sock_fd;
    EventLoop*     Loop;
    Channel*       acceptchannel;
};



#endif