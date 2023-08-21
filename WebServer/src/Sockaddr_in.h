#ifndef SOCKADDR_IN_H_
#define SOCKADDR_IN_H_

#include <netinet/in.h>
#include <arpa/inet.h>


struct Sockaddr
{
private:
    struct sockaddr_in addr;
    socklen_t addr_len;     
public:
    Sockaddr();
    Sockaddr(const char* ip, uint16_t port);
    ~Sockaddr();
    void setAddr(sockaddr_in _addr, socklen_t _addr_len);
    sockaddr_in getAddr();
    socklen_t getAddr_len();
};

#endif 