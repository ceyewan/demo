#pragma once
#include <sys/event.h>
#include <vector>
class Epoll {
public:
  Epoll();
  ~Epoll();
  void addFd(int fd, uint32_t op);
  std::vector<struct kevent> poll(int timeout = -1);

private:
  int epfd;
  struct kevent *events;
};

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