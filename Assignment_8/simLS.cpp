#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

static char *root = ".";
static char* buff = (char*)malloc(60000*sizeof(char));

struct stat get_stats(const char *filename)
{
    char path[1024];
    sprintf(path, "%s/%s", root, filename);
    struct stat sb;

    if (lstat(path, &sb) < 0)
    {
        perror(path);
        exit(1);
    }

    return sb;
}

void print_filetype(mode_t mode)
{
    switch (mode & S_IFMT)
    {
    case S_IFREG:
        sprintf(buff + strlen(buff), "-");
        break;
    case S_IFDIR:
        sprintf(buff + strlen(buff), "d");
        break;
    case S_IFLNK:
        sprintf(buff + strlen(buff), "l");
        break;
    case S_IFCHR:
        sprintf(buff + strlen(buff), "c");
        break;
    case S_IFBLK:
        sprintf(buff + strlen(buff), "b");
        break;
    case S_IFSOCK:
        sprintf(buff + strlen(buff), "s");
        break;
    case S_IFIFO:
        sprintf(buff + strlen(buff), "f");
        break;
    }
}

bool is_dir(const char *path)
{
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

void print_permissions(mode_t mode)
{
    if (mode & S_IRUSR) 
        sprintf(buff + strlen(buff), "r");
    else 
        sprintf(buff + strlen(buff), "-");
    
    if (mode & S_IWUSR)
        sprintf(buff + strlen(buff), "w");
    else 
        sprintf(buff + strlen(buff), "-");
    
    if (mode & S_IXUSR) 
        sprintf(buff + strlen(buff), "x");
    else 
        sprintf(buff + strlen(buff), "-");
    
    if (mode & S_IRGRP) 
        sprintf(buff + strlen(buff), "r");
    else 
        sprintf(buff + strlen(buff), "-");
    
    if (mode & S_IWGRP) 
        sprintf(buff + strlen(buff), "w");
    else 
        sprintf(buff + strlen(buff), "-");
    
    if (mode & S_IXGRP) 
        sprintf(buff + strlen(buff), "x");
    else 
        sprintf(buff + strlen(buff), "-");
    
    if (mode & S_IROTH) 
        sprintf(buff + strlen(buff), "r");
    else 
        sprintf(buff + strlen(buff), "-");
    
    if (mode & S_IWOTH) 
        sprintf(buff + strlen(buff), "w");
    else 
        sprintf(buff + strlen(buff), "-");
    
    if (mode & S_IXOTH) 
        sprintf(buff + strlen(buff), "x");
    else 
        sprintf(buff + strlen(buff), "-");
}

void print_time(time_t mod_time)
{
    time_t curr_time;
    time(&curr_time);
    struct tm *t = localtime(&curr_time);
    const int curr_mon = t->tm_mon;
    const int curr_yr = 1970 + t->tm_year;

    t = localtime(&mod_time);
    const int mod_mon = t->tm_mon;
    const int mod_yr = 1970 + t->tm_year;

    const char *format = ((mod_yr == curr_yr) && (mod_mon >= (curr_mon - 6)))
                             ? "%b %e %H:%M"
                             : "%b %e  %Y";

    char time_buf[128];
    strftime(time_buf, sizeof(time_buf), format, t);
    sprintf(buff + strlen(buff), "%s ", time_buf);
}

void lsLprint(char *dir, char *filename)
{
    root = dir;
    struct stat sb = get_stats(filename);

    print_filetype(sb.st_mode);
    print_permissions(sb.st_mode);
    sprintf(buff + strlen(buff), " %d ", sb.st_nlink);
    sprintf(buff + strlen(buff), "%10s ", getpwuid(sb.st_uid)->pw_name);
    sprintf(buff + strlen(buff), "%10s", getgrgid(sb.st_gid)->gr_name);
    sprintf(buff + strlen(buff), "%10ld ", (long)sb.st_size);
    print_time(sb.st_mtime);
}

void ls(char *name, int indent, int R, int a, int l)
{
    DIR *dir;
    struct dirent *entry;
    struct passwd *pw;
    struct group *gp;
    struct stat fs;
    char *c;
    dir = opendir(name);

    if (dir == NULL)
    {
        sprintf(buff,"");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (entry->d_name[0] == '.')
        {
            if (a == 0)
                continue;
        }
        if (entry->d_type == DT_DIR)
        {
            char path[1024];

            snprintf(path, sizeof(path), "%s%s/", name, entry->d_name);
            if (l == 1)
                lsLprint(name, entry->d_name);
            sprintf(buff + strlen(buff), "%*s[%s]\n", indent, "", entry->d_name);

            if (R == 1)
                ls(path, indent + 2, R, a, l);
        }
        else
        {
            if (l == 1)
                lsLprint(name, entry->d_name);
            sprintf(buff + strlen(buff), "%*s| - %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

char* customSim(string input)
{
    char str[100];
    strcpy(str, input.c_str());
    char delim[] = " ";
    int lbit = 0, Rbit = 0, abit = 0;
    char *location = NULL;
    vector<char *> command;

    char *ptr = strtok(str, delim);
    command.clear();

    while (ptr != NULL)
    {
        command.push_back(ptr);
        ptr = strtok(NULL, delim);
    }

    int limit = 0;

    if (strcmp(command[0], "ls") != 0)
    {
        sprintf(buff, "Known Command: 'ls' with parameter: 'a', 'l' , 'R'.\n");
        return buff;
    }
    if (command[command.size() - 1][0] != '-' && command.size() > 1)
    {
        location = command[command.size() - 1];
        limit = command.size() - 1;
    }
    else
        limit = command.size();
    for (size_t i = 1; i < limit; i++)
    {
        string temp = command[i];
        if (temp[0] != '-' || temp.length() == 1)
        {
            sprintf(buff, "Please enter correct parameters.\n");
            return buff;
        }
        else
        {
            temp = temp.substr(1, temp.length() - 1);
            for (int j = 0; j < temp.length(); j++)
            {
                if (temp[j] != 'a' && temp[j] != 'R' && temp[j] != 'l')
                {
                    sprintf(buff, "I only know ls command with a, R, and l as optional arguments.\n");
                    return buff;
                }
                else
                {
                    if (temp[j] == 'a')
                        abit = 1;
                    if (temp[j] == 'R')
                        Rbit = 1;
                    if (temp[j] == 'l')
                        lbit = 1;
                }
            }
        }
    }

    if (location != NULL)
    {
        string check = location;
        if (check.back() != '/') {
            check.append("/");
            strcpy(location, check.c_str());
        }
        sprintf(buff,"[%s]\n", location);
        ls(location, 0, Rbit, abit, lbit);
    }
    else
    {
        sprintf(buff, "[./]\n");
        ls("./", 0, Rbit, abit, lbit);
    }

    return buff;

}