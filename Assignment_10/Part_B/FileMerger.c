#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


// Globals 

int N;


// Strcuture to Record Information of Each Thread Created

typedef struct myThread {
int id; // Id of the thread
char* filename_in; // file to read from
char* filename_out; // file to write to
} myThread;


// Function to Print out the details of the current thread created
void ThreadDetails(myThread new_thread) {
printf(" Thread %d [ filename_in : %s, filename_out : %s]\n",
new_thread.id, new_thread.filename_in, new_thread.filename_out);
}

// Main Function to FileReader and Split

void *FileReader(void* arg) {

// New Thread Initialisation
myThread *tinfo = (myThread*) arg;

printf("T%d : STARTING\n", tinfo->id); // print current thread details

FILE* fp = fopen(tinfo->filename_in, "r");



do {

    char *line;
    size_t lsize = 0;

    getline(&line, &lsize, fp); // read a line


    FILE* fout = fopen(tinfo->filename_out, "a+");
    fwrite(line, 1, sizeof(line), fout);
    fclose(fout);



} while(feof(fp));

fclose(fp);

printf("T%d : HALTING\n", tinfo->id); 

}




int FileMerger() {



 char filename_in[20];
 char* filename_out = "file_out.txt";


for(int i = 1; i <= N; i++) {

    pthread_t thread;
    myThread *new_thread = (myThread*)malloc(sizeof(myThread));
    
    sprintf(filename_in, "file_part_%03d.txt", i);

    new_thread->filename_in = (char*) malloc(25*sizeof(char));
    new_thread->filename_out = (char*) malloc(strlen(filename_out)*sizeof(char));


    strcpy(new_thread->filename_in, filename_in);
    strcpy(new_thread->filename_out, filename_out);
    new_thread->id = i;
   

    ThreadDetails(*new_thread);

    // create a thread
    pthread_create(&thread, NULL, FileReader, new_thread);
    pthread_join(thread, NULL);
    

}

pthread_exit(0);


}


// Driver function
int main() {


    printf("Running File Merger! \n");

    // read the number of threads
    printf("Enter the Number of threads :");
    scanf("%d", &N);

    FileMerger();


   
}