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
#include "../SDES_/helper.h"


// William Stallings Simplififed DES 
// By: Luis Gonzalez



void print_keys(std::bitset<8> &key1, std::bitset<8> &key2) {
	std::cout << "Key 1: " << key1 << std::endl;
	std::cout << "Key 2: " << key2 << std::endl;
}

std::string show_string_to_binary (std::string input) {
	std::string encrypted_string = "";
	for (char &_char: input){
		encrypted_string += std::bitset<8>(_char).to_string();
	}
	return encrypted_string;
}

std::vector<std::bitset<8> > append_bits_to_encrypt(std::string &input) {
	std::vector<std::bitset<8> > char_bits;
	char_bits.reserve(input.size());
	for (char ch : input) {
		std::bitset<8> char_value(ch);
		char_bits.push_back(char_value);
	}
	return char_bits;
}

void show_encrypted_bits(std::vector<std::bitset<8> > encrypted) {
	std::string encrypted_string = "";
	for (int i = 0; i < encrypted.size(); i ++) {
		encrypted_string += encrypted[i].to_string();
	}
	std::cout << "Encrypted bits" << std::endl;
	std::cout << encrypted_string << std::endl;
}

void show_encrypted_text_char (std::vector<std::bitset<8> > encrypted) {
	std::string encrypted_string = "";
	for (int i = 0; i < encrypted.size(); i ++) {
		encrypted_string += char(encrypted[i].to_ulong());
	}
	std::cout << "Encrypted text" << std::endl;
	std::cout << encrypted_string << std::endl;
}

void show_decrypted_text(std::vector<std::bitset<8> > decrypted){
	std::string decrypted_string = "";
	for (int i = 0; i < decrypted.size(); i ++) {
		decrypted_string += decrypted[i].to_string();
	}
	std::cout << "Decrypted binary " << std::endl;
	std::cout << decrypted_string << std::endl;
}

void show_text_decrypted(std::vector<std::bitset<8> > decrypted) {
	std::string value = "";
	for(int i = 0; i < decrypted.size(); i++ ){
		value += char(decrypted[i].to_ulong());
	}
	std::cout << value << std::endl;
}

int main() {
	KeyGen key;
	std::bitset<8> k1 = key.getKey1Bit();
	std::bitset<8> k2 = key.getKey2Bit();
	print_keys(k1, k2);
	Encrypt enrypt(k1, k2);

	
	std::string input;
	std::cout << "Enter some text (hit enter when complete)" << std::endl;
	std::getline(std::cin, input);
	std::cout << "Your text to binary: " << std::endl;
	std::cout << show_string_to_binary(input) << std::endl;
	std::vector<std::bitset<8> > v = append_bits_to_encrypt(input);
	std::cout << "Total characters to encrypt: " << v.size() << std::endl;
	std::vector<std::bitset<8> > encrypted_bits;
	encrypted_bits.reserve(v.size());
	for (int i = 0; i < v.size(); i++) {
		encrypted_bits.push_back(enrypt.fk_enrypt_word(v[i]));
	}
	show_encrypted_bits(encrypted_bits);
	show_encrypted_text_char(encrypted_bits);

	std::vector<std::bitset<8> > decrypted;
	decrypted.reserve(v.size());
	for (int i = 0; i < v.size(); i++) {
		decrypted.push_back(enrypt.fk_decrypt_word(encrypted_bits[i]));
	}
	show_decrypted_text(decrypted);
	show_text_decrypted(decrypted);

	return 0;
}




