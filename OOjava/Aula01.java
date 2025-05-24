import java.util.Scanner;

public class Aula01 {
	public static void main(String[] args) {
		Scanner myScanner = new Scanner(System.in);

		System.out.println("Digite um numero: ");
		int myNum = myScanner.nextInt();

		for (int i = 0; i < myNum; i++) {			
			if (isPrime(i)) {
				System.out.print(i + " ");			
			}
		}
		
		myScanner.close();
	}

	private static boolean isPrime(int num) {
		if (num <= 1) {
			return false;
		}

		for (int i = 2; i < num; i++) {
			if (num % i == 0) {
				return false;
			}
		}

		return true;
	}
}
