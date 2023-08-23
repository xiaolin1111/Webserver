#ifndef BUF_H_
#define BUF_H_

#include <unistd.h>

#define BUFSIZE 1024

class Socket;

//缓冲区
class Buf
{
public:
    Buf();
    ~Buf();

    ssize_t Readfd(Socket* fd_);

    ssize_t Writefd(Socket* fd_);

private:
    char* buf;
};







#endif