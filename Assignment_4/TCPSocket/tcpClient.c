/* fpont 12/99 */
/* pont.net    */
/* tcpClient.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* close */
//using namespace std;

#define SERVER_PORT 1500
#define MAX_MSG 100

int main (int argc, char *argv[]) {

  int sd, rc, i;
  struct sockaddr_in localAddr, servAddr;
  struct hostent *h;
  
  
  printf("Enter the IP Address of the server: ");
  char ip[15];
  scanf(" %s", ip);

  h = gethostbyname(ip);
  if(h==NULL) {
    printf("%s: unknown host '%s'\n",argv[0],argv[1]);
    exit(1);
  }

  servAddr.sin_family = h->h_addrtype;
  memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  servAddr.sin_port = htons(SERVER_PORT);

  /* create socket */
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd<0) {
    perror("cannot open socket ");
    exit(1);
  }

  /* bind any port number */
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(0);
  
  rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
  if(rc<0) {
    printf("%s: cannot bind port TCP %u\n",argv[0],SERVER_PORT);
    perror("error ");
    exit(1);
  }
				
  /* connect to server */
  rc = connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
  if(rc<0) {
    perror("cannot connect ");
    exit(1);
  }

  int term = 0;
 
  while (1)

  {
    
    char in[1000];
    printf("Enter your message: ");
    scanf("%s", in);
    
    char *ptr = strtok(in, " ");
    while (ptr != NULL)
    {

      if (strcmp(ptr, "exit") == 0) {
        term = 1;
        break;
      }

      else{
        rc = send(sd, ptr, strlen(ptr) + 1, 0);
        ptr = strtok(NULL, " ");
      }

    }
    if (term == 1) {

      break;
    }

  }

  

return 0;
  
}

