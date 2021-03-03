#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;


// NAT Table

struct natTable
{
    string machineName;
    string ipAddr;
    string macAddr;
};


int tableSize = 10;


// Machine to IP

void machineToIP(natTable Table[]) {


	string userMachineName;
	
	
    printf("Enter Machine Name : \n");
    getline(cin, userMachineName);
            
    for ( int i = 0; i < tableSize; i++ ) {


       if( strcmp( userMachineName.c_str() , Table[i].machineName.c_str() ) == 0 ) {

				printf("IP Address for this Machine is : %s\n", Table[i].ipAddr.c_str() );
            

    	}
            
        
	
	}
	

}




void ipToMachine(natTable Table[]) {


		char userIP[50];
		
       printf("Enter IP address: \n");
       scanf("%s", userIP);


       for( int i = 0; i < tableSize; i++) {


            if( strcmp(userIP, Table[i].ipAddr.c_str() ) == 0 ) {

                printf("Machine Name for Entered IP : %s\n", Table[i].machineName.c_str() );
                break;
            

      }
            

  }

}
void ipToMAC(natTable Table[]) {



		char userIP[50];
		
       printf("Enter IP address: \n");
       scanf("%s", userIP);

       for( int i = 0 ; i < tableSize; i++ ) {


            if( strcmp(userIP, Table[i].ipAddr.c_str() ) == 0 ) {


                    printf("MAC Address for Entered IP : %s\n", Table[i].macAddr.c_str() );
                    break;
                }
            }

}


void macToIP(natTable Table[]) {



			char userMAC[50];
			
          printf("Enter MAC Address: \n");
          scanf("%s", userMAC);

          for( int i = 0; i < tableSize; i++ ) {


               if( strcmp(userMAC, Table[i].macAddr.c_str() ) == 0 ) {


                    printf("IP for Entered MAC Address is : %s\n", Table[i].ipAddr.c_str() );
                    break;
                }
            }

}



int main(void)
{   

	// Table Population
	
	
	natTable Table[tableSize];

    

    for( int i = 0 ; i < tableSize; i++ ) {

        Table[i].ipAddr = "192.168.100."+to_string(i);
        Table[i].macAddr = "00:12:AA:B6:05:"+to_string(i);
        Table[i].machineName = "machine_"+to_string(i);


    }


	// Display Menu 
	
	
	while(1) {
	
	
		int userInput = 0;
		
		printf("Enter 1 to get IP from Machine Name \n");
		printf("Enter 2 to get Machine Name From IP \n");
		printf("Enter 3 to get MAC Address from IP \n");
		printf("Enter 4 to IP from MAC Address \n");
		
		scanf("%i", &userInput);
		fflush(stdin);
		
		
		
		if ( userInput == 1 ) {
		
		
		
				// Call Function Machine to IP
				machineToIP(Table);
		
		}
		
		else if ( userInput == 2 ) {
		
		
		
				// Call Fucntion IP to Machine
				
				ipToMachine(Table);
		
		
		}
		
		
		else if ( userInput == 3 ) {
		
		
		
				// Call Function IP to MAC 
				
				ipToMAC(Table);
				
		
		
		}
		
		
		else if ( userInput == 4 ) {
		
		
		
				// Call Function MAC to IP
				macToIP(Table);
		
		}
		
		else {
		
		
			return 0;
		
		}
	
	
	
	
	
	}


}




