#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include<cstring>
#include <bits/stdc++.h>
#include <sys/types.h>
using namespace std;



void copyFile(const char* fileNameFrom, const char* fileNameTo){

    char    buff[BUFSIZ];
    FILE    *in, *out;
    size_t  n;

    in  = fopen(fileNameFrom, "rb");
    out = fopen(fileNameTo, "wb");
    while ( (n=fread(buff,1,BUFSIZ,in)) != 0 ) {
        fwrite( buff, 1, n, out );
    }
}


int main(int argc, char* argv[]){



	copyFile(argv[1],argv[2]);
	
	printf("Done");

    return 0;
}
