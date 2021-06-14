#include "webio.h"
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Webio_s {
  short port;
  int master;
};

Webio new_webio() {
  int on = 1;
  Webio w = malloc(sizeof(struct Webio_s));
  w->port = 80;

  // Open a new socket
  if ((w->master = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "[Webc] 'socket' error (%s)\n", strerror(errno));
    exit(1);
  }

  // Set socket options (1)
  if (setsockopt(w->master, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
    fprintf(stderr, "[Webc] 'setsocketopt' error (%s)\n", strerror(errno));
    exit(1);
  }

  // Set socket options (2)
#ifdef SO_REUSEPORT
  // If avaliable, set the "Reuse Port" option
  if (setsockopt(w->master, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) < 0) {
    fprintf(stderr, "[Webc] 'setsockopt' error (%s)\n", strerror(errno));
    exit(1);
  }
#endif

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(w->port);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // Binding the socket to an address
  if (bind(w->master, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    fprintf(stderr, "[Webc] 'bind' error (%s)\n", strerror(errno));
    exit(1);
  }

  return w;
}