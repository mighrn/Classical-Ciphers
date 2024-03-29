# Classical-Ciphers
## Implementing [Caesar](Caesar.hh), [Transposition](RowTransposition.hh), [Railfence](Railfence.hh), [Vigenere](Vigenere.hh), and [Playfair](Playfair.hh) Ciphers

### Miguel Hernandez
#### mig220@csu.fullerton.edu

Written in C++


To compile: In a terminal type:
```
make
```
To run: In a terminal type:
```
./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>
```
Help:
```
<CIPHER NAME> Choose from the following: CES RTS RFC VIG PLF

<KEY> Each cipher uses a unique key as follows:
	  CES: a positive integer between 0 and 26 inclusive
	  RTS: a string of letters
	  RFC: a positive integer
	  VIG: a string of letters
	  PLF: a string of letters

<ENC/DEC> Choose only one for Encryption or Decryption respectively

<INPUT FILE> Filename or path to read input

<OUTPUT FILE> Filename or path to write output
```
Note:

All input from files must only contain letters of the alphabet

(i.e. No digits, special characters, punction, or whitespaces allowed!)
