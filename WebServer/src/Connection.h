#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Socket.h"
#include "Channel.h"
#include "Buf.h"

class Socket;
class Channel;
class Buf;


class Connceter
{
public:
    Connceter(Socket*,Channel*);

    ~Connceter();

    Socket* getFd();

    Channel* getChannel();

    Buf* getBuf();
private:
    Socket*    fd;
    Channel*   ch;
    Buf*       buf;

};






#endif