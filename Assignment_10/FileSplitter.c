#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


// Strcuture to Record Information of Each Thread Created

typedef struct myThread {
int id; // Id of the thread
char* filename_in; // file to read from
int start_pos; // start pos of the thread
int end_pos; // end pos of the thread
char* filename_out; // file to write to
} myThread;


// Function to Print out the details of the current thread created
void printThreadInfo(myThread new_thread) {
printf(" Thread %d [ filename_in : %s, filename_out : %s, start_pos : %d, end_pos : %d]\n",
new_thread.id, new_thread.filename_in, new_thread.filename_out, new_thread.start_pos, new_thread.end_pos);
}

// Main Function to ReadFile and Split

void *ReadFile(void* arg) {

// New Thread Initialisation
myThread *tinfo = (myThread*) arg;

printf("T%d : STARTING\n", tinfo->id); // print current thread details

FILE* fp = fopen(tinfo->filename_in, "r");

fseek(fp, tinfo->start_pos, SEEK_SET); // goto the thread's starting position , Looking for NewLine 

int nbytes = 0; // To keep track of how many bytes read


char c;

if(tinfo->start_pos != 0) {

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


    FILE* fout = fopen(tinfo->filename_out, "a+");
    fwrite(line, 1, sizeof(line), fout);
    fclose(fout);

    

    // add the size of number string to nbytes
    nbytes += (int)strlen(line);

} while((nbytes < (tinfo->end_pos - tinfo->start_pos)) || feof(fp));

fclose(fp);

printf("T%d : HALTING\n", tinfo->id); 

}

// Function to get size of the file
int findFileSize(char* filename_in) {

FILE* fp = fopen(filename_in, "r"); 
fseek(fp, 0L, SEEK_END); 

int size = ftell(fp); 

fclose(fp);

return size; 

}


// Driver function
int main() {

int N; // number of thread

char* filename_in = "file_in.txt";
char filename_out[100]; 

int filesize = findFileSize(filename_in);

printf("File size is %d bytes.\n", filesize); 

// read the number of threads
printf("Enter the Number of threads :");
scanf("%d", &N);


// Split file based on Number of Threads
for(int i = 1; i <= N; i++) {

    pthread_t thread;
    myThread *new_thread = (myThread*)malloc(sizeof(myThread));
    //new_thread->filename_in = (char*) malloc(strlen(filename_in)*sizeof(char));
    //new_thread->filename_out = (char*) malloc(strlen(filename_out)*sizeof(char));
    sprintf(filename_out, "file_part_%03d.txt", i);

    new_thread->filename_in = (char*) malloc(25*sizeof(char));
    new_thread->filename_out = (char*) malloc(strlen(filename_out)*sizeof(char));

    


    strcpy(new_thread->filename_in, filename_in);
    strcpy(new_thread->filename_out, filename_out);
    new_thread->id = i;
    new_thread->start_pos = (i-1) * (filesize/N);
    new_thread->end_pos = (i)* (filesize/N);

    printThreadInfo(*new_thread);

    // create a thread
    pthread_create(&thread, NULL, ReadFile, new_thread);
    //pthread_join(thread, NULL);
    

}

pthread_exit(0);

}