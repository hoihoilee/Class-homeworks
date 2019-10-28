#include "std_lab_facilities.h"

int print_array(int n[]);
int sort(int n[]);

int main()
{
        int n[9];
        int i;

        for (i = 0; i < 9; i++)
                cin >> n[i];

        print_array(n);
        sort(n);
        print_array(n);

        return 0;
}

int print_array(int n[])
{
        int i, j;

        for (i = 0; i < 3; i++)
	{
		for (j = (3 * i); j < (3 * i) + 3; j++)
			cout << n[j];

		cout << endl;
	}
}

int sort(int n[])
{
        int i, j, tmp;

        for (i = 0; i < 9; i++)
        {
                for (j = 0; j < 8 - i; j++)
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

