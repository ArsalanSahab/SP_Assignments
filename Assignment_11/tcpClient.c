#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX 2048


int NUM_THREADS = 2;

// FUNCTION TO FIDE FILE SIZE

int findFileSize(char* filename_in) {

FILE* fp = fopen(filename_in, "r"); 
fseek(fp, 0L, SEEK_END); 

int size = ftell(fp); 

fclose(fp);

return size; 

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
	if (argc != 5)
	{
		printf("usage: %s hostname port number filename \n", argv[0]);
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


    // ------------- MAIN ALGORITHM--------------------------

      FILE *fp;
      char *filename = argv[4];
      

      fp = fopen(filename, "r");

      fseek(fp, 0L, SEEK_END);

      int filesize = ftell(fp);

      printf("File Size = %d", filesize);
  
      
      char data[MAX];
      int numb = atoi(argv[3]);

      int start_pos;
      int end_pos;
     
     if (numb == 1) {

      start_pos = 0;
      end_pos = ((numb)*(filesize/NUM_THREADS)) + 1;

     }

     else {

      start_pos = (numb - 1) * (filesize/NUM_THREADS);
      end_pos = ((numb)*(filesize/NUM_THREADS)) + 1;


     }

      
      printf("Start = %d, ENd = %d\n",start_pos, end_pos );

      fseek(fp,start_pos, SEEK_SET);
      //fgets(data, end_pos, fp);
      fread(data, end_pos , 1, fp);

      printf("Data = %s\n",data);
      send(sock, data, sizeof(data),0);
      bzero(data, MAX);
     
     


	/* close socket */
	close(sock);

  // --------------------------

	return 0;
}