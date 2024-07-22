// SDES_.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
#include "../SDES_/KeyGen.h"
#include "../SDES_/Encrypt.h"




// William Stallings Simplififed DES wrtten 
//By. Luis Gonzalez



static void printKeys(std::bitset<8>& key1, std::bitset<8>& key2) {
	std::cout << "Key 1: " << key1 << std::endl;
	std::cout << "Key 2: " << key2 << std::endl;
}


int main() {

	// Key 1 assert (1010 0100)
	// Key 2 assert (0100 0011)
	std::bitset<8> assertK1(164);
	std::bitset<8> assertK2(67);

	KeyGen key;

	std::bitset<8> k1 = key.getKey1Bit();
	std::bitset<8> k2 = key.getKey2Bit();

	printKeys(k1, k2);

	assert(assertK1 == k1);
	assert(assertK2 == k2);


	Encrypt enrypt(k1, k2);
	std::bitset<8> ip(189);
	std::cout << "IP: " << ip << std::endl;

	std::bitset<4> ep = enrypt.fk_enrypt_word(ip);

	std::cout << "EP: " << ep << std::endl;

	return 0;
}