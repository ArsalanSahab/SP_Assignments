#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include <grp.h>
#include <string.h>

#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fstream>



void cmdReverse(struct dirent **namelist, char *directoryPath) {


		int num_files;
		int index = 0;
		
		num_files = scandir(directoryPath, &namelist, NULL,alphasort);
		
		if(num_files < 0) 
		
		{ 
		
		perror("scandir"); 
		exit(EXIT_FAILURE); 
		} 
		
		else 
		{ 
		
		while (index < num_files) 
		
		{ 
			
			if (( strcmp(namelist[index]->d_name,".") != 0 ) && ( strcmp(namelist[index]->d_name,"..") != 0 )) {
			
				printf("%s\n", namelist[index]->d_name);
			}
			 
			free(namelist[index]);
			++index; 
		}
		 
		
		free(namelist); 
	} 
	
	
		
}




void cmdNormal(struct dirent **namelist, char *directoryPath) {


	 
	int num_files; 
	
	num_files = scandir(directoryPath, &namelist, NULL, alphasort);
	
	if(num_files < 0) 
	{ 
		perror("scandir"); 
		exit(EXIT_FAILURE); 
	} 
	else 
	{ 
		while (num_files--) 
		{ 
			if (( strcmp(namelist[num_files]->d_name,".") != 0 ) && ( strcmp(namelist[num_files]->d_name,"..") != 0 )) {
			
			char fname[255];
			
			strncpy(fname, namelist[num_files]->d_name, 254);
        	fname[254] = '\0';
			
			//namelist[num_files]->d_name;
			
			//fname = d_name;
			
			printf("%s\n",fname); 
			
				// ---------------- SIMPLY COPY FUNCTION CODE ------------------------//

	// Stream for File to Copy, opened in READ ONLY MODE
    int sf = open(fname, O_RDONLY);

	 char str[10] = "copy_";
	
		strcat(str,fname);

	// Stream for new File, opened in READ/WRTIE MODE
    int tf = open(str, O_RDONLY | O_CREAT | O_WRONLY);

    if (sf < 0 || tf < 0){

        printf("Error! \n");

        

    }

	
	// Allocating memory, size = number of bytes == 1MB
    void *c = (void *)malloc(102400);

	// Check if file can be opened/exists.
    int check = read(sf,c,1);

    while(check != 0){

        if (check == -1){
            printf("Permissions Error \n");
				break;
            
        }

        write(tf,c,1);

        

		 check = read(sf,c,1);
    }

 
 	printf("Done! \n");
	// Close Both Files
    close(sf);
    close(tf);
   


// ---------------------------------------------------------------- //



			
		
			
			
			
			
			
			
			free(namelist[num_files]); }
		} 
		free(namelist); 
	}
		
		
}


void locateFile(struct dirent **namelist, char *directoryPath) {


	printf("Enter Filename to Locate");


	char filename[100];
	
	
	
	scanf("%s", filename); 

	int num_files; 
	
	num_files = scandir(directoryPath, &namelist, NULL, alphasort);
	
	if(num_files < 0) 
	{ 
		perror("scandir"); 
		exit(EXIT_FAILURE); 
	} 
	else 
	{ 
		while (num_files--) 
		{ 
			if ( strcmp(namelist[num_files]->d_name,filename) == 0 ) {
			
			printf("File Exists in current Directory \n");
			//printf("%s\n",namelist[num_files]->d_name); 
			free(namelist[num_files]); 
		
			
			}
			
			
			else {
			
				printf("File does not exist \n");
				break;
			
			}
		} 
		free(namelist); 
	}
	
	

}

void cmdAll(struct dirent **namelist, char *directoryPath) {


	   int num_files;
		int index = 0;
		
		num_files = scandir(directoryPath, &namelist, NULL,alphasort);
		
		if(num_files < 0) 
		
		{ 
		
		perror("scandir"); 
		exit(EXIT_FAILURE); 
		} 
		
		else 
		{ 
		
		while (index < num_files) 
		
		{ 
			
			
			
			printf("%s\n", namelist[index]->d_name);
			
			 
			free(namelist[index]);
			++index; 
		}
		 
		
		free(namelist); 
	} 	
		
}



void cmdLong( char* userPath ) {


  struct passwd *pw;
  struct group *gp;
  struct dirent *ep;
  struct stat fs;

	
  //char* userPath = directoryPath;
  DIR *directoryPath;
  char *c;

  

  directoryPath=opendir(userPath);
  
  stat(userPath,&fs); 

  while((ep=readdir(directoryPath))!= NULL)

  {

    stat(ep->d_name,&fs);  

	// Printing Permissions and Type of File
    
    printf( (S_ISDIR(fs.st_mode)) ? "d" : "-");
    printf( (fs.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fs.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fs.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fs.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fs.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fs.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fs.st_mode & S_IROTH) ? "r" : "-");
    printf( (fs.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fs.st_mode & S_IXOTH) ? "x" : "-"); 


    printf(" ");
    printf("%d ",fs.st_nlink);

    pw=getpwuid(fs.st_uid);
    printf("%s ",pw->pw_name);

    gp=getgrgid(fs.st_gid);
    printf("%s ",gp->gr_name);
    printf("%lli ",fs.st_size);

    c=ctime(&fs.st_mtime);

    for ( int i = 4;i <= 15; i++ )
      printf("%c",c[i]);

    printf(" ");
    printf("%s\n",ep->d_name);

  }

  closedir(directoryPath);  
      
}


 


int main(int argc, char *argv[])
 
{ 
	struct dirent **namelist; 
	
	char *dirPath = argv[1];
	
	
	int userChoice = 0;
	
	//scanf("%i", userChoice);
	
	
	
	while (1) {
	
	
	printf("Enter Your Choice : \n Enter 1 for : ls \n Enter 2 for : ls -r \n Enter 3 for : ls -a \n Enter 4 for : ls -l \n Enter 5 for : locate file \n Enter 6 for : quit\n");
	
	
	scanf("%d", &userChoice);
	
	
	if (userChoice == 1) {
	
	
	printf("Executing Command : ls \n");
	cmdNormal(namelist, dirPath);
	
	
	}
	
	else if (userChoice == 2) {
	
	
	printf("Executing Command : ls -r \n");
	cmdReverse(namelist, dirPath);
	
	
	
	}
	
	else if (userChoice == 3) {
	
	printf("Executing Command : ls -a \n");
	cmdAll(namelist, dirPath);
	
	
	}
	
	else if (userChoice == 4 ){
	
	
	printf("Executing Commadn : ls -l \n");
	cmdLong(dirPath);
	
	
	
	
	}
	
	
	else if(userChoice == 5) {
	
	
		
		locateFile(namelist,dirPath);	
	
	}
	
	else {
	
	
		exit(EXIT_SUCCESS);
	
	}
	
	
	
	
	
	}
	
	
	
	
	return 0;
	
	
	
	
	
	} 
	
	

	
	
