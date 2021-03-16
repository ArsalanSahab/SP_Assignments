#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<cstring>
#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fstream>





int main(int argc, char **argv){


	// Stream for File to Copy, opened in READ ONLY MODe
    int sf = open(argv[1], O_RDONLY);

	// Stream for new File, opened in READ/WRTIE MODE
    int tf = open(argv[2], O_RDONLY | O_CREAT | O_WRONLY);

    if (sf < 0 || tf < 0){

        printf("Error! \n");

        return 0;

    }

	
	// Allocating memory, size = number of bytes == 1MB
    void *c = (void *)malloc(102400);

	// Check if file can be opened/exists.
    int check = read(sf,c,1);

    while(check != 0){

        if (check == -1){
            printf("Error! \n");
            return 0;
        }

        write(tf,c,1);

        

		 check = read(sf,c,1);
    }

 
 	printf("Done! \n");
	// Close Both Files
    close(sf);
    close(tf);
    




    return 0;
}