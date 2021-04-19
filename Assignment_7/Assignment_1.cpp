#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


string simCommands(int argc, vector<string> argv){

string command = (string)argv.at(0);
string pramma = (string)argv.at(1);
const char *comm = command.c_str();


const char *pramm= pramma.c_str();


string res = "";


    if (strcmp(comm, "ls") == 0){
        
        res = "ls is a Linux shell command that lists directory contents of files and directories.\n";
        
        if (strcmp(pramm, "-a")==0){
            res = res + "\nParameter %s: %s" +pramm +"To show all the hidden files in the directory";
        }
        
        else if (strcmp(pramm, "-l")==0){
            res = res + "\nParameter %s: %s" + pramm + "To show long listing information about the file/directory";
        }

        else if (strcmp(pramm, "-r")==0){
            res = res + "\nParameter %s: %s "+ pramm +"To show The File Listing In Reverse Order";
        }

        else if (strcmp(pramm, "-C")==0){
            res = res + "\nParameter %s: %s "+ pramm +"To show The File Listing by columns";
        }
        
        else if (strcmp(pramm, "-d")==0){
            res = res + "\nParameter %s: %s "+ pramm +"To show The File directory Listing only";
        }
        
        else 
        res = res + "Unknown parameter";
        

    }

//_________________________________2c_________________________________

    else if (strcmp(comm, "cp") == 0){
            
            res = " cp - copy files and directories";
            
            if (strcmp(pramm, "-i")==0){
                res = res + "\nParameter %s: %s "+ pramm +"With this option system first warns the user before overwriting the destination file. cp prompts for a response. if you press y then it overwrites the file and with any other option leave it uncopied";
            }
            
            else if (strcmp(pramm, "-b")==0){
                res = res + "\nParameter %s: %s "+ pramm +"create the backup of the destination file in the same folder with the different name and in different format.";
            }

            else if (strcmp(pramm, "-f")==0){
                res = res + "\nParameter %s: %s "+ pramm +"Destination file is deleted first and then copying of content is done from source to destination file.";
            }

            else if (strcmp(pramm, "-r")==0){
                res = res + "\nParameter %s: %s "+ pramm +"Copying directory structure";
            }
            
            else if (strcmp(pramm, "-p")==0){
                res = res + "\nParameter %s: %s "+ pramm +"the following characteristics of each source file in the corresponding destination file:the time of the last data modification and the time of the last access, the ownership (only if it has permissions to do this), and the file permission-bits.";
            }
            
            else 
            res = res + "\nUnknown parameter";
            

        }

//_________________________________3c_________________________________

    else if (strcmp(comm, "rm") == 0){
            
            res = " rm command is used to remove objects such as files, directories, symbolic links and so on from the file system. By default, it does not remove directories. ";
            
            if (strcmp(pramm, "-i")==0){
                res = res + "\nParameter %s: %s "+ pramm +"makes the command ask the user for confirmation before removing each file, you have to press y for confirm deletion, any other key leaves the file un-deleted.";
            }
            
            else if (strcmp(pramm, "-f")==0){
                res = res + "\nParameter %s: %s "+ pramm +"prompts for confirmation removal if a file is write protected. The -f option overrides this minor protection and removes the file forcefully.";
            }

            else if (strcmp(pramm, "-r")==0){
                res = res + "\nParameter %s: %s "+ pramm +"performs a tree-walk and will delete all the files and sub-directories recursively of the parent directory. At each stage it deletes everything it finds.";
            }

            else if (strcmp(pramm, "--version")==0){
                res = res + "\nParameter %s: %s "+ pramm +"This option is used to display the version of rm which is currently running on your system.";
            }
            
            else if (strcmp(pramm, "-d")==0){
                res = res + "\nParameter %s: %s "+ pramm +"remove empty directories";
            }
            
            else 
            res = res + "\nUnknown parameter";
            

        }

//_________________________________4c_________________________________

    else if (strcmp(comm, "mkdir") == 0){
            
            res = " mkdir command in Linux allows the user to create directories";
            
            if (strcmp(pramm, "--version")==0){
                res = res + "\nParameter %s: %s "+ pramm +"Display the version number, some information regarding the license and exits.";
            }
            
            else if (strcmp(pramm, "--help")==0){
                res = res + "\nParameter %s: %s "+ pramm +"It displays the help related information and exits";
            }

            else if (strcmp(pramm, "-v")==0){
                res = res + "\nParameter %s: %s "+ pramm +"It displays a message for every directory created";
            }

            else if (strcmp(pramm, "-p")==0){
                res = res + "\nParameter %s: %s "+ pramm +"A flag which enables the command to create parent directories as necessary. If the directories exist, no error is specified.";
            }
            
            else if (strcmp(pramm, "-m")==0){
                res = res + "\nParameter %s: %s "+ pramm +"This option is used to set the file modes, i.e. permissions, etc. for the created directories. The syntax of the mode is the same as the chmod command.";
            }
            
            else 
            res = res + "\nUnknown parameter";
            

        }

//_________________________________5c_________________________________

    else if (strcmp(comm, "rmdir") == 0){
            
            res = " rmdir - remove empty directories";
            
            if (strcmp(pramm, "--ignore-fail-on-non-empty")==0){
                res = res + "\nParameter %s: %s "+ pramm +"ignore each failure that is solely because a directory is non-empty";
            }
            
            else if (strcmp(pramm, "-p")==0){
                res = res + "\nParameter %s: %s "+ pramm +"remove DIRECTORY and its ancestors";
            }

            else if (strcmp(pramm, "-v")==0){
                res = res + "\nParameter %s: %s "+ pramm +"output a diagnostic for every directory processed";
            }

            else if (strcmp(pramm, "--help")==0){
                res = res + "\nParameter %s: %s "+ pramm +"display this help and exit";
            }
            
            else if (strcmp(pramm, "--version")==0){
                res = res + "\nParameter %s: %s "+ pramm +"output version information and exit";
            }
            
            else 
            res = res + "\nUnknown parameter";
            

        }

//_________________________________6c_________________________________

    else if (strcmp(comm, "pwd") == 0){
            
            res = " pwd - print name of current/working directory";
            
            if (strcmp(pramm, "-L")==0){
                res = res + "\nParameter %s: %s "+ pramm +"use PWD from environment, even if it contains symlinks";
            }
            
            else if (strcmp(pramm, "-P")==0){
                res = res + "\nParameter %s: %s "+ pramm +" avoid all symlinks";
            }

            else if (strcmp(pramm, "--help")==0){
                res = res + "\nParameter %s: %s "+ pramm +"display this help and exit";
            }

            else if (strcmp(pramm, "--version")==0){
                res = res + "\nParameter %s: %s "+ pramm +" output version information and exit";
            }
            
            else 
            res = res + "\nUnknown parameter";
            

        }

//_________________________________7c_________________________________

    else if (strcmp(comm, "cd") == 0){
            
            res = " cd command in linux known as change directory command. It is used to change current working directory.";
            res =  "It accepts no parameters";
            /*if (cmpstr(pramm,"") < 0)
            {
                res =  "This accepts no Parameters";
            }
              */          
        }

//_________________________________8c_________________________________

    else if (strcmp(comm, "mv") == 0){
            
            res = "It is a move command used to move file(s) from one directory to another or is used to rename file or folder.";
            
            if (strcmp(pramm, "-i")==0){
                res = res + "\nParameter %s: %s "+ pramm +"the command ask the user for confirmation before moving a file that would overwrite an existing file, you have to press y for confirm moving, any other key leaves the file as it is. This option doesn’t work if the file doesn’t exist, it simply rename it or move it to new location.";
            }
            
            else if (strcmp(pramm, "-f")==0){
                res = res + "\nParameter %s: %s "+ pramm +"prompts for confirmation overwriting the destination file if a file is write protected. The -f option overrides this minor protection and overwrite the destination file forcefully and delete the source file.";
            }

            else if (strcmp(pramm, "-n")==0){
                res = res + "\nParameter %s: %s "+ pramm +"mv prevent an existing file from being overwritten.";
            }

            else if (strcmp(pramm, "-b")==0){
                res = res + "\nParameter %s: %s "+ pramm +"With this option it is easier to take a backup of an existing file that will be overwritten";
            }
            
            else if (strcmp(pramm, "--version")==0){
                res = res + "\nParameter %s: %s "+ pramm +" output version information and exit";
            }
            
            else 
            res = res + "\nUnknown parameter";
            

        }

//_________________________________9c_________________________________

    else if (strcmp(comm, "help") == 0){
            
            res = "It is used to display the whole user manual of command given in its parameters";
            
            if (strcmp(pramm, "-d")==0){
                res = res + "\nParameter %s: %s "+ pramm +"output short description for each topic";
            }
            
            else if (strcmp(pramm, "-m")==0){
                res = res + "\nParameter %s: %s "+ pramm +"display usage in pseudo-manpage format";
            }

            else if (strcmp(pramm, "-s")==0){
                res = res + "\nParameter %s: %s "+ pramm +"output only a short usage synopsis for each topic matching PATTERN";
            }
            
            else 
            res = res + "\nUnknown parameter";
            
        }

//_________________________________10nc_________________________________

    else if (strcmp(comm, "man") == 0){
            
            res = "man - an interface to the system reference manuals";
            
            if (strcmp(pramm, "-f")==0){
                res = res + "\nParameter %s: %s "+ pramm +" One may not be able to remember the sections in which a command is present. So this option gives the section in which the given command is present.";
            }
            
            else if (strcmp(pramm, "-a")==0){
                res = res + "\nParameter %s: %s "+ pramm +"This option helps us to display all the available intro manual pages in succession.";
            }

            else if (strcmp(pramm, "-k")==0){
                res = res + "\nParameter %s: %s "+ pramm +"This option searches the given command as a regular expression in all the manuals and it returns the manual pages with the section number in which it is found.";
            }

            else if (strcmp(pramm, "-w")==0){
                res = res + "\nParameter %s: %s "+ pramm +"This option returns the location in which the manual page of a given command is present.";
            }
            
            else if (strcmp(pramm, "-I")==0){
                res = res + "\nParameter %s: %s "+ pramm +" It considers the command as case sensitive";
            }
            
            else 
            res = res + "\nUnknown parameter";
            

        }

    else 
        res = "Unknown command!!";
//____________________________________________________________

    return res;
}
