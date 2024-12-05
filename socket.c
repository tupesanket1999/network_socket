#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <netinet/in.h>
#include <printf.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

int handle_connection(int clientFD) {
  // printf("Connection accepted. status_code: %d\n", clientFD);
  char c[100];
  read(clientFD, c, sizeof(c));
  char *resp = "ack!";
  write(clientFD, resp, sizeof(char) * 4);
  sleep(1);
  printf("payload: %s\n", c);
  close(clientFD);
  return 1;
}

int main() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  struct in_addr address;
  struct sockaddr_in addr = {AF_INET, htons(777), INADDR_ANY};
  socklen_t addr_len = sizeof(addr);

  int bindAck = bind(fd, (struct sockaddr *)&addr, addr_len);

  if (bindAck >= 0) {
    printf("Connection successful. status_code: %d\n", bindAck);
  } else {
    printf("\nbind failed\n");
    perror("");
  }
  int listenAck = listen(fd, 1);

  printf("Listening. status_code: %d\n", listenAck);

  while (1) {
    int clientFD = accept(fd, (struct sockaddr *)&addr, &addr_len);
    int pid = fork();
    if (clientFD >= 0 && pid == 0) {
      handle_connection(clientFD);
    } else if (clientFD < 0) {
      printf("Failed Connection");
    }
    close(clientFD);
  }

  return 0;
}
