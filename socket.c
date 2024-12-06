#include <arpa/inet.h>
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
  char c[12];
  read(clientFD, c, sizeof(char) * 12);
  char *resp = "ack!";
  write(clientFD, resp, sizeof(char) * 4);
  sleep(1);
  printf("payload: %s \n", c);
  return 1;
}

int isChild(int pid) {
  if (pid == 0)
    return 1;
  return 0;
}

int main() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  struct in_addr address;
  struct sockaddr_in addr = {AF_INET, htons(1025), INADDR_ANY};
  socklen_t addr_len = sizeof(addr);

  int bindAck = bind(fd, (struct sockaddr *)&addr, addr_len);
  if (bindAck >= 0) {
    printf("Bind successful.\n");
  } else {
    perror("Error: ");
    return 0;
  }

  int listenAck = listen(fd, 1);
  if (listenAck >= 0) {
    printf("Listening.\n");
  } else {
    perror("Error: ");
    return 0;
  }

  while (1) {

    struct sockaddr_in client = {};
    socklen_t client_addr_len = sizeof(client);
    int clientFD = accept(fd, (struct sockaddr *)&client, &client_addr_len);

    printf("receivers port: %d\n", client.sin_port);
    printf("receivers ip: %s\n", inet_ntoa(client.sin_addr));

    if (clientFD >= 0) {
      int pid = fork();
      if (isChild(pid)) {
        handle_connection(clientFD);
      }
      close(clientFD);
      if (isChild(pid)) {
        return 0;
      } else {
        // waitpid(pid);
      }
    } else {
      printf("Failed Connection");
    }
  }

  return 0;
}
