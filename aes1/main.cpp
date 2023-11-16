#include <iostream>
#include <string>

using namespace std;

void AddRoundKey(unsigned char state[4][4], unsigned char *key) {

}

int main() {
    unsigned char text[16] = {'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D'}; // 128 БИТ
    unsigned char key[16] = {'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D'}; // ключ 128 бит

    unsigned char state[4][4];
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            state[i][j] = text[i + j*4];
        }
    }
    unsigned char roundKeys[10];
    AddRoundKey(state, roundKeys[0]);
}