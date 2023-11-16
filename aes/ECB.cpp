// #include <string>
// #include <cstring>
// #include <iostream>
// #include "AES.cpp"

// using namespace std;

// int main() {
//     unsigned char plain[16] = {'a', 'b', 'c', 'z', 'd', 'g', 'h', 'q', 'i', 'k', 'l', 'h', 'q', 'x', 'z', 'b'};
//     // unsigned char *plain = new unsigned char;
//     // plain = getRandomPlain(1600);
//     cout << "plain" << endl; 
//     cout << plain << endl;
//     for (auto i : plain) cout << i;
//     unsigned char key[16] = {'a', 'b', 'c', 'd', 'b', 'c', 'd', 'b', 'c', 'd', 'b', 'c', 'd', 'b', 'c', 'd'};
//     unsigned char *out = new unsigned char;
//     out = EncryptECB(plain, 16, key);
//     cout << "cheper" << endl;
//     cout << out << endl;
//     out = DecryptECB(out, 16, key);
//     cout << "dec" << endl;
//     for (int i=0; i<16; i++) cout << out[i];
// }

#include <iostream>
#include <sys/time.h>
#include <ctime>
#include "table.hpp"
#include "AES.cpp"
#include "tools.cpp"

using namespace std;

unsigned char* EncryptECB(const unsigned char in[], unsigned int inLen, const unsigned char key[]) {
  CheckLength(inLen);
  unsigned char *out = new unsigned char[inLen];
  unsigned char *roundKeys = new unsigned char[4 * 4 * (10 + 1)];
  KeyExpansion(key, roundKeys);
  for (unsigned int i = 0; i < inLen; i += 16) {
    EncryptBlock(in + i, out + i, roundKeys);
  }

  delete[] roundKeys;

  return out;
}

unsigned char *DecryptECB(const unsigned char in[], unsigned int inLen, const unsigned char key[]) {
  CheckLength(inLen);
  unsigned char *out = new unsigned char[inLen];
  unsigned char *roundKeys = new unsigned char[4 * 4 * (10 + 1)];
  KeyExpansion(key, roundKeys);
  for (unsigned int i = 0; i < inLen; i += 16) {
    DecryptBlock(in + i, out + i, roundKeys);
  }

  delete[] roundKeys;

  return out;
}

int main() {
    const unsigned int MEGABYTE = 1024 * 1024 * sizeof(unsigned char);

    unsigned int megabytesCount = 100;
    unsigned int plainLength = megabytesCount * MEGABYTE;
    unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    cout << "Start speedtest" << endl;
    srand(time(nullptr));

    unsigned char *plain = getRandomPlain(plainLength);
    
    unsigned long start = getMicroseconds();
    unsigned char *out = EncryptECB(plain, plainLength, key);
    unsigned long delta = getMicroseconds() - start;

    double speed = (double)megabytesCount / delta * MICROSECONDS;

    printf("%.2f Mb/s\n", speed);

    delete[] plain;
    delete[] out;
}