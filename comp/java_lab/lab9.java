import java.lang.Math;

public class lab9 {
	public static void main(String[] args) {

	double min = 999;
	double d = 0;
	int pointers[][] = new int[6][2];
	pointers[0][0] = 1;
	pointers[0][1] = 1;
	pointers[1][0] = 4;
	pointers[1][1] = 6;
	pointers[2][0] = 9;
	pointers[2][1] = 7;
	pointers[3][0] = 2;
	pointers[3][1] = 3;
	pointers[4][0] = 4;
	pointers[4][1] = 9;
	pointers[5][0] = 8;
	pointers[5][1] = 8;
	int p1=0,p2=0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (i == j) continue;
			
			d = Math.sqrt(Math.pow(pointers[i][0] - pointers[j][0],2) + Math.pow(pointers[i][1] - pointers[j][1],2));
			
			if (min > d){
			 min = d;
				p1=i;p2=j;
			}
		}
	}
	System.out.println("Pointers with minimum distance are P" + p1 +" and P" +p2);
	System.out.println("Minimum distance of two pointer is " + min);
	}
}	
