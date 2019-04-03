#pragma once

class Caesar: public CipherInterface
{
public:
	bool setKey(const string & key)
	{
		bool valid = true;
		int i = 0;
		while(i < key.size() && valid)
		{
			if(!isdigit(key[i]))
			{
				valid = !valid;
				cout << "ERROR! Caesar cipher key can only be a positive integer\n"
				<< "NOW EXITING\n";
			}
			i++;
		}
		if(valid)
		{
			ckey = stoi(key) % 26;
		}
		return valid;
	}
	string encrypt(const string & plaintext)
	{
		string ciphertext;
		for(int i = 0; i < plaintext.size(); i++)
		{
			int p = int(toupper(plaintext[i])) - 65;
			
			char c = char(((p + ckey) % 26) + 65);
			
			ciphertext.push_back(toupper(c));
		}
		cout << "ciphertext is " << ciphertext << endl;
		return ciphertext;
	}
	string decrypt(const string & ciphertext)
	{
		string plaintext;
		for(int i = 0; i < ciphertext.size(); i++)
		{
			int p = int(toupper(ciphertext[i])) - 65;
			
			char c = char(((p + (26 - ckey)) % 26) + 65);
			
			plaintext.push_back(toupper(c));
		}
		cout << "plaintext is " << plaintext << endl;
		return plaintext;
	}
protected:
	int ckey;
};
