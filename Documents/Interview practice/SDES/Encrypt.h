// S-DES Encryption
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>

class Encrypt {

	public:
		std::bitset<8> key1;
		std::bitset<8> key2;

		Encrypt(std::bitset<8> key1,std::bitset<8> key2) {
			this->key1 = key1;
			this->key2 = key2;
		}
		std::bitset<8> fk_enrypt_word(std::bitset<8>);
		std::bitset<8> fk_enrypt_word_round2(std::bitset<8>);
		std::bitset<8> Fun(std::bitset<8>);

	private:
		// Inital permutation
		int MAX_SIZE = 8;
		int X = 4;
		int Y = 4;

		int inital_permutation[8] = {2,6,3,1,4,8,5,7};
		int ep[8] = {4,1,2,3,2,3,4,1};
		//1011 1101 
		//1101 0111 
		int s0_box[4][4] = {{1,0,3,2},{3,2,1,0}, {0,2,1,3},{3,1,3,2}};
		int s1_box[4][4] = {{0,1,2,3}, {2,0,1,3}, {3,0,1,0}, {2,1,0,3}};

		int perm[4] = {2,4,3,1};

};


// fk(L,R)=(L XOR F(R,SK), R)
// Before XOR: 
// 1101 0111
std::bitset<8> Encrypt::Fun(std::bitset<8> right){
	std::bitset <8> ep_permute; 
	int lsb = MAX_SIZE;
	for (std::size_t i = 0; i < 8; i++) {
		int index = ep[i];
		int value = right[index-1];
		ep_permute.set(--lsb,value);
	}

	for (std::size_t i = 0; i < 8; i ++){
		int value = ep_permute[i] ^ key1[i];
		ep_permute[i] = value;
	}


	std::cout << "EP:" << ep_permute << std::endl;

	std::bitset<2> row_s0_bit;
	row_s0_bit.set(0,ep_permute[0]);
	row_s0_bit.set(1, ep_permute[3]);

	std::bitset<2> col_s0_bit;
	col_s0_bit.set(0, ep_permute[1]);
	col_s0_bit.set(1, ep_permute[2]);

	std::bitset<2> row_s1_bit; 
	row_s1_bit.set(0, ep_permute[4]);
	row_s1_bit.set(1, ep_permute[7]);

	std::bitset<2> col_s1_bit;
	col_s1_bit.set(0, ep_permute[5]);
	col_s1_bit.set(1, ep_permute[6]);


	int row_s0 = row_s0_bit.to_ulong();
	int col_s0 = col_s1_bit.to_ulong();

	int row_s1 = row_s1_bit.to_ulong();
	int col_s1 = col_s1_bit.to_ulong();


	std::cout << row_s0_bit << std::endl;
	std::cout << col_s0_bit << std::endl;

	std::cout << row_s1_bit << std::endl;
	std::cout << col_s1_bit << std::endl;
	/*
		0111 0011
		01 11 01 01
        1  3  1  1
          0     0 
         00     00
		10
		10
		10
		11
		EP: 01110011

	*/



	// Get the first 4 bits feed into s0 1 00 1 = 11->3
	// Get the last 4 bits feed into s1 0000 = 00->0

	return ep_permute;
}


std::bitset<8> Encrypt::fk_enrypt_word(std::bitset<8> ip) {
	// fk(L,R)=(L XOR F(R,SK), R)
	std::bitset<8> ep_key1 = Fun(ip);

	return ep_key1;
}