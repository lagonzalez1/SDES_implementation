
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
//C:\Users\lgonz\Documents\Code\C++\SDES_implementation\Documents\Interview practice\SDES\KeyGen.h

class KeyGen {
	public:
		// 
		int toHash[10] = {1,0,1,0,0,0,0,0,1,0};
		int input[10];
		void permute();
		void left_rotate();		
		std::bitset<8> getKey1Bit();
		std::bitset<8> getKey2Bit();

		KeyGen() {
			permute();
		}

	private:
		const int MAX = 10;
		const int MID = 5;
		const int MAX_HASH = 8;
		const int permuteHash8[8] = {6,3,7,4,8,5,10,9};
		const int permuteHash10[10] = {3,5,2,7,4,10,1,9,8,6};



};

// Shuffle starting point
void KeyGen::permute() { 
	for(int i = 0; i < MAX; i ++) {
		int value = toHash[permuteHash10[i] - 1];
		input[i] = value;
	}
}

std::bitset<8> KeyGen::getKey1Bit(){
	std::bitset<8> bit;
	left_rotate();
	std::cout << bit << std::endl;
	int lsb = MAX_HASH;
	for (int i = 0; i < MAX_HASH; i++) {
		int value = input[permuteHash8[i] - 1];
		bit.set(--lsb,value);
	}
	return bit;
}

std::bitset<8> KeyGen::getKey2Bit(){ 
	std::bitset<8> bit;
	left_rotate();
	left_rotate();
	int lsb = MAX_HASH;
	for ( int i = 0; i < MAX_HASH; i++ ) {
		bit.set(--lsb, input[permuteHash8[i] - 1]);
	}
	return bit;
}

// Rotate from first 5 elements and middle to end elements.
void KeyGen::left_rotate() {
	int firstValue = input[0];
	for (int i = 0; i < 5; i++){
		input[i] = input[i+1];
	}
	input[MID-1] = firstValue;
	int middleValue = input[MID];
	for (int k = MID; k < MAX; k++) {
		input[k] = input[k+1];
	}
	input[MAX-1] = middleValue;

}

