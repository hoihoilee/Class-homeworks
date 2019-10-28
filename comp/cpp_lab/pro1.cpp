#include "std_lab_facilities.h"

int print_array(int n[]);
int sort(int n[]);

int main()
{
	int n[10];
	int i;

	for (i = 0; i < 10; i++)
		cin >> n[i];

	print_array(n);
	sort(n);
	print_array(n);

	return 0;
}

int print_array(int n[])
{
	int i;
	
	for (i = 0; i < 10; i++)
		cout << n[i] << " " ;

	cout << endl;
}

int sort(int n[])
{
	int i, j, tmp;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 9 - i; j++)
		{
			if (n[j] > n[j+1]) 
			{
				tmp = n[j];
				n[j] = n[j+1];
				n[j+1] = tmp;
			}
		}
	}
} 
	
