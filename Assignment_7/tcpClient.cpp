/* pont.net    */


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* close */

#define SERVER_PORT 1500
#define MAX_MSG 100

int main(int argc, char *argv[])
{

  int sd, rc, i;
  struct sockaddr_in localAddr, servAddr;
  struct hostent *h;

  if (argc < 2)
  {
    printf("usage: %s <server>\nYour message goes here...\n", argv[0]);
    //end(1);
  }

  h = gethostbyname(argv[1]);
  if (h == NULL)
  {
    printf("%s: unknown host '%s'\n", argv[0], argv[1]);
    //end(1);
  }

  servAddr.sin_family = h->h_addrtype;
  memcpy((char *)&servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  servAddr.sin_port = htons(SERVER_PORT);

  /* create socket */
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if (sd < 0)
  {
    perror("cannot open socket ");
    //end(1);
  }

  /* bind any port number */
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(0);

  rc = bind(sd, (struct sockaddr *)&localAddr, sizeof(localAddr));
  if (rc < 0)
  {
    printf("%s: cannot bind port TCP %u\n", argv[0], SERVER_PORT);
    perror("error ");
    //end(1);
  }

  /* connect to server */
  rc = connect(sd, (struct sockaddr *)&servAddr, sizeof(servAddr));
  if (rc < 0)
  {
    perror("cannot connect ");
    //end(1);
  }

  char user[200];
  char pass[200];
  
  printf("Username: ");
  scanf("%c", user);
  
  printf("Password: ");
  scanf("%c", pass);
  
  rc = send(sd, user, strlen(user) + 1, 0);
  rc = send(sd, pass, strlen(pass) + 1, 0);
  
  char res[1000];
  read(sd, res, sizeof(res));

  if (strcmp(res, "Invalid") == 0) {
    printf("Invalid Username or Password. Access Denied.\n");
    close(rc);
    //end(1);
  }

  int end = 0;
  char buff[1000];
  char comm[1000];

  while (1)
  {
    printf("Command: ");
    scanf("%c", comm);
    
    char *ptr = strtok(comm, "");
    while (ptr != NULL)
    {
      if (strcmp(ptr, "exit()") == 0)
      {
        end = 1;
        break;
      }
      else
      {
        rc = send(sd, ptr, strlen(ptr) + 1, 0);
        read(sd, buff, sizeof(buff));
        printf("Response:\n%s\n", buff);
        ptr = strtok(NULL, "");
      }
    }
    if (end == 1)
    {
      break;
    }
  }

  return 0;
}
