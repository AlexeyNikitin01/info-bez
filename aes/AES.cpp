#include <string>
#include <cstring>
#include <iostream>
#include "table.hpp"

using namespace std;

void CheckLength(unsigned int len) {
  if (len % 16 != 0) {
    throw length_error("Plaintext length must be divisible by " + to_string(16));
  }
}

void SubBytes(unsigned char state[4][4]) {
  unsigned int i, j;
  unsigned char t;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      t = state[i][j];
      state[i][j] = sbox[t / 16][t % 16];
    }
  }
}

void ShiftRow(unsigned char state[4][4], unsigned int i,
                   unsigned int n)  // shift row i on n positions
{
  unsigned char tmp[4];
  for (unsigned int j = 0; j < 4; j++) {
    tmp[j] = state[i][(j + n) % 4];
  }
  memcpy(state[i], tmp, 4 * sizeof(unsigned char));
}

void ShiftRows(unsigned char state[4][4]) {
  ShiftRow(state, 1, 1);
  ShiftRow(state, 2, 2);
  ShiftRow(state, 3, 3);
}

unsigned char xtime(unsigned char b)  // multiply on x
{
  return (b << 1) ^ (((b >> 7) & 1) * 0x1b);
}

void MixColumns(unsigned char state[4][4]) {
  unsigned char temp_state[4][4];

  for (size_t i = 0; i < 4; ++i) {
    memset(temp_state[i], 0, 4);
  }

  for (size_t i = 0; i < 4; ++i) {
    for (size_t k = 0; k < 4; ++k) {
      for (size_t j = 0; j < 4; ++j) {
        if (CMDS[i][k] == 1)
          temp_state[i][j] ^= state[k][j];
        else
          temp_state[i][j] ^= GF_MUL_TABLE[CMDS[i][k]][state[k][j]];
      }
    }
  }

  for (size_t i = 0; i < 4; ++i) {
    memcpy(state[i], temp_state[i], 4);
  }
}

void AddRoundKey(unsigned char state[4][4], unsigned char *key) {
  unsigned int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      state[i][j] = state[i][j] ^ key[i + 4 * j];
    }
  }
}

void SubWord(unsigned char *a) {
  int i;
  for (i = 0; i < 4; i++) {
    a[i] = sbox[a[i] / 16][a[i] % 16];
  }
}

void RotWord(unsigned char *a) {
  unsigned char c = a[0];
  a[0] = a[1];
  a[1] = a[2];
  a[2] = a[3];
  a[3] = c;
}

void XorWords(unsigned char *a, unsigned char *b, unsigned char *c) {
  int i;
  for (i = 0; i < 4; i++) {
    c[i] = a[i] ^ b[i];
  }
}

void Rcon(unsigned char *a, unsigned int n) {
  unsigned int i;
  unsigned char c = 1;
  for (i = 0; i < n - 1; i++) {
    c = xtime(c);
  }

  a[0] = c;
  a[1] = a[2] = a[3] = 0;
}

void KeyExpansion(const unsigned char key[], unsigned char w[]) {
  unsigned char temp[4];
  unsigned char rcon[4];

  unsigned int i = 0;
  while (i < 4 * 4) {
    w[i] = key[i];
    i++;
  }

  i = 4 * 4;
  while (i < 4 * 4 * (10 + 1)) {
    temp[0] = w[i - 4 + 0];
    temp[1] = w[i - 4 + 1];
    temp[2] = w[i - 4 + 2];
    temp[3] = w[i - 4 + 3];

    if (i / 4 % 4 == 0) {
      RotWord(temp);
      SubWord(temp);
      Rcon(rcon, i / (4 * 4));
      XorWords(temp, rcon, temp);
    } else if (4 > 6 && i / 4 % 4 == 4) {
      SubWord(temp);
    }

    w[i + 0] = w[i - 4 * 4] ^ temp[0];
    w[i + 1] = w[i + 1 - 4 * 4] ^ temp[1];
    w[i + 2] = w[i + 2 - 4 * 4] ^ temp[2];
    w[i + 3] = w[i + 3 - 4 * 4] ^ temp[3];
    i += 4;
  }
}

void InvSubBytes(unsigned char state[4][4]) {
  unsigned int i, j;
  unsigned char t;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      t = state[i][j];
      state[i][j] = inv_sbox[t / 16][t % 16];
    }
  }
}

void InvMixColumns(unsigned char state[4][4]) {
  unsigned char temp_state[4][4];

  for (size_t i = 0; i < 4; ++i) {
    memset(temp_state[i], 0, 4);
  }

  for (size_t i = 0; i < 4; ++i) {
    for (size_t k = 0; k < 4; ++k) {
      for (size_t j = 0; j < 4; ++j) {
        temp_state[i][j] ^= GF_MUL_TABLE[INV_CMDS[i][k]][state[k][j]];
      }
    }
  }

  for (size_t i = 0; i < 4; ++i) {
    memcpy(state[i], temp_state[i], 4);
  }
}

void InvShiftRows(unsigned char state[4][4]) {
  ShiftRow(state, 1, 4 - 1);
  ShiftRow(state, 2, 4 - 2);
  ShiftRow(state, 3, 4 - 3);
}

void XorBlocks(const unsigned char *a, const unsigned char *b,
                    unsigned char *c, unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    c[i] = a[i] ^ b[i];
  }
}

void EncryptBlock(const unsigned char in[], unsigned char out[],
                       unsigned char *roundKeys) {
  unsigned char state[4][4];
  unsigned int i, j, round;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      state[i][j] = in[i + 4 * j];
    }
  }

  AddRoundKey(state, roundKeys);

  for (round = 1; round <= 10 - 1; round++) {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, roundKeys + round * 4 * 4);
  }

  SubBytes(state);
  ShiftRows(state);
  AddRoundKey(state, roundKeys + 10 * 4 * 4);

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      out[i + 4 * j] = state[i][j];
    }
  }
}

void DecryptBlock(const unsigned char in[], unsigned char out[],
                       unsigned char *roundKeys) {
  unsigned char state[4][4];
  unsigned int i, j, round;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      state[i][j] = in[i + 4 * j];
    }
  }

  AddRoundKey(state, roundKeys + 10 * 4 * 4);

  for (round = 10 - 1; round >= 1; round--) {
    InvSubBytes(state);
    InvShiftRows(state);
    AddRoundKey(state, roundKeys + round * 4 * 4);
    InvMixColumns(state);
  }

  InvSubBytes(state);
  InvShiftRows(state);
  AddRoundKey(state, roundKeys);

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      out[i + 4 * j] = state[i][j];
    }
  }
}
