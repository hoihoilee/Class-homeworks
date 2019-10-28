#include "std_lab_facilities.h"

const int SZ = 256;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Error" << endl;
		return 0;
	}

	ifstream ifs (argv[1]);
	char letter;
	int abc[SZ];

	for (int i = 0; i < SZ; i++)
		abc[i] = 0;

	if (ifs.is_open())
	{
		while (ifs.get(letter))
		{
			if (letter == 10) continue;
			abc[(int)letter]++;
		}
		ifs.close();
	}
	else
	{
		cout << "Unable to open file to read" << endl;
		return 0;
	}

	ofstream ofs ("freq_report.txt");
	
	if (ofs.is_open())
	{
		while (1)
		{
			int max[2] = {0, 0};

			for (int i = 0; i < SZ; i++)
			{
				if (max[0] < abc[i])
				{
					max[0] = abc[i];
					max[1] = i;
				}
			}
			
			if (max[0] == 0) break;

			ofs << (char)max[1] << "(value: " << max[1] << ") : " << max[0] << endl;
			abc[max[1]] = 0;
		}
		ofs.close();
	}
	else cout << "Unable to open file to write" << endl;
	
	return 0;
}
