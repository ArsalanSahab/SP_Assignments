import java.io.*;

public class task_2 {

    public static void swapByValue(int x, int y){

        int swap = x;
        x = y;
        y = swap;
    }   


    public static void swapByReference(IntWrapper x, IntWrapper y) {

    IntWrapper swap = new IntWrapper(x.x);
      x.x = y.x;
      y.x = swap.x;
    }

    public static void main(String[] args) {
    
    // Swap by Value

      int x = 35;
      int y = 25;
      System.out.println("Before swapping, x = " + x + " and y = " + y);
      
      swapByValue(x, y);
      
      System.out.println("After swapping, x = " + x + " and y is " + y);

    // Swap ByRefrence 
    
      IntWrapper x = new IntWrapper(30);
      IntWrapper y = new IntWrapper(45);
     
      System.out.println("Before swapping, x = " + x.x + " and y = " + y.x);
    
      swapByReference(x, y);
      
      System.out.println("After swapping, x = " + x.x + " and b is " + y.x);
   }
}

class IntWrapper {
   public int x;
   public IntWrapper(int x){ this.x = x;}
}