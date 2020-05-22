public class HelloWorld{
	public static void main(String args[]){
		int a = 1;
		int b = 2;
		Demo d = new Demo();
		int c = d.add(a,b);
		System.out.println("Hello World!!!");
		System.out.println(c);
	}
}

class Demo{
	public int add(int a,int b){
		return a + b;
	}
}