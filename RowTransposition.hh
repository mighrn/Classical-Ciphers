#pragma once

class RowTransposition: public CipherInterface
{
public:
	bool setKey(const string& key)
	{
		bool valid = false;
		int i = 0;
		while(i < key.size() && !valid)
		{
			if(isalpha(key[i]))
			{
				int rank = 0;
				for(int x = 0; x < key.size(); x++)
				{
					if(x != i)
					{
						if(key[i] > key[x])
						{
							rank++;
						}
						else if (key[i] == key[x])
						{
							if(i > x)
							{
								rank++;
							}
						}
					}
				}
				rtkey.push_back(rank);
				i++;
			}
			else
			{
				valid = !valid;
				cout << "ERROR! Row Transposition key can only contain letters\n"
				<< "You typed: " << key << "\nNOW EXITING\n";
			}
		}
		cout << "using this key: ";
		printKey();
	
		return !valid;
	}

	string encrypt(const string& plaintext)
	{
		int rsize = ceil(double(plaintext.size()) / double(rtkey.size()));
		if(rtkey.size() >= plaintext.size())
		{
			cout << "WARNING! Key is greater than size of text\n";
			rsize = plaintext.size();
		}
		string ciphertext;
		
		for(int c = 0; c < rtkey.size(); c++)
		{
			for(int r = 0; r < rsize; r++)
			{
				int const n = findIndex(c, rtkey);
				if(r * rtkey.size() + n <= plaintext.size())
				{
					ciphertext.push_back(plaintext[r * rtkey.size() + n]);
				}
			}
		}
		cout << "ciphertext: " << ciphertext << endl;
		
		return ciphertext;
	}
	
	string decrypt(const string& ciphertext)
	{
		int csize = rtkey.size();
		if(rtkey.size() >= ciphertext.size())
		{
			cout << "WARNING! Key is greater than size of text\n";
			csize = ciphertext.size();
		}
		int rsize = ceil(double(ciphertext.size()) / double(csize));
		
		string plaintext;
		string temp = ciphertext;
		int extra = (ciphertext.size() % csize);
		
		if(extra > 0)
		{
			vector<int> sortKey;
			
			for(int y = csize - 1; y > extra - 1; y--)
			{
				if(sortKey.size() == 0)
				{
					sortKey.push_back(rtkey[y]);
				}
				else
				{
					auto n = sortKey.begin();
					bool found = false;
					while(n < sortKey.end() && !found)
					{
						if(rtkey[y] <= sortKey[*n])
						{
							sortKey.insert(n, 1, rtkey[y]);
							found = !found;
							n++;
						}
						else
						{
							if(n + 1 == sortKey.end())
							{
								sortKey.push_back(rtkey[y]);
								found = !found;
								n++;
							}
							else
							{
								n++;
							}
						}
					}
				}
			}
			for(int x = 0; x < sortKey.size(); x++)
			{
				temp.insert(((sortKey[x] + 1) * rsize) - 1, 1, '*');
			}
		}
		
		cout << "\ntmp: " << temp << endl;
		
		for(int i = 0; i < rsize; i++)
		{
			for(int j = 0; j < csize; j++)
			{
				plaintext.push_back(temp[rtkey[j] * rsize + i]);
			}
		}
		
		cout << "plaintext: " << plaintext << endl;
		
		return plaintext;
	}
	
	void printKey()
	{
		for(int i = 0; i < rtkey.size(); i++)
		{
			cout << rtkey[i] << ' ';
		}
		cout << endl;
	}
	
	int const findIndex(int const & f, vector<int> const & arr)
	{
		bool found = false;
		int i = 0;
		while(i < arr.size() && !found)
		{
			if(arr.at(i) == f)
			{
				found = !found;
			}
			i++;
		}
		return i - 1;
	}
protected:
	vector<int> rtkey;
};
