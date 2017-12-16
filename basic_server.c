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

// Couldn't figure out how to implement rot(n)
// Runs along the lines of rot13 however
/*
void rotn(char *buf){

}
*/
int main() {
  int to_client;
  int from_client;

  // shake
  from_client = server_handshake(&to_client);

  while(1){
    // wait for client
    char buf[BUFFER_SIZE];
    read(from_client, buf, sizeof(buf));
    printf("recieved: %s", buf);

    // rot13 and send back
    rot13(buf);
    // implement translate here
    // translate(buf);
    write(to_client, buf, strlen(buf) + 1);
  }
  close(to_client);
  close(from_client);

  return 0;
}
