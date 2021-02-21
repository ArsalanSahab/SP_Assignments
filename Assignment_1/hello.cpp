
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<vector>

using namespace std;

int main( int argc, char** argv )
{
   
   cout << "You have entered : " << argc << "\n";

   // String Manipulation

   std::string arg1(argv[1]);
   arg1 = arg1 + " --help";
   const char* out = arg1.c_str();

   // For Loop

   for (int i = 0; i < argc; ++i) {

      cout << argv[i] << "\n\n";
   }

   // Terminal Executor

   cout << "Documentation For : " << argv[1] << "\n";
   system(out);
   
   return 0;
}