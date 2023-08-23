#include "Connection.h"

#include "Socket.h"
#include "Channel.h"
#include "Buf.h"


Connceter::Connceter(Socket* fd_,Channel* ch_):fd(fd_),ch(ch_),buf(nullptr)
{
    buf = new Buf();
}


Connceter::~Connceter()
{
    delete fd;
    delete ch;
    delete buf;
}

Socket* Connceter::getFd()
{
    return fd;
}

Channel* Connceter::getChannel()
{
    return ch;
}

Buf* Connceter::getBuf()
{
    return buf;
}