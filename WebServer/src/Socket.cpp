#include "Socket.h"

#include "string.h"
#include <sys/socket.h>       //for socket
#include <sys/types.h>
#include <netinet/in.h>       //for sockaddr_in
#include <arpa/inet.h>        //inet_addr
#include <fcntl.h>
#include "Sockaddr_in.h"
#include "util.h"
#include "unistd.h"

Socket::Socket()
{
    fd = socket(AF_INET,SOCK_STREAM,0);
    check(fd == -1,"socket create error");
}

Socket::Socket(int fd_):fd(fd_){}

Socket::~Socket()
{
    if(fd != -1)
    {
        close(fd);
    }
}

void Socket::Bind(Sockaddr* _addr)
{
    
     struct sockaddr_in addr = _addr->getAddr();
    socklen_t addr_len = _addr->getAddr_len();
    check(bind(fd,(struct sockaddr*)&addr,addr_len) == -1,"socket bind error");
    _addr->setInetAddr(addr, addr_len);
}

void Socket::Listen()
{
    check(listen(fd,ListenqueueLen) == -1,"listen scoket error");
}

int Socket::Accept(Sockaddr* clientaddr)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    bzero(&addr, sizeof(addr));
    int clnt_sockfd = ::accept(fd, (sockaddr*)&addr, &addr_len);
    check(clnt_sockfd == -1, "socket accept error");
    clientaddr->setInetAddr(addr, addr_len);
    return clnt_sockfd;
}

void Socket::Connection(const char* ip,int port)
{
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);
    if(connect(fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1,"connect error");
}

void Socket::setnonblocking()
{
    int old_option = fcntl(fd,F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
}