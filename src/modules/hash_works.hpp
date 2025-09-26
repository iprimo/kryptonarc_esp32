//////////////////////////////////////////////////
//  First, install js-sha3 via npm if needed:
// // npm install js-sha3
// const { sha3_256 } = require('js-sha3');
// // Usage:
// function generateSHA3_256(input) {
//   return sha3_256(input); // returns hex string
// }
// // Example:
// console.log(generateSHA3_256("your input string"));

//////////////////////////////////////////////////
// // First, install js-sha512 via npm if needed:
// // npm install js-sha512
// const { sha512 } = require('js-sha512');
// // Usage:
// function generateSHA512Hex(input) {
//   return sha512(input); // returns hex string
// }
// // Example:
// console.log(generateSHA512Hex("your input string"));


#ifndef hash_works_HPP
#define hash_works_HPP

#include "MD5Builder.h"

#include "mbedtls/sha512.h"

// --- SHA3-256 (Keccak) minimal implementation ---
#include <stdint.h>
#include <string>


// Helper: Convert bytes to hex string
inline std::string bytesToHex(const uint8_t* bytes, size_t len) {
  static const char hex[] = "0123456789abcdef";
  std::string out;
  out.reserve(len * 2);
  for (size_t i = 0; i < len; ++i) {
    out.push_back(hex[bytes[i] >> 4]);
    out.push_back(hex[bytes[i] & 0xF]);
  }
  return out;
}

// Generate SHA-512 hash as hex string
inline std::string generateSHA512Hex(const char* str) {
  uint8_t hash[64];
  mbedtls_sha512_context ctx;
  mbedtls_sha512_init(&ctx);
  mbedtls_sha512_starts_ret(&ctx, 0); // 0 = SHA-512, 1 = SHA-384
  mbedtls_sha512_update_ret(&ctx, reinterpret_cast<const unsigned char*>(str), strlen(str));
  mbedtls_sha512_finish_ret(&ctx, hash);
  mbedtls_sha512_free(&ctx);
  return bytesToHex(hash, 64);
}




// Tiny Keccak implementation (public domain) - only what is needed for SHA3-256
extern "C" {
// Forward declaration for C linkage
void keccak_256(const uint8_t *in, size_t inlen, uint8_t *md);
}

// Generate SHA3-256 hash as hex string
inline std::string generateSHA3_256(const char* str) {
  uint8_t hash[32];
  keccak_256(reinterpret_cast<const uint8_t*>(str), strlen(str), hash);
  return bytesToHex(hash, 32);
}

String generateMD5Hash(const char* str) {
  MD5Builder md5;
  md5.begin();
  md5.add(str);
  md5.calculate();
  // Serial.println(" ***  ***  ***  ***  *** str *** : ");
  // Serial.print(str);
  // Serial.println(" ***  ***  ***  ***  *** md5.toString() *** : ");
  // Serial.print(md5.toString());
  
  return md5.toString();
}


// --- Minimal Keccak implementation for SHA3-256 ---
#ifdef __cplusplus
extern "C" {
#endif

#define KECCAKF_ROUNDS 24
static const uint64_t keccakf_rndc[24] = {
  0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL,
  0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL,
  0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL,
  0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL,
  0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL,
  0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL,
  0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL,
  0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};
static const int keccakf_rotc[24] = {
  1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 2, 14, 27, 41, 56, 8, 25, 43, 62, 18, 39, 61, 20, 44
};
static const int keccakf_piln[24] = {
  10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, 2, 20, 14, 22, 9, 6, 1
};

static void keccakf(uint64_t st[25]) {
  int i, j, round;
  uint64_t t, bc[5];
  for (round = 0; round < KECCAKF_ROUNDS; round++) {
    for (i = 0; i < 5; i++)
      bc[i] = st[i] ^ st[i + 5] ^ st[i + 10] ^ st[i + 15] ^ st[i + 20];
    for (i = 0; i < 5; i++) {
      t = bc[(i + 4) % 5] ^ ((bc[(i + 1) % 5] << 1) | (bc[(i + 1) % 5] >> (64 - 1)));
      for (j = 0; j < 25; j += 5)
        st[j + i] ^= t;
    }
    t = st[1];
    for (i = 0; i < 24; i++) {
      j = keccakf_piln[i];
      bc[0] = st[j];
      st[j] = (t << keccakf_rotc[i]) | (t >> (64 - keccakf_rotc[i]));
      t = bc[0];
    }
    for (j = 0; j < 25; j += 5) {
      for (i = 0; i < 5; i++)
        bc[i] = st[j + i];
      for (i = 0; i < 5; i++)
        st[j + i] ^= (~bc[(i + 1) % 5]) & bc[(i + 2) % 5];
    }
    st[0] ^= keccakf_rndc[round];
  }
}

void keccak_256(const uint8_t *in, size_t inlen, uint8_t *md) {
  uint64_t st[25];
  uint8_t temp[136];
  size_t i, rsiz = 136, rsizw = rsiz / 8;
  memset(st, 0, sizeof(st));
  while (inlen >= rsiz) {
    for (i = 0; i < rsizw; i++)
      ((uint64_t *)st)[i] ^= ((uint64_t *)in)[i];
    keccakf(st);
    in += rsiz;
    inlen -= rsiz;
  }
  memset(temp, 0, rsiz);
  memcpy(temp, in, inlen);
  temp[inlen++] = 0x06;
  temp[rsiz - 1] |= 0x80;
  for (i = 0; i < rsizw; i++)
    ((uint64_t *)st)[i] ^= ((uint64_t *)temp)[i];
  keccakf(st);
  for (i = 0; i < 32; i++)
    md[i] = ((uint8_t *)st)[i];
}

#ifdef __cplusplus
}
#endif

#endif // hash_works_HPP