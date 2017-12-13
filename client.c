#include "pipe_networking.h"


int main() {
  int to_server;
  int from_server;

  // shake
  from_server = client_handshake(&to_server);

  // get user input and send it to server
  char buf[BUFFER_SIZE];
  printf("input:");
  fgets(buf, sizeof(buf), stdin);
  printf("you entered: %s\n", buf);
  write(to_server, buf, strlen(buf));

  // get processed string back and print it
  read(from_server, buf, sizeof(buf));
  printf("processed message: %s\n", buf);
}
