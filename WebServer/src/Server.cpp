#include "Server.h"

#include <unistd.h>
#include <functional>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include "Acceptor.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Sockaddr_in.h"
#include "sys/epoll.h"

Server::Server(EventLoop* l):acceptor(nullptr),main_loop(l)
{
    acceptor = new Acceptor(l);
    std::function<void(Socket*)> cb = std::bind(&Server::Acceptconn, this, std::placeholders::_1);
    acceptor->setfunc(cb);
}

void Server::loop()
{
    main_loop->loop();
}

void Server::Read(Socket* fd)
{
    char buf[1024];
    int sockfd = fd->getFd();
    while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd , buf, sizeof(buf));
        if(bytes_read > 0){
            printf("message from client fd %d: %s\n", sockfd, buf);
            write(sockfd, buf, sizeof(buf));
        } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if(bytes_read == 0){  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            break;
        }
    }
}


//接受连接函数,将新连接加入epoll树中
void Server::Acceptconn(Socket* socketfd)
{
    Sockaddr* cliaddr = new Sockaddr();
    int i = socketfd->Accept(cliaddr);

    Socket* client_fd = new Socket(i); 
    
    client_fd->setnonblocking();             //将套接字设置为非阻塞

    Channel* ch = new Channel(client_fd->getFd(),main_loop); 

    std::function<void()> cb = std::bind(&Server::Read,this,client_fd);  
    ch->setCallback(cb);
    ch->enableReading();
    // ch.setevent(EPOLLIN|EPOLLET);            
}
