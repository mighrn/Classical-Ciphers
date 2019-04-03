#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#include "CipherInterface.hh"
#include "Playfair.hh"
#include "RowTransposition.hh"
#include "Railfence.hh"
#include "Vigenere.hh"
#include "Caesar.hh"

void displayHelp()
{
	cout << "Usage:\n"
	<< "\t./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUTFILE>\n\n"
	<< "<CIPHER NAME> Choose one from the following:\n"
	<< " PLF\n RTS\n RFC\n VIG\n CES\n"
	<< "<KEY> Type your encryption key\n"
	<< "<ENC/DEC> Choose only one mode to either encrypt or decrypt\n"
	<< "<INPUTFILE> The file to encrypt or decrypt\n"
	<< "<OUTPUTFILE> File after encryption or decryption\n";
}

void argParse(int argc, char** argv, vector<string> & u)
{
	//check the amount of arguments
	if(argc == 6)
	{
		//copy arguments into a vector of string type
		for(int i = 0; i < 5; i++)
		{
			u.push_back(argv[i + 1]);
		}
		
		//check ciphername
		if(u[0] != "PLF" && u[0] != "RTS"
		&& u[0] != "RFC" && u[0] != "VIG"
		&& u[0] != "CES")
		{
			cout << "ERROR! Incorrect cipher name: " << u[0] << endl;
			displayHelp();
			cout << "NOW EXITING\n";
			exit(-1);
		}
		
		if(u[2] != "ENC" && u[2] != "DEC")
		{
			cout << "ERROR! Incorrect cipher mode: " << u[3] << endl;
			displayHelp();
			cout << "NOW EXITING\n";
			exit(1);
		}
	}
	else if(argc < 6)
	{
		cout << "ERROR! Not enough arguments\n";
		displayHelp();
		cout << "NOW EXITING\n";
		exit(-1);
	}
	else
	{
		cout << "ERROR! Too many arguments\n";
		displayHelp();
		cout << "NOW EXITING\n";
		exit(-1);
	}
}

int main(int argc, char** argv)
{
	/* REPLACE THIS PART WITH YOUR CODE 
	 * THE CODE BELOW IS A SAMPLE TO 
	 * ILLUSTRATE INSTANTIATION OF CLASSES
	 * THAT USE THE SAME INTERFACE.
	 */	
	
	vector<string> userInput;
	argParse(argc, argv, userInput);
	
	string text;
	ifstream fin(userInput[3]);
	if(!fin.is_open() || !fin.good())
	{
		cout << "ERROR! Could not open input file: "
		<< userInput[3] << "\nNOTE: can only read from text files"
		<< "\nNOW EXITING\n";
		exit(-1);
	}
	else
	{
		while(!fin.eof())
		{
			fin >> text;
		}
		fin.close();
	}
	ofstream fout(userInput[4]);
	if(!fout.is_open() || !fout.good())
	{
		cout << "ERROR! Could not open output file: "
		<< userInput[3] << "\nNOTE: can only write to text files"
		<< "\nNOW EXITING\n";
		exit(-1);
	}
	CipherInterface* cipher = nullptr;
	if(userInput[0] == "PLF")
	{
		/* Create an instance of the Playfair cipher */	
		cipher = new Playfair();
	
		/* Error checks */
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		
		/* Set the encryption key */
		if(!cipher->setKey(userInput[1]))
		{
			cout << "key exit\n";
			exit(-1);
		}
		
		if(userInput[2] == "ENC")
		{
			if(text.size() % 2 == 1)
			{
				//plaintext has odd amount of pairs
				//add an X to the end
				text.push_back('X');
			}
			cout << "plaintext to be encrypted: " << text << endl;
			string ciphertext = cipher->encrypt(text);
			fout << ciphertext << endl;
		}
		else
		{
			if(text.size() % 2 == 1)
			{
				cout << "ERROR! ciphertext has odd number of letters\n"
				<< "NOW EXITING\n";
				exit(-1);
			}
			cout << "ciphertext to be decrypted: " << text << endl;
			string plaintext = cipher->decrypt(text);
			fout << plaintext << endl;
		}
		cipher = nullptr;
		delete cipher;
	}
	else if (userInput[0] == "RTS")
	{
		cipher = new RowTransposition();
	
		/* Error checks */
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		
		if(!cipher->setKey(userInput[1]))
		{
			cout<< "key exit\n";
			exit(-1);
		}
		
		if(userInput[2] == "ENC")
		{
			string ciphertext = cipher->encrypt(text);
			fout << ciphertext << endl;
		}
		else
		{
			string plaintext = cipher->decrypt(text);
			fout << plaintext << endl;
		}
		cipher = nullptr;
		delete cipher;
	}
	else if(userInput[0] == "RFC")
	{
		cipher = new Railfence();
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		
		if(!cipher->setKey(userInput[1]))
		{
			cout<< "key exit\n";
			exit(-1);
		}
		
		if(userInput[2] == "ENC")
		{
			string ciphertext = cipher->encrypt(text);
			fout << ciphertext << endl;
		}
		else
		{
			string plaintext = cipher->decrypt(text);
			fout << plaintext << endl;
		}
		cipher = nullptr;
		delete cipher;
	}
	else if(userInput[0] == "VIG")
	{
		cipher = new Vigenere();
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		
		if(!cipher->setKey(userInput[1]))
		{
			cout<< "key exit\n";
			exit(-1);
		}
		
		if(userInput[2] == "ENC")
		{
			string ciphertext = cipher->encrypt(text);
			fout << ciphertext << endl;
		}
		else
		{
			string plaintext = cipher->decrypt(text);
			fout << plaintext << endl;
		}
		cipher = nullptr;
		delete cipher;
	}
	else
	{
		cipher = new Caesar();
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		
		if(!cipher->setKey(userInput[1]))
		{
			cout<< "key exit\n";
			exit(-1);
		}
		
		if(userInput[2] == "ENC")
		{
			string ciphertext = cipher->encrypt(text);
			fout << ciphertext << endl;
		}
		else
		{
			string plaintext = cipher->decrypt(text);
			fout << plaintext << endl;
		}
		cipher = nullptr;
		delete cipher;
	}
	
	fout.close();
	
	return 0;
}

