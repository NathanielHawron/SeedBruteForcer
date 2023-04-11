import java.util.Random;
import java.lang.Thread;

class Main {  
  public static void main(String args[]) { 
    System.out.println("Hello, world!"); 
    int[] x = {-2, 3, 1,-1,-1, 0, 5, 8, 6, 6};
    int[] z = {-3,-1, 2, 3, 2, 2, 3, 5, 7, 5};
    long threads = (long)Math.pow(2,34);
    long increment = (1L<<63)/threads*2L;
    System.out.print("Increment: ");
    System.out.println(increment);
    for(long i=-threads/2;i<threads/2;++i){
      System.out.print("Thread #: ");
      System.out.print(i);
      System.out.print(". Checking from: ");
      System.out.print(i*increment);
      System.out.print(" to ");
      System.out.println((i+1)*increment);
      findSeedGivenSlimeChunk(i*increment,(i+1)*increment,x,z);
    }
  }
  public static void findSeedGivenSlimeChunk(long min, long max, int[] x, int[] z){
    for(long i=min;i<max;++i){
      boolean passedCheck = true;
      for(int j=0;j<x.length;++j){
        if(!isSlimeChunk(i,x[j],z[j])){
          passedCheck = false;
          break;
        }
      }
      if(passedCheck){
        System.out.print("Found: ");
        System.out.println(i);
      }
    }
  }
  public static boolean isSlimeChunk(long seed, int xPosition, int zPosition){
    Random rnd = new Random(
      seed +
      (int) (xPosition * xPosition * 0x4c1906) +
      (int) (xPosition * 0x5ac0db) +
      (int) (zPosition * zPosition) * 0x4307a7L +
      (int) (zPosition * 0x5f24f) ^ 0x3ad8025f
    );
    return rnd.nextInt(10) == 0;
  }
}