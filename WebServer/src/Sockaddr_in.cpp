#include "Sockaddr_in.h"
#include <string.h>
#include <arpa/inet.h>

Sockaddr::Sockaddr() : addr_len(sizeof(addr)){
    bzero(&addr, sizeof(addr));
}
Sockaddr::Sockaddr(const char* ip, uint16_t port) : addr_len(sizeof(addr)){
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr_len = sizeof(addr);
}

Sockaddr::~Sockaddr(){
}

void Sockaddr::setAddr(sockaddr_in _addr, socklen_t _addr_len){
    addr = _addr;
    addr_len = _addr_len;
}

sockaddr_in Sockaddr::getAddr(){
    return addr;
}
socklen_t Sockaddr::getAddr_len(){
    return addr_len;
}