import java.util.Scanner;

public class Exercicio4 {
  static double somar(double a, double b) {
    return a + b;
  }
  static int FAT(int x){
    int res = 1;
    for(int i=x; i >= 1; i--){
      res = res * i;
    }

    return res;
  }
  static int FATR(int x){
    if (x == 1) {
      return 1;
    }
    return x * FATR(x - 1);
  }
  static int FIB(int x){
    if (x == 0) {
      return 0;
    }
    if (x == 1) {
      return 1;
    }
    int res = FIB(x - 1) + FIB(x - 2);
    
    return res;
  }
  public static void main(String[] args) {
    double a,b;
    Scanner scanner = new Scanner(System.in);

    System.out.print("Digite o primeiro valor: ");
    a = scanner.nextInt();
    // System.out.print("Digite o segundo valor: ");
    // b = scanner.nextDouble();    
    scanner.close();

    for (int i = 1; i <= a; i++){
      System.out.println("Fibonnaci: " + FIB(i));
    }

    // System.out.println("Fibonnaci: " + FIB((int) a));
    // System.out.println("Soma :" + somar(a, b));
  }
}
