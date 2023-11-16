#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void swap(unsigned char *s, int j, int i) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void rc4(unsigned char *key, int klen) {
    unsigned char s[256];
    for (int i=0; i<256; i++)
        s[i] = i;
    int j = 0;
    for (int i=0; i<256; i++) {
        j = (j + s[i] + key[i % klen]) % 256;
        swap(s, j, i);
    }

    j = 0;
    int i = 0;
    ifstream inFile("input.txt");
    ofstream outFile("out.txt");
    char byte;
    while (inFile.read(&byte, sizeof(char))) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        int t = (s[i] + s[j]) % 256;
        unsigned char k = s[t];
        char result = (byte ^ k);
        outFile.write(&result, sizeof(char));
    }
    inFile.close();
    outFile.close();
    cout << "ok";
}

int main() {
    unsigned char input;
    unsigned char key[10] = {'a', 'b', 'c', 'b', 'c', 'b', 'c', 'b', 'c', 'b'};
    unsigned char output;
    int klen = 10;
    cout << "here";
    rc4(key, klen);
}