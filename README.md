Here is an implementation of SDES encryption algorithm using 2 symetric keys to encrypt/decrypt <br/>

To run:
Compiled on c++ v 14.0.3 <br/>

command: git clone -url-

Run the following commands:

2. command: g++ SDES.cpp -o {fileoutput-name-this}.exe
3. Then execute file on terminal <br/>

command ./{fileoutput-name-this}.exe



<u>Process Key Generation</u><br/>
Symmetric Key Creation:
<br/>
Initialization: First, create two symmetric keys defined by a permutation of 10 values. This permutation allows you to take the value of the initial key in binary at each index and assign it to an empty array of size 10. Since arrays are zero-indexed and the permutation is at +1, subtract 1 from each index value.
Left Rotation:
<br/>
Splitting and Rotating: Split the array into two halves. Perform a left rotation on both the first 5 bits and the last 5 bits. To achieve this, split the array into two, get the value of the first elements, and override the middle element with the first value. Then, iterate through each input and override with the next value, stopping before the swapped value.
Improvement: Use bitset initially, as bit set operations allow for bit shift manipulations (<<=, >>=).
Using Bitset:

Bitset Function: Move to bitset, as it provides methods to simplify bit manipulation. Create a function that returns a bitset by loading the values from least significant to most significant bit. This means iterating to the hash size and setting from hash size - 1 at each step.
<br/>
<u>Process Encryption</u><br/>
Encrypting a Bitset:

Plaintext Value: Take a bitset of size 8 as the plaintext value. Split the plaintext into two bitsets, left and right.
Round 1: XOR the left bitset with the result of a function Fun() that takes the initial key1 and the right bitset of the plaintext.
Round 2: Use the right bitset from the original plaintext as the new left bitset and the computed value L XOR F(R, SK) as the new right bitset. Run the same function with the swapped values but use key2 instead, yielding new bitsets of size 4 for both left and right. Combine the results to get the encrypted value in bits.
<br/>
<u>Process Decryption</u><br/>

Decrypting a Bitset:
<br/>
Inverse Operation: Decryption works as the inverse operation of encryption. Simply run the function inverted from encryption to yield the plaintext in bits.
<br/>
<u>Process Main </u><br/>
Main Class and Functions:
<br/>
Class for Key Generation: Create a class for key generation to generate both keys.
Read Input: Read in a string and parse each character into a bitset. Store each bitset in a vector to process each encryption in a loop.
Decryption: Iterate over the encrypted vector of bits and call the fk_decrypt_word() function to decrypt.



