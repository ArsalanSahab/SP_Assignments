#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>

using namespace std;


int ipToBinary(const char *stc)
{  
    char *str = (char*)stc;
    char *token = strtok(str,".");

    unsigned int total = 0;
    int count = 0;

    while ( token != NULL ) {

        int value = stoi(token); 

        if ( count == 0 ) {


            total = total + (value * 256 * 256 * 256 );
            count++;
        }

        else if ( count == 1 ) {

            total = total + (value * 256 * 256);
            count++;

        }


        else if ( count == 2 ) {


            total = total + (value*256);
            count++;

        }


        else if ( count == 3 ) {

            total = total + value;
            break;

        }
        

        token = strtok(NULL,".");
    }

    return total;
    
}



unsigned char* ipGetter( unsigned int ip, unsigned char bytes[] )

{

    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;   
    
	return bytes;
	
}



int main()

{  

            string ip;
            string subnet;

            printf("Enter IP address : \n");
            getline (cin, ip);

            printf("Enter Subnet Mask : \n");
            getline (cin, subnet);

            unsigned int ipBinary = ipToBinary( ip.c_str() );
            unsigned int subnetBinary = ipToBinary( subnet.c_str() );
            unsigned int netID = ipBinary & subnetBinary;
            
            unsigned char *net;
            unsigned char bytes[4];
            net = ipGetter(netID,bytes);
            
            printf("Network IP : %d.%d.%d.%d \n", net[3], net[2], net[1], net[0]);
            net = ipGetter(subnetBinary,bytes);

            int tot_addr = 0;
            int octet1 = 256-((int)net[0]);
            int octet2 = 256-((int)net[1]);
            int octet3 = 256-((int)net[2]);
            int octet4 = 256-((int)net[3]);
            tot_addr = octet1;

            if ( octet2 != 0 ) {

                tot_addr = tot_addr*(octet2);
            }

            if ( octet3 != 0 ) {

                tot_addr = tot_addr*(octet3);
            }

            if ( octet4 != 0 ) {

                tot_addr = tot_addr*(octet4);
            }

            unsigned int broadcastAddr = netID + tot_addr;
            int range = broadcastAddr - netID;
            

            netID = netID+1;
            net = ipGetter(netID,bytes);

            printf("Gateway : %d.%d.%d.%d \n", net[3], net[2], net[1], net[0]);

            netID = netID+1;
            net = ipGetter(netID,bytes);

            for ( int i = 2;i < range-1;i++ ) {

                printf("%d.%d.%d.%d \n", net[3], net[2], net[1], net[0]);
                netID = netID+1;
                net = ipGetter(netID,bytes);

            }

            printf("Broadcast Address : %d.%d.%d.%d\n", net[3], net[2], net[1], net[0]);
            
            
        
      
			return 0;

    
    
    
}