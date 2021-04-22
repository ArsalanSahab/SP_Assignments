#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>


int NUM_THREADS = 2;


typedef struct sock_info{
	
	int id;
}s_info;

void * cientThread(void *arg)
{

  s_info *s = (s_info *)arg;

  printf("Executing Thread Number #%d\n", s->id);    
 
  char message[1024];
  char buffer[1024];
  int clientSocket;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  // Create the socket. 
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  //Configure settings of the server address
 // Address family is Internet 
  serverAddr.sin_family = AF_INET;

  //Set port number, using htons function 
  serverAddr.sin_port = htons(8888);

 //Set IP address to localhost
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    //Connect the socket to the server using the address
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    // --------------------- MAIN LOGIC ------------------------- //

      FILE *fp;
      char *filename = "test_1.txt";
      
      fp = fopen(filename, "r");

      fseek(fp, 0L, SEEK_END);

      int filesize = ftell(fp);

      printf("File Size = %d\n", filesize);

     
      int start_pos;
      int end_pos;
     
     if (s->id == 1) {

      start_pos = 0;
      end_pos = ((s->id)*(filesize/NUM_THREADS)) + 1;

     }

     else {

      start_pos = (s->id - 1) * (filesize/NUM_THREADS);
      end_pos = ((s->id)*(filesize/NUM_THREADS)) + 1;


     }

    printf("Start = %d, End = %d\n",start_pos, end_pos );

      fseek(fp,start_pos, SEEK_SET);
      fread(buffer, end_pos , 1, fp);

      

    // ---------------------------------------------------------- //






    //strcpy(message,"Hello\n");

   if( send(clientSocket , buffer , strlen(buffer) , 0) < 0)
    {
            printf("Send failed\n");
    }
    bzero(buffer,sizeof(buffer));
    //Print the received message
    printf("Data Tranferred \n");
    close(clientSocket);
    pthread_exit(NULL);
}
int main(){
  int i = 1;
  pthread_t tid[NUM_THREADS];
  while(i<3)
  {

    s_info *clie_sock = (s_info *)malloc(sizeof(s_info));
	clie_sock->id = i;  
    
    if( pthread_create(&tid[i], NULL, cientThread, (void *)clie_sock) != 0 )
           printf("Failed to create thread\n");
    i++;
  }
  
  i = 1;
  while(i<3)
  {
     printf("Closing Thread \n"); 
     pthread_join(tid[i++],NULL);
     
    
  }
  return 0;
}