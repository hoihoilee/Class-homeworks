#include "std_lab_facilities.h"

int subseq(int X, int Y); //check whether X is subsequence of Y or not
int substr(int X, int Y); //check whether X is substring of Y or not

int main()
{
	int X, Y;

	cout << "Enter Y : ";
	cin >> Y; //get Y value
	cout << "Enter X : ";
	cin >> X; //get X value
	
	try
	{
		if ((Y < X) || (X < 0) || (Y < 0)) throw X; // when X is greater than Y or input value is negative value, throw error 
		
		if (substr(X, Y)) cout << "X is substring of Y" << endl; // if function 'substr' is true, print this message
		else if (subseq(X, Y)) cout << "X is subsequence of Y" << endl; // if function 'subseq' is true, print this message
		else cout << "X is neither substring nor subsequence of Y" << endl; // if both 'substr' and 'subseq' are false, print this message
	}
	catch (int e)
	{
		cerr << "Invalid value" << endl;
	}
}

int subseq(int X, int Y)
{
	if (X == 0) return 1; // if all of X's numbers are checked, X is subsequence of Y
	else if (Y == 0) return 0; // if all of X's numbers are not checked yet, but no more Y's numbers are left, X is not subsequence of Y
	
	else
	{
		int b = Y%10; // Y's last number
		int a = X%10; // X's last number

		if (a == b)
			return subseq(X/10, Y/10); // if X's last number and Y's last number are same, check next number of both
		else
			return subseq(X, Y/10); // not same number, check next number of Y with X's last number
	}
}
		
int substr(int X, int Y)
{
	while (X <= Y) // when Y becomes smaller than X, terminate checking
	{
		int tmp_X = X;
		int tmp_Y = Y;

		while (tmp_X != 0)
		{
			int b = tmp_Y%10; //Y's last number
			int a = tmp_X%10; //X's last number

			if (a == b) // if X's last number and Y's last number are same, check next number of both
			{
				tmp_X = tmp_X/10;
				tmp_Y = tmp_Y/10;
			}
			else break; // if not substring, break and check next sequence of Y
		}

		if (tmp_X == 0) return 1; // if X is substring of Y, return true value

		Y = Y/10; //check next sequence of Y
	}
	
	return 0; // if checking is over, X is not substring of Y so return false value
}			
