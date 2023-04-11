import java.util.Random;

class Main {  
  public static void main(String args[]) { 
    for(int i=-100;i<0;++i){
        Random r = new Random(i);
        System.out.println(r.nextInt(10));
    }
  }
}