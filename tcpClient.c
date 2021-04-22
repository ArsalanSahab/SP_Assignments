#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 2048


int NUM_THREADS = 2;

typedef struct sock_info{
	int cfd;
	int num;
}s_info;


void *send_file(void *arg) {

    // ------------- MAIN ALGORITHM--------------------------


      s_info *s = (s_info *)arg;
      FILE *fp;
      char *filename = "test_1.txt";
      
      fp = fopen(filename, "r");

      fseek(fp, 0L, SEEK_END);

      int filesize = ftell(fp);

      printf("File Size = %d", filesize);
  
      
      char data[MAX];
     

      int start_pos;
      int end_pos;
     
     if (s->num == 1) {

      start_pos = 0;
      end_pos = ((s->num)*(filesize/NUM_THREADS)) + 1;

     }

     else {

      start_pos = (s->num - 1) * (filesize/NUM_THREADS);
      end_pos = ((s->num)*(filesize/NUM_THREADS)) + 1;


     }

      
      printf("Start = %d, End = %d\n",start_pos, end_pos );

      fseek(fp,start_pos, SEEK_SET);
      fread(data, end_pos , 1, fp);

      printf("Data = %s\n",data);
      send(s->cfd, data, sizeof(data),0);
      bzero(data, MAX);

     

     // -------------------------------------





  
}

int main(int argc, char ** argv)
{

  // CLIENT SIDE SOCKET SETUP

	int port;
	int sock = -1;
	struct sockaddr_in address;
	struct hostent * host;
	int len;
	
	/* checking commandline parameter */
	if (argc != 4)
	{
		printf("usage: %s hostname port filename \n", argv[0]);
		return -1;
	}

	/* obtain port number */
	if (sscanf(argv[2], "%d", &port) <= 0)
	{
		fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
		return -2;
	}

	/* create socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
		return -3;
	}

	/* connect to server */
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	host = gethostbyname(argv[1]);
	if (!host)
	{
		fprintf(stderr, "%s: error: unknown host %s\n", argv[0], argv[1]);
		return -4;
	}
	memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);
	if (connect(sock, (struct sockaddr *)&address, sizeof(address)))
	{
		fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
		return -5;
	}


    //-----------------------


    //------------------ THREADING

    for (int i = 1; i <= NUM_THREADS; i++) {


    s_info *clie_sock = (s_info *)malloc(sizeof(s_info));
		clie_sock->cfd = sock;
		clie_sock->num = i;
		pthread_t id;

    printf("Executing Thread Number #%d \n" , clie_sock->num);
		pthread_create(&id,NULL,(void *)send_file,(void *)clie_sock);
		pthread_detach(id);
    

    printf("Halting Thread Number #%d \n", clie_sock->num);


    }


    // --------------------


	/* close socket */

  close(sock);
	

  // --------------------------

	return 0;
}