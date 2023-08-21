#include "src/Server.h"
#include "src/ThreadPool.h"
#include "src/Epoll.h"
#include "src/EventLoop.h"
#include "src/Acceptor.h"

int main()
{
    ThreadPool* t = new ThreadPool();

    Epoll* ep = new Epoll();

    EventLoop* l = new EventLoop(ep,t);

    Server* ser = new Server(l);

    ser->loop();
}