#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  // make fifo
  if(mkfifo("WKP", 0644))
    perror("mkfifo");
  int from = open("WKP", O_RDONLY);

  // wait for message
  char buf[HANDSHAKE_BUFFER_SIZE];
  // printf("asdfasdfasdf\n");
  read(from, buf, sizeof(buf));
  printf("server reading buf: %s\n", buf);

  // send message back
  remove("WKP");
  int to = open(buf, O_WRONLY);
  char buff[sizeof(ACK)] = ACK;
  // printf("asdfasdfasdf\n");
  write(to, buff, sizeof(buff));
  printf("server writing buf: %s\n", buff);

  // confirm sending capabilities
  read(from, buff, sizeof(buff));
  printf("server reading buff: %s\n", buff);
  // printf("asdfasdfasdf\n");

  // check message
  if(strcmp(buff, ACK))
    printf("wrong message: %s\n", buff);

  // return fds
  *to_client = to;
  return from;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  // write to WKP
  int toserver = open("WKP", O_WRONLY);
  char buf[HANDSHAKE_BUFFER_SIZE];
  sprintf(buf, "%d", getpid());
  if(mkfifo(buf, 0644))
    perror("mkfifo");
  // printf("asdfasdfasdf\n");
  write(toserver, buf, sizeof(buf));
  printf("client writing buf: %s\n", buf);
  perror("write");

  // wait for response
  // i don't know why it's blocking on this open
  int fromserver = open(buf, O_RDONLY);
  // printf("asdf\n");
  char buff[HANDSHAKE_BUFFER_SIZE];
  // printf("asdf\n");
  read(fromserver, buff, sizeof(buff));
  printf("client reading buff: %s\n", buff);
  remove(buf);

  // confirm response
  // printf("asdf\n");
  write(toserver, buff, sizeof(buff));

  printf("client writing buff: %s\n", buff);

  // return fds
  *to_server = toserver;
	return fromserver;
}
