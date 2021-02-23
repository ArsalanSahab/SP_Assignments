#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<cstring>

using namespace std;



int main() {


  // Get IP From User

  char IP[16];

  cout << "Ënter IP" << "\n";

  cin >> IP;

  char *token = strtok(IP, ".");

  int integer[3];


  for(int i=0; i < 4; i++){

    int[i] = atoi(token[i]);
  
  }
  return 0;

    
}