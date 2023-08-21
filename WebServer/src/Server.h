#ifndef SERVER_H_
#define SERVER_H_



class EventLoop;
class ThreadPool;
class Acceptor;
class Socket;


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
};




#endif