#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


// Global Variables

int N;


// Main Threads Structure

typedef struct myThread {
int id; // Id of the thread
char* filename_in; // file to read from
int start_pos; // byte position to start reading from
int end_pos; // byte postion to read till
char* filename_out; // file to write to
} myThread;


// Function to Print out the details of the current thread created

void ThreadDetails(myThread new_thread) {
printf(" Thread Number #%d [ Input File : %s, Output File : %s, byte_start_position : %d, byte_end_position : %d]\n",
new_thread.id, new_thread.filename_in, new_thread.filename_out, new_thread.start_pos, new_thread.end_pos);
}

// Main Function to FileReader and Split

void *FileReader(void* arg) {

// New Thread Initialisation
myThread *split_thread = (myThread*) arg;

printf("Thread #%d : Executing\n", split_thread->id); // print current thread details

FILE* fp = fopen(split_thread->filename_in, "r");

fseek(fp, split_thread->start_pos, SEEK_SET); // goto the thread's starting position , Looking for NewLine 

int nbytes = 0; // To keep track of how many bytes read


char c;

if(split_thread->start_pos != 0) {

    do{

        c = (char)fgetc(fp); // read a char

        nbytes++; // increate number of bytes read

        if(c == '\n' || c == EOF) {

            break;
        }// if we strike \n of EOF

         

    } while(1);

}

do {

    char *line;
    size_t lsize = 0;

    getline(&line, &lsize, fp); // read a line


    FILE* fout = fopen(split_thread->filename_out, "a+");
    fwrite(line, 1, sizeof(line), fout);
    fclose(fout);

    

    // add the size of number string to nbytes
    nbytes += (int)strlen(line);

} while((nbytes < (split_thread->end_pos - split_thread->start_pos)) || feof(fp));

fclose(fp);

printf("Thread #%d : Stopping\n", split_thread->id); 

}

// Function to get size of the file
int findFileSize(char* filename_in) {

FILE* fp = fopen(filename_in, "r"); 
fseek(fp, 0L, SEEK_END); 

int size = ftell(fp); 

fclose(fp);

return size; 

}




// File Splicer

int FileSplicer() {


char* filename_in = "file_in.txt";
char filename_out[100]; 

int filesize = findFileSize(filename_in);

printf("File size is %d bytes.\n", filesize); 




// Split file based on Number of Threads
for(int i = 1; i <= N; i++) {

    pthread_t thread;
    myThread *new_thread = (myThread*)malloc(sizeof(myThread));
    
    sprintf(filename_out, "file_part_%03d.txt", i);

    new_thread->filename_in = (char*) malloc(25*sizeof(char));
    new_thread->filename_out = (char*) malloc(strlen(filename_out)*sizeof(char));

    


    strcpy(new_thread->filename_in, filename_in);
    strcpy(new_thread->filename_out, filename_out);
    new_thread->id = i;
    new_thread->start_pos = (i-1) * (filesize/N);
    new_thread->end_pos = (i)* (filesize/N);

    ThreadDetails(*new_thread);

    // create a thread
    pthread_create(&thread, NULL, FileReader, new_thread);
    pthread_join(thread, NULL);
    

}

pthread_exit(0);




}


// Driver function
int main() {


    printf("Running File Splicer! \n");

    // read the number of threads
    printf("Enter the Number of threads :");
    scanf("%d", &N);

    FileSplicer();


   
}