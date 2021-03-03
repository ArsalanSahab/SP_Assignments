public class AddrTrans{

  
   // Global NAT Table

    public static String[][] nat_table = {

      {"Machine0","01.AB.55.ZA.00.01","192.168.100.1"},
      {"Machine1","02.AC.56.ZB.00.02","192.168.100.2"},
      {"Machine2","03.AD.57.ZC.00.03","192.168.100.3"},
      {"Machine3","04.AE.58.ZD.00.04","192.168.100.4"},
      {"Machine4","05.AF.58.ZE.00.05","192.168.100.5"}
    };

    public static String MachineToIP(String name) {

        for (int i = 0; i < nat_table.length; i++) {

            if (name == nat_table[i][0]) return nat_table[i][2];
        }

        return "Not in Table";
    }


    
    public static String IPToMachine(String ip) {

        for (int i = 0; i < nat_table.length; i++) {

            if (ip == nat_table[i][2]) return nat_table[i][0];
        }

        return "Not in Table";
    }


    
    
    public static String IPToMAC(String ip) {

        for (int i = 0; i < nat_table.length; i++) {

            if (ip == nat_table[i][2]) return nat_table[i][1];
        }

        return "Not in Table";
    }    



    public static String MACToIP(String mac) {

        for (int i = 0; i < nat_table.length; i++) {

            if (mac == nat_table[i][1]) return nat_table[i][2];
        }

        return "Not in Table";
    } 


    
    public static void main(String[] args) {


		 String ip_addr = "Enter IP Address";
		 System.out.println(IPToMachine(ip_addr));
		 System.out.println(IPToMAC(ip_addr));



        String machine_name = "Enter Machine Name ";
        System.out.println(MachineToIP(machine_name));
       
        String mac_addr = "Enter MAC Address";
		 System.out.println(MACToIP(mac_addr));

    }




}