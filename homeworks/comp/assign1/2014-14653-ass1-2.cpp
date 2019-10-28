#include "std_lab_facilities.h"
#include "string.h"

int crypt(char str[], int key, int choice); //Encrypt or decrypt the string
int Err_check(char str[]); //check whether input string has unallowed value or not

int main()
{
	char input_choice[256];
	int choice;

	while (1)
	{
		cout << "Encrypt (1) Decrypt (2) : ";
		cin >> input_choice; // get input
		choice = (int)input_choice[0] - 48; // variable 'choice' becomes ASCII code number (minus 48 - because ASCII code number of '1' is 49) of first letter of input string
	
		if ((strlen(input_choice) == 1) && ((choice == 1) || (choice == 2))) break; //length of input string is 1 and choice is either 1 or 2 means, input string is either '1' or '2'
		
		cout << "Invalid value" << endl; // if input string is neither '1' nor '2', print this message and get another string again
	}

	try
	{
		int key;
		char str[256];
				
		cout << "Enter string : ";
		cin >> str; // get string
		cout << "Enter key value : ";
		cin >> key; // get key

		if (key < 0) throw 1; // negative key value is not allowed
		Err_check(str);
		crypt(str, key, choice);

		cout << str << endl; // print encrypted or decrypted string
	}
	catch (int e)
	{
		cerr <<"Input value is out of range" << endl;
	}
}

int crypt(char str[], int key, int choice)
{
	int i, j;
	char word_array[256] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789"; // base word array

	for (i = 0; i < strlen(str); i++)
	{
		for (j = 0; j < 61; j++)
		{
			if (str[i] != word_array[j]) continue; // match letter of string with letter of base word array
			
			if (choice == 1) str[i] = word_array[(j + key)%61]; // Encrypting the letter with key
			else str[i] = word_array[(j + 61 - (key%61))%61]; // Decrypting the letter with key
			
			break;
		}	
	}
}

int Err_check(char str[])
{
	int i;

	for (i = 0; i < strlen(str); i++)
       	{
		if (((int)str[i] > 48) && ((int)str[i] < 58)) continue; // range 1 ~ 9
		else if (((int)str[i] > 64) && ((int)str[i] < 91)) continue; // range A ~ Z
		else if (((int)str[i] > 96) && ((int)str[i] < 123)) continue; // range a ~ z
                else // out of range then throw error
		{
			throw 1;
                        break;
                }
	}
}

