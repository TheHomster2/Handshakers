#include "pipe_networking.h"

void rot13(char *buf){

}

int main() {
  int to_client;
  int from_client;

  // shake
  from_client = server_handshake(&to_client);

  // wait for client
  char buf[BUFFER_SIZE];
  read(from_client, buf, sizeof(buf));

  // rot13 and send back
  rot13(buf);
  write(to_client, buf, strlen(buf));

}
