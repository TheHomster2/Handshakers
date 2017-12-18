#include "pipe_networking.h"

void rot13(char *buf){
  int i = 0;
  while(buf[i]){
    if (('a' <= buf[i]) && (buf[i] < 'a' + 13))
      buf[i] += 13;
    else if (('A' <= buf[i]) && (buf[i] < 'A' + 13))
      buf[i] += 13;
    else if (('Z' - 13 < buf[i]) && (buf[i] <= 'Z'))
      buf[i] -= 13;
    else if (('z' - 13 < buf[i]) && (buf[i] < 'z'))
      buf[i] -= 13;
    i ++;
  }
}

// Translating the letters to uppercase and lowercase simultaneously
void translate(char *buf){
  int i = 0;
  int length;
  length = strlen(buf);
  while(i < length){
    if ((buf[i] >= 65) && (buf[i] <= 90)){
      buf[i] = buf[i] + 32;
    }
    else if ((buf[i] >= 97) && (buf[i] < 122)){
      buf[i] = buf[i] - 32;
    }
    i++;
  }
}

int main() {
  int to_client;
  int from_client;
  char buf[BUFFER_SIZE];

  while(1){
    // shake
    from_client = server_handshake(&to_client);

    // while there is input
    while(read(from_client, buf, sizeof(buf))){
      printf("recieved: %s", buf);
      // rot13 and send back
      rot13(buf);
      translate(buf);
      write(to_client, buf, strlen(buf) + 1);
    }

    close(to_client);
    close(from_client);
  }
}
