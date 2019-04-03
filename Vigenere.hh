#pragma once

class Vigenere: public CipherInterface
{
public:
	bool setKey(const string & key)
	{
		bool valid = true;
		int i = 0;
		while(i < key.size() && valid)
		{
			if(!isalpha(key[i]))
			{
				valid = !valid;
				cout << "ERROR! Vigenere key can only contain letters\n"
				<< "NOW EXITING\n";
			}
			vkey.push_back(toupper(key[i]));
			i++;
		}
		return valid;
	}
	
	string encrypt(const string & plaintext)
	{
		string ciphertext;
		string newvkey = vkey;
		if(vkey.size() < plaintext.size())
		{
			for(int i = 0; i < plaintext.size() - vkey.size(); i++)
			{
				newvkey.push_back(toupper(plaintext[i]));
			}
		}
		for(int i = 0; i < plaintext.size(); i++)
		{
			int p = int(toupper(plaintext[i])) - 65;
			
			char c = char(((p + int(newvkey[i]) - 65) % 26) + 65);
			
			ciphertext.push_back(toupper(c));
		}
		cout << "ciphertext is " << ciphertext << endl;
		return ciphertext;
	}
	
	string decrypt(const string & ciphertext)
	{
		string plaintext;
		string newvkey = vkey;
		for(int i = 0; i < ciphertext.size(); i++)
		{
			int c = int(toupper(ciphertext[i])) - 65;
			int p = (26 + (c - (int(newvkey[i]) - 65))) % 26;
			char plain = char(p + 65);
			
			if(newvkey.size() < ciphertext.size())
			{
				newvkey.push_back(plain);
			}
			plaintext.push_back(plain);
		}
		cout << "plaintext: " << plaintext << endl;
		return plaintext;
	}
protected:
	string vkey;
};
