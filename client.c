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

int main() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr = {AF_INET, htons(777), INADDR_ANY};
  socklen_t addr_len = sizeof(addr);

  int connectAck = connect(fd, (struct sockaddr *)&addr, addr_len);

  if (connectAck >= 0) {
    printf("Connection successful. status_code: %d\n", connectAck);
    char *req = "hello word!";
    char resp[100];
    write(fd, req, sizeof(char) * 11);
    read(fd, resp, sizeof(char) * 4);
    printf("response: %s\n", resp);
    close(fd);
    return 0;
  } else {
    printf("Failed: %d", connectAck);
    perror("connection failed");
    return 0;
  }
  return 0;
}
