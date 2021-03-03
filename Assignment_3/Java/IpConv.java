import java.util.Scanner;


public class IpConv{

    
    public static String IntegerToString(long ip) {

        String ip_string = String.format("%d.%d.%d.%d", (ip >> 24 & 0xff), (ip >> 16 & 0xff), (ip >> 8 & 0xff), (ip & 0xff));

         return ip_string;
    }




	public static long StringToInteger(String ip_addr) {

        int[] tokens = new int[4];
        String[] parts = ip_addr.split("\\.");

        for ( int i = 0; i < 4; i++ ) {

            tokens[i] = Integer.parseInt(parts[i]);
        }
        
        
		  
		int result = ( ( tokens[0] * 256 + tokens[1] ) * 256 + tokens[2] ) * 256 + tokens[3];
         
		
		return result &  0x00000000ffffffffL;
    
}




     public static void main(String []args) {

        Scanner in = new Scanner(System.in);

        system.out.println("Enter 1 to get Number from IP ");
        system.out.println("Press 2 to get IP from Number ");

        int userInput = in.nextInt();

        if (userInput == 1 ) {


            system.out.println("Enter IP :  ");
            String s = in.nextLine();
            system.out.println(StringToInteger(s));
        
        }


        else if (userInput == 2)
{
            system.out.println("Enter Number : ");
            Long s = in.nextLong();
            system.out.println(IntegerToString(s));
        
}
        
     

}






}