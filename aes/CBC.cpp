#include <iostream>
#include <cstring>
#include <string>
#include "AES.cpp"
#include "tools.cpp"
#include <ctime>

using namespace std;

unsigned char *EncryptCBC(const unsigned char in[], unsigned int inLen, const unsigned char key[], const unsigned char *iv) {
    CheckLength(inLen);
    unsigned char *out = new unsigned char[inLen];
    unsigned char block[16];
    unsigned char *roundKeys = new unsigned char[4 * 4 * (10 + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, 16);
    for (unsigned int i = 0; i < inLen; i += 16) {
      XorBlocks(block, in + i, block, 16);
      EncryptBlock(block, out + i, roundKeys);
      memcpy(block, out + i, 16);
    }

    delete[] roundKeys;

    return out;
}

unsigned char *DecryptCBC(const unsigned char in[], unsigned int inLen, const unsigned char key[], const unsigned char *iv) {
    CheckLength(inLen);
    unsigned char *out = new unsigned char[inLen];
    unsigned char block[16];
    unsigned char *roundKeys = new unsigned char[4 * 4 * (10 + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, 16);
    for (unsigned int i = 0; i < inLen; i += 16) {
      DecryptBlock(in + i, out + i, roundKeys);
      XorBlocks(block, out + i, out + i, 16);
      memcpy(block, in + i, 16);
    }

    delete[] roundKeys;

    return out;
}

int main() {
    unsigned char iv[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    const unsigned int MEGABYTE = 1024 * 1024 * sizeof(unsigned char);

    unsigned int megabytesCount = 100;
    unsigned int plainLength = megabytesCount * MEGABYTE;
    unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    cout << "Start speedtest" << endl;
    srand(time(nullptr));

    unsigned char *plain = getRandomPlain(plainLength);
    
    unsigned long start = getMicroseconds();
    unsigned char *out = EncryptCBC(plain, plainLength, key, iv);
    unsigned long delta = getMicroseconds() - start;

    double speed = (double)megabytesCount / delta * MICROSECONDS;

    printf("%.2f Mb/s\n", speed);
}
