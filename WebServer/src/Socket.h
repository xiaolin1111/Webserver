#ifndef SOCKET_H_
#define SOCKET_H_


#define ListenqueueLen  100

class Sockaddr;

class Socket
{
public:
    Socket();

    ~Socket();

    Socket(int fd_);

    void Bind(Sockaddr*);    

    void Listen();

    int Accept(Sockaddr* clientaddr);

    void Connection(const char* ip,int port);

    int getFd(){ return fd; }

    void setnonblocking();    //将套接字设置为非阻塞

private:
    int fd;
};




#endif


