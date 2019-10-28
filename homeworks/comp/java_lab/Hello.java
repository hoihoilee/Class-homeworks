//import java.util.Random;

public class Hello {
	public static void main(String[] args) {
		String tmp = "A\tB  C";
		String[] t = tmp.split(" ");
		for (int i = 0; i < t.length; i++)
			System.out.println("\""+t[i]+"\"");
		/*int n = 0;
		while (true) {
		Random ran1 = new Random();
		Random ran2 = new Random();
		int dice1 = ran1.nextInt(12) + 1;
		int dice2 = ran2.nextInt(12) + 1;
		System.out.println(dice1 + " " +dice2);
		n++;
		if ((dice1 == 12) && (dice2 == 12)) break;
		}
		String out = "We rolled dices " + n + " times";
		System.out.println(out);

		String str = ",A - B C.D\nE\"F's(,.-\"\n's)().";
		System.out.println(str+"\n");

		str = str.replace(',', ' ');
		str = str.replace('.', ' ');
		str = str.replace('(', ' ');
		str = str.replace(')', ' ');
		str = str.replaceAll(" - ", " ");
		str = str.replace('\"', ' ');
		str = str.replaceAll("'s", " ");
		str = str.replace('\n', ' ');
		
		System.out.println(str+"\n");
		String[] temp = str.split(" ");
		for (int i = 0; i < temp.length; i++) {
			if (temp[i].length() == 0) continue;
			System.out.print(temp[i]+"\n----\n");
		}
		String t = 3 + "";
		System.out.println(t);*/
	}
}
