#pragma once
// S-DES Encryption
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <map>

class Encrypt {

public:
	std::bitset<8> key1;
	std::bitset<8> key2;

	Encrypt(std::bitset<8> key1, std::bitset<8> key2) {
		this->key1 = key1;
		this->key2 = key2;
	}
	std::bitset<4> decimal_to_binary(int, int);
	std::bitset<4> left_xor_operation(std::bitset<4>, std::bitset<4>);
	std::bitset<8> fk_enrypt_word(std::bitset<8>);
	std::bitset<8> fk_decrypt_word(std::bitset<8>);
	std::bitset<4> split_plaintext_left(std::bitset<8>);
	std::bitset<4> split_plaintext_right(std::bitset<8>);
	std::bitset<8> combine_result(std::bitset<4>,std::bitset<4>);
	std::bitset<4> sbox_permutation(int, int);
	std::bitset<4> Fun(std::bitset<4>, std::bitset<8>);
	std::map<int, int> bit_permutation(std::bitset<4>);

protected:
	// Inital permutation
	int MAX_SIZE = 8;
	int MAX_PERM_4 = 4;
	int BIT_HALF = 4;

	int ep[8] = { 4,1,2,3,2,3,4,1 };
	// Defined by preceding matrix in pdf.
	int s0_box[4][4] = { {1,0,3,2},{3,2,1,0}, {0,2,1,3},{3,1,3,2} };
	int s1_box[4][4] = { {0,1,2,3}, {2,0,1,3}, {3,0,1,0}, {2,1,0,3} };
	// Permutations 
	int inital_permutation[8] = { 2,6,3,1,4,8,5,7 };
	int perm[4] = { 2,4,3,1 };

};


// fk(L,R)=(L XOR F(R,SK), R)
// Before XOR: 
// 1101 0111
std::bitset<4> Encrypt::Fun(std::bitset<4>right, std::bitset<8> key) {
	std::bitset <8> ep_permute;
	int lsb = 8;
	for (int i = 0; i < 8; i++) {
		int index = ep[i];
		int value = right[index - 1]; // Grabs only from 4
		ep_permute.set(i, value);
	}
	for (int i = 0; i < 8; i++) {
		int value = ep_permute[i] ^ key[i]; // Check this order might be off since bit lg-sm
		ep_permute.set(i, value);
	}
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
	return sbox_permutation(s0_value, s1_value);
}

std::map<int, int>Encrypt::bit_permutation(std::bitset<4>bits) {
	std::map<int, int> hash_;
	int start = 0;
	for (int i = 3; i >= 0; i--) {
		hash_[start++] = bits[i];
	}
	return hash_;
}

std::bitset<4> Encrypt::sbox_permutation(int a, int b) {
	std::bitset<4> s_box_permutation;
	std::bitset<4> modified_binary = decimal_to_binary(a, b);
	std::map<int, int> hash_ = bit_permutation(modified_binary);
	int m = MAX_PERM_4;
	int start = 1;
	for (int i = 0; i < 4; i++) {
		int index = perm[i]-1;
		s_box_permutation.set(--m, hash_[index]);
	}
	return s_box_permutation;
}


std::bitset<4> Encrypt::left_xor_operation(std::bitset<4> left, std::bitset<4> output_fun) {

	std::bitset<4> ll;
	int k = MAX_PERM_4;
	for (int i = 0; i < 4; i++) {
		int value = left[i] ^ output_fun[i];
		ll.set(i, value);
	}
	return ll;
}

std::bitset<4> Encrypt::decimal_to_binary(int a, int b) {
	std::bitset<4> converted;
	std::bitset<2>left(a);
	std::bitset<2>right(b);	
	int o = 4;
	int left_start = 0;
	for (int i = 0; i < MAX_PERM_4; i++) {
		if (i < 2) {
			converted.set(i, right[i]);	
		}else {
			converted.set(i, left[left_start++]);
		}
	}
	return converted;
}

std::bitset<4> Encrypt::split_plaintext_right(std::bitset<8> ip) {
	std::bitset<4> right;
	int k = MAX_PERM_4;
	for (int i = 0; i < 4; i++) {
		right.set(i, ip[i]);
	}
	return right;
}
std::bitset<4> Encrypt::split_plaintext_left(std::bitset<8> ip) {
	std::bitset<4> left;
	int k = 0;
	for (int i =4; i < 8; i++){
		left.set(k++, ip[i]);
	}

	return left;
}

std::bitset<8>Encrypt::combine_result(std::bitset<4>left, std::bitset<4>right){
	std::bitset<8> result;
	int o = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		if (i < 4) {
			result.set(i, right[i]);
		}
		if (i >= 4) {
			result.set(i, left[o++]);
		}
	}
	return result;
}


std::bitset<8> Encrypt::fk_enrypt_word(std::bitset<8> ip) {
	// fk(L,R)=(L XOR F(R,SK), R)
	std::bitset<4> left = split_plaintext_left(ip);
	std::bitset<4> right = split_plaintext_right(ip);


	// Round 1
	std::bitset<4> fk_compute = Fun(right, key1);
	std::bitset<4> fk_computed_left = left_xor_operation(left, fk_compute);
	
	// Left: right(ip)  Right: fk_computed_left
	// Round 2 
	std::bitset<4> fk_compute_2 = Fun(fk_computed_left, key2);
	std::bitset<4> fk_computed_left_2 = left_xor_operation(right, fk_compute_2);
	return combine_result(fk_computed_left_2, fk_computed_left);
}

std::bitset<8> Encrypt::fk_decrypt_word(std::bitset<8> cp) {
	// fk(L,R)=(L XOR F(R,SK), R)
	std::bitset<4> left = split_plaintext_left(cp);
	std::bitset<4> right = split_plaintext_right(cp);

	// Round 2 
	std::bitset<4> fk_compute_2 = Fun(right, key2);
	std::bitset<4> fk_computed_left_2 = left_xor_operation(left, fk_compute_2); // Right
	
	// Round 1
	std::bitset<4> fk_compute = Fun(fk_computed_left_2, key1);
	std::bitset<4> fk_computed_left = left_xor_operation(right, fk_compute);
	return combine_result(fk_computed_left,fk_computed_left_2);
}



