

```c
#include "cliserv.h"

int
main(int argc, char *argv[])
{                             /* simple TCP client */
  struct  sockaddr_in serv;
  char    request[REQUEST], reply[REPLY];
  int     sockfd, n;
  
  if (argc != 2)
    err_quit("usage: tcpcli <IP address of server>");
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    err_sys("socket error");
    
  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;
  ```
