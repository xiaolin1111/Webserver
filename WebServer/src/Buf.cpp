#include "Buf.h"


#include <string.h>
#include "Socket.h"

Buf::Buf():buf(nullptr)
{   
    buf = new char[BUFSIZE];
}

Buf::~Buf()
{
    delete [] buf;
}

ssize_t Buf::Readfd(Socket* fd_)
{
    bzero(buf, sizeof(buf));
    return read(fd_->getFd() , buf, 1024);
}


ssize_t Buf::Writefd(Socket* fd_)
{
    return write(fd_->getFd(), buf, 1024);
}
