#include <poll.h>
#include <sndio.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int n = 0;
  struct mio_hdl *m;
  struct pollfd pfds[1] = {{0}};
  char midibuf[4096] = {0};
  if (argc == 2) {
    m = mio_open(argv[0], MIO_IN | MIO_OUT, 1);
  } else {
    m = mio_open("rmidi/0", MIO_IN | MIO_OUT, 1);
  }
  pfds[0].fd = STDIN_FILENO;
  pfds[0].events = POLLIN;
  while(poll(pfds, 1, 0) != -1) {
    if (pfds[0].revents & POLLIN) {
      n = read(STDIN_FILENO, midibuf, 4096);
      mio_write(m, midibuf, n);
    }
    n = mio_read(m, midibuf, 4096);
    mio_write(m, midibuf, n);
  }
  mio_close(m);
}
