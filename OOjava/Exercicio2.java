import java.util.Scanner;
 
class Main {
    public static void main(String[] args) {
        Scanner scan;
        scan = new Scanner(System.in);
 
        int num;
        System.out.print("Digite a variavel: ");
        num = scan.nextInt();

        for (int i = 2; i <= num; i++) {
            if (i == num) {
                System.out.print("O numero e primo");
                break;
            }
            if (num % i == 0) {
                System.out.print("O numero nao e primo");
                break;
            }
        }

        scan.close();
    }
}