#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 1024


int NUM_THREADS = 0;
 

// SOCKET STRUCTURE TO HOLD CUSTOM DATA 
typedef struct sock_info{
	int cfd;
	struct sockaddr_in clie_addr;
	int num;
}s_info;
 
// PRINT ERROR MSG REMOVES REDUNDANCY

void print_error(const char *msg)
{
	perror(msg);
	exit(1);
}


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

    to = fopen(filename, "w");
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

    printf("Files Merged");




}


// MAIN THREAD GET MSG FROM CLINET FUNCTION
 
void *get_msg(void *arg)
{

  

	s_info *s = (s_info *)arg;
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
 
int main(int argc,char **argv)
{	

  NUM_THREADS = atoi(argv[1]);


  // SERVER SIDE SOCKET SETUP

	int sfd = socket(AF_INET,SOCK_STREAM,0);
	if (sfd == -1)
	{
		print_error("socket");
	}

	struct sockaddr_in serv_addr,clie_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8888);
	//serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

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

  // ----------------------------------


  

  // THREADED SERVER SOCKETS 
	int i = 0;
	while(1)
	{
		socklen_t clie_addr_len = sizeof(clie_addr);
		int cfd = accept(sfd,(struct sockaddr *)&clie_addr,&clie_addr_len);
		if (cfd == -1)
		{
			print_error("accept");
		}
		
		s_info *clie_sock = (s_info *)malloc(sizeof(s_info));
		clie_sock->cfd = cfd;
		clie_sock->clie_addr = clie_addr;
		clie_sock->num = i++;
    
		pthread_t id;
		pthread_create(&id,NULL,(void *)get_msg,(void *)clie_sock);
		//pthread_detach(id);
    pthread_join(id,NULL);

    

    
	} 

  //------------------------------


  // Merging Files


  

	return 0;
}