public class Lab11Driver {
public static void main(String[] args) {
	Human a = new Human("TA1", 2015);
	a.walk();

       System.out.println(a);       Student b = new Student("Not TA", 2016, 11111);       b.walk();       System.out.println(b);//*       //Polymorphism       Human h1 = new Student("h1", 1000, 10101);  //safe       Student h2 = (Student)h1;   //Need type casting\*       //instance of       Human a1 = new Human("a1", 1000);       Student a2 = new Student("a2", 1000, 1000);       Human a3 = new Student("a3", 1000, 1000);       System.out.println(a1 instanceof Human);    //true       System.out.println(a1 instanceof Student);  //false       System.out.println(a2 instanceof Human);    //true       System.out.println(a2 instanceof Student);  //true       System.out.println(a3 instanceof Human);    //true       System.out.println(a3 instanceof Student);  //true       a1 = a2;       System.out.println(a1 instanceof Student);  //true\*/   }<Left>
