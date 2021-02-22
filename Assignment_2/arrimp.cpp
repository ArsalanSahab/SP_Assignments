#include <stdio.h> 
#include <stdlib.h> 

// Array Implementation using malloc and new


int main() {


// Size Initialisation

int row = 5, column = 5;
int size = 5;


// malloc Implementation : One Dimensional


int *mallocArray = (int *)malloc(size * sizeof(int));

for (int i = 0; i < size; i++) {

		mallocArray[i] = i * 5;
}

for (int i = 0; i < size; i++) {

		printf("%d",mallocArray[i]);
}


// malloc Implementation : Two Dimensional

    int *mallocArr = (int *)malloc(row * column * sizeof(int)); 
  
    int i, j, count = 0; 

    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         *(mallocArr + i*c + j) = ++count; 
  
    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         printf("%d ", *(mallocArr + i*c + j));


// new Implementation : One Dimensioanl 

int *newArray = new int();

for (int i = 0; i < size; i++) {

		newArray[i] = i * 5;
}

for (int i = 0; i < size; i++) {

		printf("%d",newArray[i]);
}

// new Implementation : Two Dimensional

int* newArr = new int[row * column]; 
  
    
for (int i = 0; i < row; i++) { 
        for (int j = 0; j < column; j++) { 
  
             
            *(newArr + i * column + j) = ++count; 
        } 
    } 
  
for (int i = 0; i < row; i++) { 
        for (int j = 0; j < column; j++) { 
  
            printf("%d", *(newArr + i * column + j));
        } 
    } 

}