public class Calculadora {
  String marca;
  double preco;
  Calculadora(String MARCA, Double PRECO){
    this.marca = MARCA;
    this.preco = PRECO;
  }

  static double soma(double a, double b){
    return a + b;

  }
  public static void main(String[] args){
    Calculadora c = new Calculadora("Cassio", 79.99);

    System.out.println("Marca " + c.marca);
    System.out.println("Preco R$ " + c.preco);
    System.out.println(c.soma(10, 20));
  }
 
}
