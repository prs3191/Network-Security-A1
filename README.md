# Network-Security-A1
# Prog A
Implement the RC4 code given on page 93. Try out the code with
different key values to convince yourself that the code does generate random
octets. [This code has a minor bug that you must fix otherwise you will see a lot
of zeros.] Using the key “zxcvb”, and ignoring the first 512 octets, encrypt the
message “This class is easier than I thought.” and turn in your code as well as the
encrypted output.
# Prog B
Program a secret key encryption and decryption method based on the
following:
- Your program must take an array of 8 characters as an input and output an array
of 8 encrypted characters.
- Write the code necessary to create 8 unique random substitution tables, one for
each character of the array.
- Your methods must use a 64-bit key (can be represented as another array of 8
characters) derived from an 8-character password.
- Encryption algorithm: Take the input array and xor it with the key. Using the
xored output, perform a character-by-character substitution using the different
substitution tables. Perform the permutation step once after the substitution step.
For the permutation step, (circular) shift the bit pattern by one to the left with the
leftmost bit becoming the rightmost bit. Repeat the above steps 16 times,
corresponding to 16 rounds, with the output of a round serving as the input for the
next round.
- Decryption algorithm: Reverse the encryption algorithm. The permutation,
however, should (circular) shift the bit pattern by 1 bit to the right. The
substitution tables are used for reversing the substitution.
Take a sample input bit pattern (represented as an array of 8 characters) and produce the
encrypted output pattern. Feed the encrypted output pattern to your decryption function to
obtain the input bit pattern. Match the two patterns to ensure that your decryption indeed
reverses your encryption. Do the same by changing only one bit in the input pattern. You
must include print statements in your code to print the input, per round encrypted output,
and per round decrypted output in an output file for both input bit patterns.
