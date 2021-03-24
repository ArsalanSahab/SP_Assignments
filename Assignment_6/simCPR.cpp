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

int dir(std::string path){

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) { /* print all the files and directories within directory */
            if (ent->d_name != std::string(".")){          //REMOVE PWD
                if (ent->d_name != std::string("..")){     //REMOVE PARENT DIR

                    std::cout << path << ent->d_name << std::endl;

                }
            }
        }

        std::cout << std::endl;

        closedir (dir);
    }else{
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    return 0;
}


int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}


int copyAllFiles(string sorc, string dest){

    DIR *dir;
    struct dirent *ent;
	 string sorcPath = sorc;
	string destPath = dest;
    if ((dir = opendir (sorc.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) { /* print all the files and directories within directory */
            if (ent->d_name != std::string(".")){          //REMOVE PWD
                if (ent->d_name != std::string("..")){

							
						
						cout << "Source Path : " << sorcPath << endl;
						cout << "Destination Path : " << destPath << endl; 
						
     					
						sorcPath = sorcPath + ent->d_name;
                    destPath = destPath + ent->d_name;

						
						if (isDirectory(sorcPath.c_str())) {
						
						
								cout << sorcPath << " is a Folder " << endl;
								
								// Create Direcotry on dest path
								
								if (mkdir(destPath.c_str(), 0777) == -1) {
								
									cerr << "Error :  " << strerror(errno) << endl;
								
								}
        
  
    else {

		cout << "Directory created " << endl;


}
        
						sorcPath = sorcPath + "/";
						destPath = destPath + "/";



						copyAllFiles(sorcPath.c_str(),destPath.c_str());


						sorcPath = sorc;
						destPath = dest;
						
						}
						
						
						else {
						
						cout << "Copying From : " << sorcPath << " to " << destPath << endl;

                    copyFile(sorcPath.c_str(), destPath.c_str());

	                 sorcPath = sorc;
                    destPath = dest;

						
						
						
						}

						

                    

			


                }
            }
        }

        std::cout << std::endl;

        closedir (dir);
    }else{
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    return 0;
}

int main(int argc, char* argv[]){

    //dir("C:\\example");                           //SHOWS CONTENT IN FOLDER
    copyAllFiles(argv[1], argv[2]); //COPY FOLDER'S CONTENT


    return 0;
}