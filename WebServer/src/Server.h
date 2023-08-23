#ifndef SERVER_H_
#define SERVER_H_

#include<map>
#include "Connection.h"

class EventLoop;
class ThreadPool;
class Acceptor;
class Socket;
class Connecter;

class Server
{
public:
    Server(EventLoop*);

    ~Server(){};

    void Read(Socket*);

    void Acceptconn(Socket*);

    void loop();
private:
    Acceptor*     acceptor;
    EventLoop*    main_loop;
    std::map<int,Connceter*> Connceters;
};




#endif