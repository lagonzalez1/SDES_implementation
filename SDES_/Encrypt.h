#pragma once
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

	Encrypt(std::bitset<8> key1, std::bitset<8> key2) {
		this->key1 = key1;
		this->key2 = key2;
	}
	std::bitset<4> fk_enrypt_word(std::bitset<8>);
	std::bitset<4> sbox_permutation(int, int);
	int* decimal_to_binary(int, int, int[4]);
	std::bitset<4> Fun(std::bitset<8>);

private:
	// Inital permutation
	int MAX_SIZE = 8;
	int X = 4;
	int Y = 4;

	int inital_permutation[8] = { 2,6,3,1,4,8,5,7 };
	int ep[8] = { 4,1,2,3,2,3,4,1 };
	//1011 1101 
	//1101 0111 
	int s0_box[4][4] = { {1,0,3,2},{3,2,1,0}, {0,2,1,3},{3,1,3,2} };
	int s1_box[4][4] = { {0,1,2,3}, {2,0,1,3}, {3,0,1,0}, {2,1,0,3} };

	int perm[4] = { 2,4,3,1 };

};


// fk(L,R)=(L XOR F(R,SK), R)
// Before XOR: 
// 1101 0111
std::bitset<4> Encrypt::Fun(std::bitset<8> right) {
	std::bitset <8> ep_permute;
	int lsb = MAX_SIZE;
	for (std::size_t i = 0; i < 8; i++) {
		int index = ep[i];
		int value = right[index - 1];
		ep_permute.set(--lsb, value);
	}

	for (std::size_t i = 0; i < 8; i++) {
		int value = ep_permute[i] ^ key1[i];
		ep_permute[i] = value;
	}

	std::cout << "EP:" << ep_permute << std::endl;

	std::bitset<2> row_s0_bit;
	row_s0_bit.set(1, ep_permute[7]);
	row_s0_bit.set(0, ep_permute[4]);

	std::bitset<2> col_s0_bit;
	col_s0_bit.set(1, ep_permute[6]);
	col_s0_bit.set(0, ep_permute[5]);

	std::bitset<2> row_s1_bit;
	row_s1_bit.set(1, ep_permute[3]);
	row_s1_bit.set(0, ep_permute[0]);

	std::bitset<2> col_s1_bit;
	col_s1_bit.set(1, ep_permute[2]);
	col_s1_bit.set(0, ep_permute[1]);

	int row_s0 = row_s0_bit.to_ulong();
	int col_s0 = col_s0_bit.to_ulong();

	int row_s1 = row_s1_bit.to_ulong();
	int col_s1 = col_s1_bit.to_ulong();


	// GET bitset of 4 using s0_value, s1_value
	int s0_value = s0_box[row_s0][col_s0];
	int s1_value = s1_box[row_s1][col_s1];

	// Get the first 4 bits feed into s0 1 00 1 = 11->3
	// Get the last 4 bits feed into s1 0000 = 00->0
	return sbox_permutation(s0_value, s1_value);
}

std::bitset<4> Encrypt::sbox_permutation(int a, int b) {
	std::bitset<4> s_box_permutation;
	int binary[4] = { 0,0,0,0 };
	int* modified_binary = binary;
	modified_binary = decimal_to_binary(a, b, binary);
	
	// Assert number cannot be larger than 3
	for (int i = 3; i >= 0; i--) {
		s_box_permutation.set(i, modified_binary[i]);
	}
	return s_box_permutation;
}

int* Encrypt::decimal_to_binary(int a, int b, int binary[4]) {
	int i = 0;
	while (a > 0) {
		binary[i] = a % 2;
		a = a / 2;
		i++;
	}

	int k = 2;
	while (b > 0) {
		binary[k] = b / 2;
		b = b / 2;
		k++;
	}

	return binary;

}


std::bitset<4> Encrypt::fk_enrypt_word(std::bitset<8> ip) {
	// fk(L,R)=(L XOR F(R,SK), R)
	std::bitset<4> ep_key1 = Fun(ip);

	return ep_key1;
}