// ------- HEADER FILES ---------- //

#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>



// GLOBAl DECLARATIONS
#define MAX 1024
int NUM_THREADS = 0;
 

// SOCKET STRUCTURE TO HOLD CUSTOM DATA 
typedef struct sock_thread{
	int cfd;
	struct sockaddr_in clie_addr;
	int num;
}sock_thread;
 
// PRINT ERROR MSG REMOVES REDUNDANCY
void print_error(const char *msg)
{
	perror(msg);
	exit(1);
}


// FUCNTION TO MARGE FILES

void file_merge(char *source){

   FILE *from, *to;
   char *filename = "Merged.txt";
   char c;


   from = fopen(source, "r");
    if (from == NULL)
    {
        printf("Cannot open file %s \n", source);
        exit(0);
    }

    to = fopen(filename, "a+");
    if (to == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }


    c = fgetc(from);
    while (c != EOF)
    {
        fputc(c, to);
        c = fgetc(from);
    }

    fclose(from);
    fclose(to);

}


// MAIN THREAD GET MSG FROM CLINET FUNCTION
 
void *server_thread(void *arg)
{

  

	sock_thread *s = (sock_thread *)arg;
	char ipbuf[BUFSIZ] = {};
	inet_ntop(AF_INET,&s->clie_addr.sin_addr.s_addr,ipbuf,sizeof(ipbuf));
	int n,i,port;
	port = ntohs(s->clie_addr.sin_port);
  s->num = s->num +1;

	printf("new client join ip:%s port:%d thread_number:%d.\n",ipbuf,port,s->num );



// ----------- MAIN ALGORITHM -------------


  FILE *fp;
  char *filename;
  filename = (char*) malloc(25*sizeof(char));
  sprintf(filename, "file_part_%03d.txt", s->num);
  fp = fopen(filename, "w");

  char buffer[MAX];
  int x;

  while (1) {
    
    x = read(s->cfd,buffer,sizeof(buffer));

    if (x <= 0){
      break;
      
    }

    printf("Data Recieved = %s\n\n", buffer);
    fprintf(fp,"%s",buffer);
    bzero(buffer, MAX);
    
  }

  fclose(fp);

// -------------------------------

  


	close(s->cfd);
	free(s);
	return NULL;
}
 


// -------- MAIN DRIVER FUNCTION ----------- // 
int main(int argc,char **argv)
{	

	

if(argc != 2){


		printf("usage : %s <num_threads[Must be Same in Client and Server]>\n",argv[0]);
		return -1;




}

	
NUM_THREADS = atoi(argv[1]);
	


  


  // ------- SERVER SIDE SOCKET SETUP ---------- //

	int sfd = socket(AF_INET,SOCK_STREAM,0);

	if (sfd == -1)
	{
		print_error("socket");
	}

	struct sockaddr_in serv_addr,clie_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8888);
	inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);
	int result = bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

	if (result == -1)
	{
		print_error("bind");
	}
 
	result = listen(sfd,128);

	if (result == -1)
	{
		print_error("listen");
	}

  // ---------------------------------------------------------------- //


  

  // -------- FOR LOOP TO CREATE THREADS FOR SOCKETS --------------- //
	int i = 0;

  int quit = 0;
	while(quit != NUM_THREADS)
	{
		socklen_t clie_addr_len = sizeof(clie_addr);
		int cfd = accept(sfd,(struct sockaddr *)&clie_addr,&clie_addr_len);
		if (cfd == -1)
		{
			print_error("accept");
		}
		
		sock_thread *clie_sock = (sock_thread *)malloc(sizeof(sock_thread));
		clie_sock->cfd = cfd;
		clie_sock->clie_addr = clie_addr;
		clie_sock->num = i++;
    
		pthread_t id;
		pthread_create(&id,NULL,(void *)server_thread,(void *)clie_sock);
		//pthread_detach(id);
    pthread_join(id,NULL);

    quit++;

	} 

  //--------------------------------------------------------------------------------- //


  // FILES MERGE DRIVER

  char *file = (char*) malloc(25*sizeof(char));

  for (int d = 1; d < NUM_THREADS +1; d++) {
      sprintf(file, "file_part_%03d.txt", d);
      file_merge(file);
}

 
printf("Files Merged");
return 0;
}