#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>


int NUM_THREADS = 0;


typedef struct sock_info{
	
	int id;
}s_info;




void * cientThread(void *arg)
{




   FILE *fp;
    char *filename = "test_1.txt";
      
   fp = fopen(filename, "r");


   

  s_info *s = (s_info *)arg;

  printf("Executing Thread Number #%d\n", s->id);    
 
  char message[2048];
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

     
    
      fseek(fp, 0L, SEEK_END);

      int filesize = ftell(fp);

      printf("File Size = %d\n", filesize); 

     
      int start_pos;
      int end_pos;
     
     if (s->id == 1) {

      start_pos = 0;
      end_pos = ((s->id)*(filesize/NUM_THREADS));

     }

     else  {

      start_pos = (s->id - 1) * (filesize/NUM_THREADS);
      end_pos = ((s->id)*(filesize/NUM_THREADS)) ;


     }

    printf("Start = %d, End = %d\n",start_pos, end_pos );

    

      fseek(fp,start_pos, SEEK_SET);
      
      fread(buffer, sizeof(char), (end_pos-start_pos), fp);
      
  
    // ---------------------------------------------------------- //

    printf("Data = %s\n", buffer);

   if( send(clientSocket , buffer , strlen(buffer) , 0) < 0)
    {
            printf("Send failed\n");
    }
    bzero(buffer,sizeof(buffer));

    //Print the received message
    printf("Data Tranferred \n");
    printf("Closing Thread Number #%d \n\n",s->id); 
    close(clientSocket);
    pthread_exit(NULL);
}
int main(int argc,char **argv){


  NUM_THREADS = atoi(argv[1]);



  for(int i = 1; i <= NUM_THREADS; i++) {

    pthread_t thread[NUM_THREADS];
     s_info *clie_sock = (s_info *)malloc(sizeof(s_info));
	  clie_sock->id = i;  
  
    // create a thread
    pthread_create(&thread[i], NULL, cientThread, (void *)clie_sock);
    pthread_join(thread[i], NULL);
    

}

pthread_exit(0);

// ---------------


  


  

  return 0;
}