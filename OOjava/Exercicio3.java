import java.util.Scanner;

public class Exercicio3 {
  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);

    String nome;
    int idade;
    float altura;

    
    System.out.print("Digite a idade: ");
    idade = scan.nextInt();
    scan.nextLine();  
    System.out.print("Digite o nome: ");
    nome = scan.nextLine();
    System.out.print("Digite a altura: ");
    altura = scan.nextFloat();

    System.out.println(nome+" tem "+idade+" anos e "+altura+" de altura.");

    scan.close();
  }
}
