#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

/**
 * @brief Determines the number of AES rounds based on the key size
 *
 * @param keySize Key size in bits (128, 192, or 256)
 * @return unsigned int Number of rounds (10 for 128-bit, 12 for 192-bit, 14 for 256-bit keys)
 */
unsigned int numRounds(unsigned int keySize);

/**
 * @brief Determines the number of 32-bit words in the key
 *
 * @param keySize Key size in bits (128, 192, or 256)
 * @return unsigned int Number of 32-bit words (4 for 128-bit, 6 for 192-bit, 8 for 256-bit keys)
 */
unsigned int numKeyWords(unsigned int keySize);

/**
 * @brief Retrieves a value from the AES S-Box
 *
 * The S-Box (Substitution Box) is used in the SubBytes step of AES encryption
 *
 * @param num Byte value to look up in the S-Box (0-255)
 * @return u_int8_t Substituted byte value from the S-Box
 */
u_int8_t getSBoxValue(u_int8_t num);

/**
 * @brief Retrieves a value from the inverse AES S-Box
 *
 * The inverse S-Box is used in the InvSubBytes step of AES decryption
 *
 * @param num Byte value to look up in the inverse S-Box (0-255)
 * @return u_int8_t Substituted byte value from the inverse S-Box
 */
u_int8_t getSBoxInvert(u_int8_t num);

/**
 * @brief Calculates the round constant for the key schedule
 *
 * The round constant is used in the key expansion process and is calculated as
 * x^(i-1) in the Galois Field GF(2^8)
 *
 * @param num Round number (1-10 for AES-128, 1-12 for AES-192, 1-14 for AES-256)
 * @return u_int8_t Round constant value
 */
u_int8_t rc(u_int8_t num);

/**
 * @brief Expands the original cipher key into the round keys
 *
 * This function generates the round key material necessary for the AddRoundKey
 * operation during encryption and decryption.
 *
 * @param key Pointer to the original cipher key (16, 24, or 32 bytes)
 * @param roundKeys Pointer to memory where the expanded key will be stored
 *                  (16*(rounds+1) bytes, where rounds depends on the key size)
 * @param keySize Key size in bits (128, 192, or 256)
 */
void keyExpansion(u_int8_t *key, u_int8_t *roundKeys, unsigned int keySize);

/**
 * @brief Extracts a specific round key from the expanded key material
 *
 * @param roundKeys Pointer to the expanded key material produced by keyExpansion()
 * @param roundKey Pointer to memory where the 16-byte round key will be stored
 * @param round The round number (0 to rounds, where round 0 is the initial key addition)
 */
void getRoundKey(u_int8_t *roundKeys, u_int8_t *roundKey, u_int8_t round);

/**
 * @brief Performs the AddRoundKey operation
 *
 * XORs the state matrix with the round key
 *
 * @param state Pointer to the 16-byte AES state matrix
 * @param roundKey Pointer to the 16-byte round key
 */
void addRoundKey(u_int8_t *state, u_int8_t *roundKey);

/**
 * @brief Performs the SubBytes operation
 *
 * Substitutes each byte in the state matrix with its corresponding value in the S-Box
 *
 * @param state Pointer to the 16-byte AES state matrix
 */
void subBytes(u_int8_t *state);

/**
 * @brief Performs the ShiftRows operation
 *
 * Cyclically shifts the bytes in each row of the state matrix to the left
 * - Row 0: No shift
 * - Row 1: Shift left by 1
 * - Row 2: Shift left by 2
 * - Row 3: Shift left by 3
 *
 * @param state Pointer to the 16-byte AES state matrix
 */
void shiftRows(u_int8_t *state);

/**
 * @brief Multiplies a byte by 2 in the Galois Field GF(2^8)
 *
 * Used as part of the MixColumns operation. Multiplication by 2 is a left shift
 * followed by a conditional XOR with 0x1B if the result overflows.
 *
 * @param state Pointer to the 16-byte AES state matrix
 */
void multiply2(u_int8_t *state);

/**
 * @brief Multiplies a byte by 3 in the Galois Field GF(2^8)
 *
 * Used as part of the MixColumns operation. Multiplication by 3 is
 * calculated as: 3*x = 2*x ⊕ x
 *
 * @param state Pointer to the 16-byte AES state matrix
 */
void multiply3(u_int8_t *state);

/**
 * @brief Performs the MixColumns operation
 *
 * Multiplies each column of the state matrix by a fixed polynomial
 * c(x) = 3x^3 + x^2 + x + 2 in the Galois Field GF(2^8)
 *
 * @param state Pointer to the 16-byte AES state matrix
 */
void mixColumns(u_int8_t *state);

