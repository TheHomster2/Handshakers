#include "pipe_networking.h"

void rot13(char *buf){
  int i = 0;
  while(buf[i]){
    if (('a' <= buf[i]) && (buf[i] < 'a' + 13))
      buf[i] += 13;
    else if (('A' <= buf[i]) && (buf[i] < 'A' + 13))
      buf[i] += 13;
    else if (('Z' - 13 < buf[i]) && (buf[i] <= 'Z'))
      buf[i] += 13;
    else if (('z' - 13 < buf[i]) && (buf[i] < 'z'))
      buf[i] += 13;
  }
}

// anthony this is wrong
// 1. you're supposed to modify str not return a different string
// 2. it's supposed to switch upper to lower not just one way
// unsigned char * transupper(char *str) {
//     unsigned char *str1 = (unsigned char *) str;
//     int i = 0;
//     for (; str1[i]; i++) {
//         str1[i] = toupper(str1[i]);
//     }
// return str1;

int main() {
  int to_client;
  int from_client;

  // shake
  from_client = server_handshake(&to_client);

  // wait for client
  while(1){
    char buf[BUFFER_SIZE];
    read(from_client, buf, sizeof(buf));
    printf("revieved: %s\n", buf);

    // rot13 and send back
    rot13(buf);

    // transupper(buf);
    write(to_client, buf, sizeof(buf));
  }
  close(to_client);
  close(from_client);

  return 0;
}
