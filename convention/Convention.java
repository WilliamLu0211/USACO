import java.util.ArrayList;
import java.io.*;

class Bus {

  private int[] arriveTimes;
  private int size;

  public Bus(int s){
    arriveTimes = new int[s];
    size = 0;
  }

  public boolean isFilled(){
    return size == arriveTimes.length;
  }

  public void addCow(int t){
    arriveTimes[size] = t;
    size ++;
  }

  public int maxWaitTime(){
    int min = arriveTimes[0], max = arriveTimes[0];
    for (int i : arriveTimes){
      if (i > max)
        max = i;
      if (i < min)
        min = i;
    }
    return max - min;
  }

}

public class Convention {

  private static void swap(int[] arr, int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
  }

  private static void sort(int[] arr){
    int j;
    for (int i = 1; i < arr.length; i ++){
      j = i;
      while (j != 0 && arr[j] < arr[j - 1]){
        swap(arr, j, j - 1);
        j --;
      }
    }
  }

  private static int getMax(int[] cows, ArrayList<Bus> busses){
    int max = 0;
    int piece;
    int i = 0;
    for (int t : cows){
      if ( busses.get(i).isFilled() )
        i ++;
      busses.get(i).addCow(t);
    }
    for (Bus b : busses){
      piece = b.maxWaitTime();
      if (piece > max)
        max = piece;
    }
    return max;
  }

  public static void main(String[] args) {
    File f = new File("convention.in");
    FileReader fr = new FileReader(f);
    char[] buf = new char[99999];
    fr.read(buf);
    String str = new String(buf);

    String[] lines = str.split("\n");
    String[] nums = lines[0].split(" ");
    int[] cows = new int[Integer.parseInt(nums[0])];
    sort(cows);
    ArrayList<Bus> busses = new ArrayList();
    for (int i = 0; i < Integer.parseInt(nums[1]); i ++){
      busses.add( new Bus(Integer.parseInt(nums[2])) );
    }

    int max = getMax(cows, busses);

    f = new File("convention.out");
    f.createNewFile();
    PrintWriter p = new PrintWriter(f);
    p.println(max);

  }


}
