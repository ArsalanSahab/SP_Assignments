#include <iostream>
#include <string.h>
#include <cmath>


using namespace std;




void ipToUnsg() {



	
	char ip[100];
	unsigned long uIP = 0; int index = 0; int count = 3;


	printf("Enter the IP Address: \n");
   scanf("%s", ip);




    char *key = strtok(ip,".");

    while(key != NULL){


        int converter = stoi(key);

        if(index == 0 || index == 1 || index == 2) {


            uIP = uIP + (converter * pow(256,count));
            count--;
            index++;


        }


        else if(index = 3){

            uIP = uIP + (converter * pow(256,count));
            count--;
            break;
 
        }

        key = strtok(NULL,".");
    }
            
    
    printf("Integer Value for Entered IP = %lu\n", uIP);
   



}



void unsgToIP() {



	 unsigned long ipU = 0;	
	 unsigned int ipU_1,ipU_2,ipU_3,ipU_4;

    printf("Enter the unsigned integer: \n");
	 scanf("%lu",&ipU);


    ipU_4 = (ipU%256);
    ipU_3 = (ipU/256)%256;
    ipU_2 = ((ipU/(256*256))%256);
    ipU_1 = ((ipU/(256*256*256))%256);

    printf("IP Address for Entered Integer = %d.%d.%d.%d \n", ipU_1,ipU_2,ipU_3,ipU_4);
    


}


int main(void)


{
   
	ipToUnsg();
	unsgToIP();
	
    return 0;
    
}
