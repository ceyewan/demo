#include "Epoll.h"
#include "util.h"
#include <cstddef>
#include <string.h>
#include <unistd.h>

#define MAX_EVENTS 1000

Epoll::Epoll() : epfd(-1), events(nullptr) {
  epfd = kqueue();
  errif(epfd == -1, "epoll create error");
  events = new struct kevent[MAX_EVENTS];
  bzero(events, sizeof(*events) * MAX_EVENTS);
}

Epoll::~Epoll() {
  if (epfd != -1) {
    close(epfd);
    epfd = -1;
  }
  delete[] events;
}

void Epoll::addFd(int fd, uint32_t op) {
  struct kevent ev;
  bzero(&ev, sizeof(ev));
  EV_SET(&ev, fd, op, EV_ADD, 0, 0, NULL);
}

std::vector<struct kevent> Epoll::poll(int timeout) {
  std::vector<struct kevent> activeEvents;
  int nfds = kevent(epfd, NULL, 0, events, MAX_EVENTS, NULL);
  errif(nfds == -1, "epoll wait error");
  for (int i = 0; i < nfds; ++i) {
    activeEvents.push_back(events[i]);
  }
  return activeEvents;
}

/*
#include <stdio.h>
#include <sys/event.h>
#include <unistd.h>

int main() {
    int kq = kqueue();
    struct kevent event;
    EV_SET(&event, STDIN_FILENO, EVFILT_READ, EV_ADD, 0, 0, NULL);

    while (1) {
        struct kevent events[1];
        int nevents = kevent(kq, &event, 1, events, 1, NULL);
        if (nevents > 0) {
            printf("Data is available on stdin\n");
            break;
        }
    }
    close(kq);
    return 0;
}
*/