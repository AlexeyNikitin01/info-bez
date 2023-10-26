#include<bitset>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;
class DES
{
public:
	 bitset <32> F (bitset <32> R, bitset <48> k); // функция F
	 bitset <28> leftshift (bitset <28> k, int); // функция сдвига влево
	 void generateKeys (); // Генерировать 16 48-битных подключей
	 bitset <64> char_to_bit (const char s [8]); // Преобразование символов char в двоичные
	bitset<64> change(bitset<64> temp);
	 bitset <64> DES_encryp (bitset <64> & plain); // шифрование DES 
	 bitset <64> DES_decrypt (bitset <64> & cipher); // Расшифровка DES
	 void get_s (string str) {s = str;} // Получить открытый текст
	 void get_key (string key_t) {k = key_t;} // Получаем ключ
	void show_encryp(void);
	void show_decrypt(void);
	DES();
	~DES();
private:
	 string s; // обычный текст
	 string k; // Ключ
	 bitset <64> key; // 64-битный ключ
	 bitset <48> subkey [16]; // ключ для каждого раунда
 
	int IP[64] =
	{
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9,  1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7
	};
 
	int IP_1[64] = 
	{  
		40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41,  9, 49, 17, 57, 25 
	};
 
	int E[48] = 
	{ 
		32,  1,  2,  3,  4,  5,
		4,  5,  6,  7,  8,  9,
		8,  9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32,  1 
	};

