#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define CSTAR(adr) ((const struct sockaddr *)&adr)
#define STAR(adr) ((struct sockaddr *)&adr)

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage : %s port\n", argv[0]);
    exit(1);
  }

  short port = (short)atoi(argv[1]);
  int res;

  int master = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (master < 0) {
    perror("Server : socket creation failed");
    exit(1);
  }
  int on = 1;
  res = setsockopt(master, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  res = bind(master, CSTAR(addr), sizeof(addr));

  if (res < 0) {
    perror("Server : error bind");
    exit(1);
  }

  struct sockaddr_in cli_addr;
  int cli_len = sizeof(cli_addr);
  res = listen(master, SOMAXCONN);

  if (res < 0) {
    perror("Server : listen failed");
    exit(1);
  }

  fprintf(stderr, "Listening on port %d\n", port);

  char buff[512];
  int client_socket;

  while ((client_socket =
              accept(master, STAR(cli_addr), (socklen_t *)&cli_len)) != -1) {
    printf("Server : connection accepted with %s\n",
           inet_ntoa(cli_addr.sin_addr));
    res = recv(client_socket, buff, 512, 0);
    if (res < 0) {
      perror("Server : recv failed");
      exit(1);
    }
    buff[res] = '\0';
    printf("Got '%s'\n", buff);

    char *page = "HTTP/1.1 200 OK\n"
                 "Date: unknown\n"
                 "Content-Type: text/html; charset=UTF-8\n"
                 "Content-Length: 200\n"
                 "Last-Modified: unknown\n"
                 "Server: Webc\n"
                 "Accept-Ranges: bytes\n"
                 "Connection: close\n\n"
                 "<html lang =\"fr\">"
                 "<head>"
                 "<meta charset = \"utf-8\">"
                 "<title>Webc</title>"
                 "</head>"
                 "<body>Hello There</body>"
                 "</html>";
    res = send(client_socket, page, strlen(page), 0);
    if (res < 0) {
      perror("Server : send failed");
      exit(1);
    }
  }

  return 0;
}