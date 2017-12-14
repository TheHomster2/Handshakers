#include "pipe_networking.h"

void rot13(char *buf){

}

unsigned char * transupper(char *str) {
    unsigned char *str1 = (unsigned char *) str;
    int i = 0;
    for (; str1[i]; i++) {
        str1[i] = toupper(str1[i]);
    }
return str1;

int main() {
  int to_client;
  int from_client;

  // shake
  from_client = server_handshake(&to_client);
  if (from_client == -1){
	printf("Failure to connect");
	return 1;

  // wait for client
  char buf[BUFFER_SIZE];
  read(from_client, buf, sizeof(buf));
  if (strcmp(buf, "\n") == 0){
	close(to_client);
	close(from_client);
	}
  printf("%s\n", buf);
	

  // rot13 and send back
  rot13(buf);
  transupper(buf)
  write(to_client, buf, strlen(buf));

}	
