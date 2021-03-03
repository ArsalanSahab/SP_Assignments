public class IPGen {

    

    public static String IntegerToString(int[] int_ip) {

        String str_ip = int_ip[0] + "." + int_ip[1] + "." + int_ip[2] + "." + int_ip[3];
        return str_ip;

    }



    public static int[] StringToInteger(String str_ip) {

        String[] split_str = str_ip.split("\\.");
        int[] token = new int[split_str.length];

        for (int i = 0; i < split_str.length; i++) {

            token[i] = Integer.parseInt(split_str[i]);
        }

        return token;

    }



    
    public static int[] BinaryToInteger(int[][] bin_int) {

        int[] int_bin = new int[4];
        int sum = 0;

        for (int i = 0; i < 4; i++) {

            sum = 0;

            for (int j = 0; j < 8; j++) {

                sum += bin_int[i][j]  * Math.pow(2, 7 - j);
            }

            int_bin[i] = sum;

        }

        return int_bin;

    }

    


	public static int[][] IntegerToBinary(int[] int_bin) {
	
        int[][] bin_int = new int[4][8];
    
        for (int i = 0; i < 4; i++) {

            int temp[] = new int[8];
            temp[0] = 0; temp[1] = 0; temp[2] = 0; temp[3] = 0; temp[4] = 0; temp[5] = 0; temp[6] = 0; temp[7] = 0;
            int temp = int_bin[i];

            for (int k = 0; temp_2 > 0; k++) {

                temp[7 - k] = temp_2 % 2;
                temp_2 /= 2;
            }

            for (int j = 0; j < 8; j++) {

                bin_int[i][j] = temp[j];
            }
        }
        
        return bin_int;
    }





    public static int[] Finder(int[] arr) {

        if (arr[0] == 255 && arr[1] == 255 && arr[2] == 255 && arr[3] == 255) {

            return arr;
        }

        else if (arr[1] == 255 && arr[2] == 255 && arr[3] == 255) {

            arr[0] += 1;
            return arr;
        }

        else if (arr[2] == 255 && arr[3] == 255) {

            arr[1] += 1;
            return arr;
        }

        else if (arr[3] == 255) {

            arr[2] += 1;
            return arr;

        }

        else {

            arr[3] += 1;
            return arr;

        }

    }





    public static int count(String s) {
        int[] x = StringToInteger(s);
        int[][] b = IntegerToBinary(x);
        int c = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (b[i][j] == 0) c++;
            }
        }
        return (int) Math.round(Math.pow(2, c) - 2);
    }






    public static void main(String[] args) {
        String ip = "192.168.100.1";
        String sub = "255.255.255.0";
        
        int[][] ipBin = IntegerToBinary(StringToInteger(ip));
        int[][] subnetMaskBin = IntegerToBinary(StringToInteger(sub));
        int[][] netAdd = new int[4][8];

        for (int i = 0; i < 4; i++) {

            for (int j = 0; j < 8; j++) {

                if (ipBin[i][j] == 1 && subnetMaskBin[i][j] == 1) netAdd[i][j] = 1;
                else netAdd[i][j] = 0;

            }
        }

        int[] netAddInt = BinaryToInteger(netAdd);
        int hosts = count(sub);

        int[] next = Finder(netAddInt);
        System.out.println("Gateway : " + IntegerToString(gateway));
    
        for (int i = 1; i < hosts; i++) {
            next = Finder(next);
            System.out.println("Hosts_Number  " + (i + 1) + ": " + IntegerToString(next));
        }
        int[] broadcast = Finder(next);
        
        System.out.println("\n Broadcast Address : " + IntegerToString(broadcast));
    }
}