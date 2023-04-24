#include "Epoll.h"
#include "InetAddress.h"
#include "Socket.h"
#include "util.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#define MAX_EVENTS 1024
#define READ_BUFFER 1024

int main() {
  Socket *serv_sock = new Socket();
  InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);
  serv_sock->bind(serv_addr);
  serv_sock->listen();
  Epoll *ep = new Epoll();
  serv_sock->setnonblocking();
  ep->addFd(serv_sock->getFd(), EVFILT_READ | EVFILT_) return 0;
}