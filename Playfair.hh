#pragma once

class Playfair: public CipherInterface
{
public:
	/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool setKey(const string& key)
{
	bool flag = false;
	int i = 0;
	while(i < key.size() && !flag)
	{
		if(isalpha(key[i]))
		{
			bool valid = true;
			bool isj = false;
			if(key[i] == 'j' || key[i] == 'J')
			{
				//check if input is a J
				isj = true;
			}
			int n = 0;
			if(key.size() == 0)
			{
				valid = true;
			}
			else
			{
				while(n < pfkey.size() && valid)
				{
					if(isj)
					{
						if(pfkey[n] == 'I')
						{
							//if input is J, check key for I
							valid = !valid;
						}
					}
					else
					{
						if(pfkey[n] == toupper(key[i]))
						{
							//check key for repeats
							valid = !valid;
						}
					}
					n++;
				}
			}
			
			if(valid)
			{
				//if input was valid, add it to the key accordingly
				if(isj)
				{
					pfkey.push_back('I');
				}
				else
				{
					pfkey.push_back(toupper(key[i]));
				}
			}
			i++;
		}
		else
		{
			cout << "ERROR! Playfair Key should only contain letters of the english alphabet"
			<< "\nYou typed: " << key << "\nNOW EXITING\n";
			flag = !flag;
		}
	}
	return !flag;
}




/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string encrypt(const string& plaintext)
{
	cout << "PLF encryption\n";
	makeMatrix();
	string ciphertext;
	
	//plaintext is encrypted in pairs
	for(int i = 0; i < plaintext.size(); i += 2)
	{
		char p1, p2;
		//deal with I/J problem
		if(plaintext[i] == 'j' || plaintext[i] == 'J')
		{
			p1 = 'I';
		}
		else
		{
			p1 = toupper(plaintext[i]);
		}
		if(plaintext[i + 1] == 'j' || plaintext[i + 1] == 'J')
		{
			p2 = 'I';
		}
		else
		{
			p2 = toupper(plaintext[i + 1]);
		}
		
		if(p1 == p2)
		{
			//both letters are equal
			//encrypt both as letter one right and one down
			int row;
			int col;
			findIndex(p1, row, col);
			row = (row + 1) % 5;
			col = (col + 1) % 5;
			ciphertext.push_back(matrix[row * 5 + col]);
			ciphertext.push_back(matrix[row * 5 + col]);
		}
		else
		{
			int row1, row2, col1, col2;
			findIndex(p1, row1, col1);
			findIndex(p2, row2, col2);
			if(row1 == row2)
			{
				//letters are in the same row
				//encrypt as one letter to the right
				col1 = (col1 + 1) % 5;
				col2 = (col2 + 1) % 5;
				ciphertext.push_back(matrix[row1 * 5 + col1]);
				ciphertext.push_back(matrix[row2 * 5 + col2]);
			}
			else if(col1 == col2)
			{
				//letters are in the same column
				//encrypt as one letter down
				row1 = (row1 + 1) % 5;
				row2 = (row2 + 1) % 5;
				ciphertext.push_back(matrix[row1 * 5 + col1]);
				ciphertext.push_back(matrix[row2 * 5 + col2]);
			}
			else
			{
				//letters form a rectangle
				ciphertext.push_back(matrix[row1 * 5 + col2]);
				ciphertext.push_back(matrix[row2 * 5 + col1]);
			}
		}
	}
	cout << "the ciphertext is: " << ciphertext << endl;
	return ciphertext; 
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string decrypt(const string& cipherText) 
{
	makeMatrix();
	string plaintext;
	
	for(int i = 0; i < cipherText.size(); i += 2)
	{
		char c1, c2;
		if(cipherText[i] == 'j' || cipherText[i] == 'J')
		{
			c1 = 'I';
		}
		else
		{
			c1 = toupper(cipherText[i]);
		}
		if(cipherText[i + 1] == 'j' || cipherText[i + 1] == 'J')
		{
			c2 = 'I';
		}
		else
		{
			c2 = toupper(cipherText[i + 1]);
		}
		
		if(c1 == c2)
		{
			//letters are same
			//decrypt as one col left and one row up
			int row, col;
			findIndex(c1, row, col);
			row = (row - 1) % 5;
			col = (col - 1) % 5;
			plaintext.push_back(matrix[row * 5 + col]);
			plaintext.push_back(matrix[row * 5 + col]);
		}
		else
		{
			int row1, row2, col1, col2;
			findIndex(c1, row1, col1);
			findIndex(c2, row2, col2);
			if(row1 == row2)
			{
				//letters are in the same row
				//decrypt as one letter to the left
				col1 = (col1 + 4) % 5;
				col2 = (col2 + 4) % 5;
				plaintext.push_back(matrix[row1 * 5 + col1]);
				plaintext.push_back(matrix[row2 * 5 + col2]);
			}
			else if(col1 == col2)
			{
				//letters are in the same column
				//decrypt as one letter up
				row1 = (row1 - 1) % 5;
				row2 = (row2 - 1) % 5;
				plaintext.push_back(matrix[row1 * 5 + col1]);
				plaintext.push_back(matrix[row2 * 5 + col2]);
			}
			else
			{
				//letters form a rectangle
				plaintext.push_back(matrix[row1 * 5 + col2]);
				plaintext.push_back(matrix[row2 * 5 + col1]);
			}
		}
	}
	cout << "plaintxt is: " << plaintext << endl;
	return plaintext;	
}

void makeMatrix()
{
	for(int i = 0; i < pfkey.size(); i++)
	{
		matrix.push_back(pfkey[i]);		
	}
	for(int i = 0; i < 26; i++)
	{
		if(i != 9)
		{
			//skip J
			bool repeat = false;
			int j = 0;
			while(j < pfkey.size() && !repeat)
			{
				if(pfkey[j] == char(i + 65))
				{
					repeat = !repeat;
				}
				j++;
			}
			if(!repeat)
			{
				matrix.push_back(char(i + 65));
			}
		}		
	}
	printMatrix();
}

void printMatrix()
{
	cout << "Constructed the following matrix with this key: "
	<< pfkey << endl;
	for(int r = 0; r < 5; r++)
	{
		for(int c = 0; c < 5; c++)
		{
			cout << matrix[r * 5 + c] << ' ';
		}
		cout << '\n';
	}
}

void findIndex(char const & p, int & r, int & c)
{
	int x = 0;
	bool found = false;
	bool isj = false;
	if(p == 'j' || p == 'J')
	{
		isj = true;
	}
	while(x < matrix.size() && !found)
	{
		if(isj)
		{
			if(matrix[x] == 'I')
			{
				found = !found;
			}
		}
		else
		{
			if(matrix[x] == p)
			{
				found = !found;
			}
		}
		x++;
	}
	c = (x - 1) % 5;
	r = ((x - 1) - c) / 5;
}

protected:
	string pfkey = "";
	string matrix = "";

};

