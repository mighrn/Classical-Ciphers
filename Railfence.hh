#pragma once

class Railfence: public CipherInterface
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
				cout << "ERROR! Railfence key can only be a positive integer\n"
				<< "NOW EXITING\n";
			}
			i++;
		}
		if(valid)
		{
			rfkey = stoi(key) % 26;
		}
		return valid;
	}
	
	string encrypt(const string & plaintext)
	{
		int nrfkey = rfkey % plaintext.size();
		if(rfkey >= plaintext.size())
		{
			cout << "WARNING! Key is greater than size of text\n";
			nrfkey = plaintext.size();
		}
		string ciphertext;
		int csize = ceil(double(plaintext.size()) / double(nrfkey));
		
		for(int o = 0; o < nrfkey; o++)
		{
			for(int i = 0; i < csize; i++)
			{
				if(i * nrfkey + o < plaintext.size())
				{
					ciphertext.push_back(plaintext[i * nrfkey + o]);
				}
			}
		}
		
		cout << "ciphertext: " << ciphertext << endl;
		return ciphertext;
	}
	
	string decrypt(const string & ciphertext)
	{
		int nrfkey = rfkey % ciphertext.size();
		if(rfkey >= ciphertext.size())
		{
			cout << "WARNING! Key is greater than size of text\n";
			nrfkey = ciphertext.size();
		}
		string plaintext;
		string temp = ciphertext;
		int csize = ceil(double(ciphertext.size()) / double(nrfkey));
		
		int extra = (ciphertext.size() % nrfkey);
		
		if(extra > 0)
		{
			for(int i = extra + 1; i < nrfkey + 1; i++)
			{
				temp.insert(i * csize - 1, 1, '*');
			}
		}
		
		cout << "temp string : " << temp << endl;
		
		for(int x = 0; x < csize; x++)
		{
			for(int y = 0; y < nrfkey; y++)
			{
				plaintext.push_back(temp[y * csize + x]);
			}
		}
		
		cout << "plaintext: " << plaintext << endl;
		return plaintext;
	}
protected:
	int rfkey;
};