/**
 * @brief Encrypts a single 16-byte block using AES
 *
 * Implements the complete AES encryption algorithm for a single 16-byte block:
 * 1. Initial AddRoundKey
 * 2. For each round (except the final round):
 *    - SubBytes
 *    - ShiftRows
 *    - MixColumns
 *    - AddRoundKey
 * 3. Final round (without MixColumns):
 *    - SubBytes
 *    - ShiftRows
 *    - AddRoundKey
 *
 * @param block Pointer to the 16-byte block to encrypt (modified in-place)
 * @param roundKeys Pointer to the expanded key material
 * @param rounds Number of rounds (10 for AES-128, 12 for AES-192, 14 for AES-256)
 */
void encrypt(u_int8_t *block, u_int8_t *roundKeys, unsigned int rounds);

/**
 * @brief Performs the inverse MixColumns operation
 *
 * Multiplies each column of the state matrix by a fixed polynomial
 * c^-1(x) = 9x^3 + 13x^2 + 11x + 14 in the Galois Field GF(2^8)
 *
 * @param state Pointer to the 16-byte AES state matrix
 */
void invMixColumns(u_int8_t *state);

/**
 * @brief Performs the inverse SubBytes operation
 *
 * Substitutes each byte in the state matrix with its corresponding value in the
 * inverse S-Box
 *
 * @param state Pointer to the 16-byte AES state matrix
 */
void invSubBytes(u_int8_t *state);

/**
 * @brief Performs the inverse ShiftRows operation
 *
 * Cyclically shifts the bytes in each row of the state matrix to the right
 * - Row 0: No shift
 * - Row 1: Shift right by 1
 * - Row 2: Shift right by 2
 * - Row 3: Shift right by 3
 *
 * @param state Pointer to the 16-byte AES state matrix
 */
void invShiftRows(u_int8_t *state);

/**
 * @brief Decrypts a single 16-byte block using AES
 *
 * Implements the complete AES decryption algorithm for a single 16-byte block:
 * 1. Initial AddRoundKey
 * 2. For each round (except the final round):
 *    - InvShiftRows
 *    - InvSubBytes
 *    - AddRoundKey
 *    - InvMixColumns
 * 3. Final round (without InvMixColumns):
 *    - InvShiftRows
 *    - InvSubBytes
 *    - AddRoundKey
 *
 * @param block Pointer to the 16-byte block to decrypt (modified in-place)
 * @param roundKeys Pointer to the expanded key material
 * @param rounds Number of rounds (10 for AES-128, 12 for AES-192, 14 for AES-256)
 */
void decrypt(u_int8_t *block, u_int8_t *roundKeys, unsigned int rounds);

/**
 * @brief Encrypts data using AES in Electronic Codebook (ECB) mode
 *
 * ECB mode encrypts each 16-byte block individually. This is the simplest mode
 * but is not recommended for most applications as it doesn't hide data patterns.
 *
 * @param content Pointer to the data to encrypt (modified in-place)
 * @param key Pointer to the encryption key (16, 24, or 32 bytes)
 * @param keySize Key size in bits (128, 192, or 256)
 * @param length Length of the data in bytes (must be a multiple of 16)
 */
void ecb_encrypt(u_int8_t *content, u_int8_t *key, unsigned int keySize, size_t length);

/**
 * @brief Decrypts data using AES in Electronic Codebook (ECB) mode
 *
 * ECB mode decrypts each 16-byte block individually.
 *
 * @param content Pointer to the data to decrypt (modified in-place)
 * @param key Pointer to the decryption key (16, 24, or 32 bytes)
 * @param keySize Key size in bits (128, 192, or 256)
 * @param length Length of the data in bytes (must be a multiple of 16)
 */
void ecb_decrypt(u_int8_t *content, u_int8_t *key, unsigned int keySize, size_t length);

/**
 * @brief Encrypts data using AES in Cipher Block Chaining (CBC) mode
 *
 * CBC mode XORs each plaintext block with the previous ciphertext block
 * before encryption, which helps hide patterns in the plaintext.
 * The first block is XORed with an initialization vector (IV).
 *
 * @param content Pointer to the data to encrypt (modified in-place)
 * @param key Pointer to the encryption key (16, 24, or 32 bytes)
 * @param keySize Key size in bits (128, 192, or 256)
 * @param iv Pointer to the 16-byte initialization vector
 * @param length Length of the data in bytes (must be a multiple of 16)
 */
void cbc_encrypt(u_int8_t *content, u_int8_t *key, unsigned int keySize, u_int8_t *iv, size_t length);

/**
 * @brief Decrypts data using AES in Cipher Block Chaining (CBC) mode
 *
 * CBC mode requires decrypting each block and then XORing with the previous
 * ciphertext block to recover the plaintext. The first block is XORed with
 * the initialization vector (IV).
 *
 * @param content Pointer to the data to decrypt (modified in-place)
 * @param key Pointer to the decryption key (16, 24, or 32 bytes)
 * @param keySize Key size in bits (128, 192, or 256)
 * @param iv Pointer to the 16-byte initialization vector
 * @param length Length of the data in bytes (must be a multiple of 16)
 */
void cbc_decrypt(u_int8_t *content, u_int8_t *key, unsigned int keySize, u_int8_t *iv, size_t length);