	int S_BOX[8][4][16] = {
		{
			{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
	{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
	{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
	{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
		},
	{
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
	{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
	{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
	{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
	},
	{
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
	{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
	{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
	{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
	},
	{
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
	{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
	{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
	{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
	},
	{
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
	{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
	{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
	{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
	},
	{
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
	{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
	{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
	{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
	},
	{
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
	{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
	{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
	{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
	},
	{
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
	{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
	{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
	{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
	}
	};
 

	int P[32] = 
	{ 
		16,  7, 20, 21,
		29, 12, 28, 17,
		1, 15, 23, 26,
		5, 18, 31, 10,
		2,  8, 24, 14,
		32, 27,  3,  9,
		19, 13, 30,  6,
		22, 11,  4, 25
	};

	int PC_1[56] = 
	{ 
		57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10,  2, 59, 51, 43, 35, 27,
		19, 11,  3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14,  6, 61, 53, 45, 37, 29,
		21, 13,  5, 28, 20, 12,  4 
	};

	int PC_2[48] = 
	{ 
		14, 17, 11, 24,  1,  5,
		3, 28, 15,  6, 21, 10,
		23, 19, 12,  4, 26,  8,
		16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32
	};
 
	int shiftBits[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 }; 
};

DES::DES()
{
}
 
 
DES::~DES()
{
}
 
bitset<32> DES::F(bitset<32> R, bitset<48> k) {
	// Расширение электронного блока
	bitset<48> expandR;  
	for (int i = 0; i < 48; i++)
		expandR[47 - i] = R[32 - E[i]];  //expandR[i] = R[E[i] - 1];
	 // XOR
	expandR = expandR ^ k;
	 // вместо этого S-поле
	bitset<32> output;
	int x = 0;
	for (int i = 0; i < 48; i = i + 6)
	{
		int row = expandR[i] * 2 + expandR[i + 5];
		int col = expandR[i + 1] * 8 + expandR[i + 2] * 4 + expandR[i + 3] * 2 + expandR[i + 4];
		int num = S_BOX[i / 6][row][col];
		bitset<4> temp(num);
		output[x + 3] = temp[0];
		output[x + 2] = temp[1];
		output[x + 1] = temp[2];
		output[x] = temp[3];
		x += 4;
	}
	 // Замена P-бокса
	bitset<32> tmp = output;
	for (int i = 0; i < 32; i++)
		output[i] = tmp[P[i] - 1];
 
	return output;
}
 // Функция сдвига влево
bitset<28> DES::leftshift(bitset<28> k, int shift) {
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
 
void DES::generateKeys() {
	bitset<56> real_key;
	bitset<28> left;
	bitset<28> right;
	bitset<48> compressKey;
 
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
 
 
 // Функция инструмента: преобразовать массив символов char в двоичный
bitset<64> DES::char_to_bit(const char s[8]) {
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
	/*for (int i = 0; i<8; ++i)
		for (int j = 0; j<8; ++j)
			bits[i * 8 + j] = ((s[i] >> j) & 1);
			*/
	return bits;
}
 // Функция инструмента: выполнить двоичное обратное преобразование
bitset<64> DES::change(bitset<64> temp) {
	bitset<64> bits;
	for (int i = 0; i < 64; i = i + 8)
	{
		for (int j = 0; j < 8; j++)
		{
			bits[i + j] = temp[i + 7 - j];
		}
	}
	return bits;
}
 
bitset<64> DES::DES_encryp(bitset<64> &plain) {
	bitset<64> cipher;
	bitset<64> currentBits;
	bitset<32> left;
	bitset<32> right;
	bitset<32> newLeft;
	 // Первоначальная замена IP
	for (int i = 0; i < 64; i++)
		currentBits[i] = plain[IP[i] - 1];//
 
	for (int i = 0; i < 32; i++)
		left[i] = currentBits[i];
	for (int i = 32; i < 64; i++)
		right[i - 32] = currentBits[i];
	 // Вводим 16 раундов изменения
	for (int round = 0; round < 16; round++)
	{
		newLeft = right;
		right = left ^ F(right, subkey[round]);
		left = newLeft;
	}
	 // Слияние
	for (int i = 0; i < 32; i++)
		cipher[i] = right[i];
	for (int i = 32; i < 64; i++)
		cipher[i] = left[i - 32];
	 // Обратная инициализация замены
	currentBits = cipher;
	for (int i = 0; i < 64; i++)
		cipher[i] = currentBits[IP_1[i] - 1];
 
	return cipher;
}
 
bitset<64> DES::DES_decrypt(bitset<64> & cipher) {
	bitset<64> plain;
	bitset<64> currentBits;
	bitset<32> left;
	bitset<32> right;
	bitset<32> newLeft;
	 // Заменить IP
	for (int i = 0; i < 64; i++)
		currentBits[i] = cipher[IP[i] - 1];
 
	for (int i = 0; i < 32; i++)
		left[i] = currentBits[i];
	for (int i = 32; i < 64; i++)
		right[i - 32] = currentBits[i];
	 // Вводим 16 итераций (подключи применяются в обратном порядке)
	for (int round = 0; round < 16; round++)
	{
		newLeft = right;
		right = left ^ F(right, subkey[15 - round]);
		left = newLeft;
	}
	 // Слияние
	for (int i = 0; i < 32; i++)
		plain[i] = right[i];
	for (int i = 32; i < 64; i++)
		plain[i] = left[i - 32];
	 // Обратная инициализация замены
	currentBits = plain;
	for (int i = 0; i < 64; i++)
		plain[i] = currentBits[IP_1[i] - 1];
 
	return plain;
}
 
 
void DES::show_encryp() {
	bitset<64> plain = char_to_bit(s.c_str());
	key = char_to_bit(k.c_str());
	 // Создание 16 подключей
	generateKeys();
	 // Записываем зашифрованный текст в a.txt
	bitset<64> cipher = DES_encryp(plain);
    cout << cipher << endl;
	fstream file1;
	file1.open("C://out.txt", ios::binary | ios::out);
	file1.write((char*)&cipher, sizeof(cipher));
	file1.close();
}
 
void DES::show_decrypt() {
    bitset<64> plain = char_to_bit(s.c_str());
    // bitset<64> plain;
    // for(int i = 0; i < 8; i++) {
    //     plain <<= 8;
    //     plain ^= s[i];
    // }

	key = char_to_bit(k.c_str());
    
    // for(int i = 0; i < 8; i++) {
    //     key <<= 8;
    //     key ^= k[i];
    // }
    cout << "Key: " << key << endl;
    //cout << "Plain: " << plain << endl;
	 // Создание 16 подключей
	generateKeys();
	 // Записываем зашифрованный текст в a.txt
	bitset<64> cipher = DES_encryp(plain);
    cout << cipher << endl;

	 // Расшифровываем и записываем в файл b.txt
	bitset<64> temp_plain = DES_decrypt(cipher);
	bitset<64> temp_1 = change(temp_plain);

    cout << temp_plain << endl;
    cout << temp_1 << endl;

    char out;
    string outStr = "";
    for (int i = 0; i < 8; i++) {
        out = (char)temp_1.to_ullong();
        temp_1 >>= 8;
        outStr = out + outStr;
        cout << out;
    }

    cout << outStr << endl;

    // for (int i = 0; i < 8; i++) {
    //     out = (char)temp_1.to_ullong();
    //     temp_plain >>= 8;
    //     outStr = out + outStr;
    // }
    // cout << outStr << endl;

}


int main() {
	DES C;
	string s = "computer";
	string k = "01234567";
	C.get_s(s);
	C.get_key(k);
	// C.show_encryp (); // Зашифровать, сгенерировать зашифрованный текст и записать его в a.txt
	// cout << "finish" << endl;
	// cout << "\n";
	cout << "start " << endl;
	C.show_decrypt (); // Считываем зашифрованный текст в a.txt, расшифровываем, генерируем открытый текст и записываем его в b.txt
	cout << "finish" << endl;
}