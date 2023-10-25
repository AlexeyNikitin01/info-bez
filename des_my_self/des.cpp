#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int PC_2[48] = { 
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int PC_1[56] = {
    57, 49, 41, 33, 25, 17, 9 , 1 , 58, 50, 42, 34, 26, 18,
    10, 2 , 59, 51, 43, 35, 27, 19, 11, 3 , 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7 , 62, 54, 46, 38, 30, 22,
    14, 6 , 61, 53, 45, 37, 29, 21, 13, 5 , 28, 20, 12, 4 ,
};


// bitset<28> leftshift(bitset<28> block, int shift) {
//     bitset<28> temp = block;
//     if (shift == 1) {
// 		for (int i = 0; i < 27; i++)
// 		{
// 			if (i - shift < 0)
// 				block[i - shift + 28] = temp[i];
// 			else
// 				block[i] = temp[i + shift];
// 		}
// 	}
// 	if (shift == 2)
// 	{
// 		for (int i = 0; i < 26; i++)
// 		{
// 			if (i - shift < 0)
// 				block[i - shift + 28] = temp[i];
// 			else
// 				block[i] = temp[i + shift];
// 		}
// 	}
// 	return block;
// }

// void keys(char key[8], bitset<48> keysForDes[16]) {
//     int shiftBits[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
//     bitset<56> permationFirstKey;
//     bitset<28> left;
//     bitset<28> right;
//     bitset<48> currentKey;
//     bitset<48> subkey[16];
//     bitset<64> keyBit;

//     // key to bit
// 	int x = 0;
// 	for (int i = 0; i < 8; i++)
// 	{
// 		int num = int(key[i]);
// 		bitset<8> temp(num);
// 		for (int j = 7; j >= 0; j--)
// 		{
// 			keyBit[x + j] = temp[7 - j];
// 		}
// 		x += 8;
//     }

//     // первая замена IP для ключа
//     for (int i=0; i < 56; i++) {
//         permationFirstKey[i] = keyBit[IP[i]-1];
//     }

//     // 16 раундов для ключа
//     for (int round = 0; round < 16; round++) {
//         // 2 блока ключа
//         for (int i = 0; i < 28; i++)
// 			left[i] = permationFirstKey[i];
// 		for (int i = 28; i < 56; i++)
// 			right[i - 28] = permationFirstKey[i];
        
//         // сдвиг каждого блока
//         left = leftshift(left, shiftBits[round]);
// 		right = leftshift(right, shiftBits[round]);
//         // соединение ключа в 56 бит
//         for (int i=0; i < 28; i++)
// 			permationFirstKey[i] = left[i];
// 		for (int i = 28; i < 56; i++)
// 			permationFirstKey[i] = right[i - 28];
//         // финишная перестановка
// 		for (int i = 0; i < 48; i++)
// 		{
// 			int m = FP[i];
// 			currentKey[i] = permationFirstKey[m - 1];
// 		}                                   
		
// 		subkey[round] = currentKey;
//     }
//     for (int i=0; i<16; i++)
//         cout << subkey[i] << endl;
// }


// int main() {
//     char key[8] = {'D', 'E', 'S', 'k', 'e', 'y', '5', '6'};
//     bitset<48> keysForDes[16];
//     keys(&key[8], keysForDes);
// }

bitset<28> leftshift(bitset<28> k, int shift) {
	bitset<28> temp = k;
	if (shift == 1)
	{
		for (int i = 0; i < 27; i++)
		{
			if (i - shift < 0)
				k[i - shift + 28] = temp[i];
			else
				k[i] = temp[i + shift];
		}
	}
	if (shift == 2)
	{
		for (int i = 0; i < 26; i++)
		{
			if (i - shift < 0)
				k[i - shift + 28] = temp[i];
			else
				k[i] = temp[i + shift];
		}
	}
	return k;
}

bitset<64> char_to_bit(const char s[8]) {
	bitset<64> bits;
	int x = 0;
	for (int i = 0; i < 8; i++)
	{
		int num = int(s[i]);
		bitset<8> temp(num);
		for (int j = 7; j >= 0; j--)
		{
			bits[x + j] = temp[7 - j];
		}
		x += 8;
	}
	return bits;
}

void generateKeys(const char s[8]) {
     // Циклический сдвиг влево
    int shiftBits[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
	bitset<56> real_key;
	bitset<28> left;
	bitset<28> right;
	bitset<48> compressKey;
    bitset<48> subkey[16];

    bitset<64> key = char_to_bit(s);
 
	 // Во-первых, после выбора и замены ПК-1 удаляем 8-битный бит четности исходного ключа
	 // И переставляем
	for (int i = 0; i < 56; i++)
		real_key[i] = key[PC_1[i] - 1];
 
	for (int round = 0; round < 16; round++)
	{
		for (int i = 0; i < 28; i++)
			left[i] = real_key[i];
		for (int i = 28; i < 56; i++)
			right[i - 28] = real_key[i];
		 // Сдвиг влево
		left = leftshift(left, shiftBits[round]);
		right = leftshift(right, shiftBits[round]);
		 // Подключаем, заменяем и выбираем ПК-2 для перестановки и сжатия
		for (int i=0; i < 28; i++)
			real_key[i] = left[i];
		for (int i = 28; i < 56; i++)
			real_key[i] = right[i - 28];
		for (int i = 0; i < 48; i++)
		{
			int m = PC_2[i];
			compressKey[i] = real_key[m - 1];
		}                                   
		
		subkey[round] = compressKey;
	}
 
}

int main() {
    char key[8] = {'D', 'E', 'S', 'k', 'e', 'y', '5', '6'};
    generateKeys(key);
}
