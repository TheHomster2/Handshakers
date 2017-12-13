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
  read(from, buf, sizeof(buf));

  // send message back
  remove("WKP");
  char buff[BUFFER_SIZE] = ACK;
  int to = open(buf, O_WRONLY);
  write(to, buff, sizeof(buff));

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
	write(toserver, buf, sizeof(buf));

  // wait for response
  int fromserver = open(buf, O_RDONLY);
  char buff[BUFFER_SIZE];
  read(fromserver, buff, sizeof(buff));

  //check
  

  // return fd
  *to_server = toserver;
	return fromserver;
}
