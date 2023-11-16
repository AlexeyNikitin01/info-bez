# import codecs
# import base64

# def rc4(key, plain, mode="code"):
#     if mode == "code":
#         plain = [ord(c) for c in plain]
#     key = [ord(c) for c in key]
#     s = sbox(key)
#     kstr = keystream(s)

#     res = []
#     for c in plain:
#         val = ("%02X" % (c ^ next(kstr)))  # XOR and taking hex
#         res.append(val)
#     return ''.join(res)

# def sbox(key):
#     s = [i for i in range(256)]
#     for i in range(256):
#         s[i] = i

#     j = 0
#     for i in range(256):
#         j = (j + s[i] + key[i % len(key)]) % 256
#         s[i], s[j] = s[j], s[i]
#     return s

# def keystream(s):
#     i = 0
#     j = 0
#     while True:
#         i = (i + 1) % 256
#         j = (j + s[i]) % 256
#         s[i], s[j] = s[j], s[i]
#         k = s[(s[i] + s[j]) % 256]
#         yield k

# if __name__ == "__main__":
#     key = "Key"
#     # plaintext = "Plaintext"
#     # chiper = rc4(key, plaintext)
#     # # print(type(chiper), chiper)

#     # new_chiper = codecs.decode('BBF316E8D940AF0AD3', 'hex_codec')
#     # text = rc4(key, new_chiper, "decode")
#     # # print(codecs.decode(text, 'hex_codec').decode('utf-8'))

#     with open("1111.jpg", "r") as f:
#         print("work")
#         p = f.read()
#         chiper = rc4(key, p.hex())
#         print(len(p))
#         print("Picture", type(p), "Chiper", type(chiper)) 
    
#     new_chiper = codecs.decode(chiper, 'hex_codec')
#     out = rc4(key, new_chiper, "decode")
#     print("OUT2", type(out), len(out), out[:10], out.encode()[:10])
    

import numpy as np
import cv2
MOD=256

#Key padding до 256 бит
def KSA(key):
    keylen = len(key)
    # create the array S
    S = list(range(MOD))
    i = 0
    j = 0
    for i in range(MOD):
        j = (j+S[i]+key[i % keylen]) % MOD
        S[i],S[j] = S[j],S[i]
    return S

class RC4:
    def __init__(self,_key =np.random.randint(0,255,(256))):      
        self.key = KSA(_key)

    # Используйте RC4_img для шифрования изображений
    def RC4_img(self,filepath):
        frame = cv2.imread(filepath)
        height = frame.shape[0]
        weight = frame.shape[1]
        channels = frame.shape[2]
        i = 0
        for row in range(height):            # Путешествие высоко
            for col in range(weight):         # Обход широкий
                for c in range(channels):     # Удобный канал
                    frame[row, col, c] =frame[row, col, c] ^ self.key[i%MOD]
                    i+=1
        return frame
      

    def RC4(self,data):
        new_data = []
        for i in range(data):
            _ = data[i]^self.key[i%MOD]
            new_data.append(_)
            return new_data
    # Записать текущий ключ
    def write_key(self,filepath="./keytxt.txt"):
        file = open(filepath,'w')
        for i in range(len(self.key)):
            file.write(str(self.key[i]))
            file.write('\n')
        file.close()
    # Читать ключ
    def read_key(self,filepath="./keytxt.txt"):
        file = open(filepath,'r')
        _key = []
        for line in file:
            _key.append(int(line))
        self.key = KSA(_key)
if __name__=="__main__":
    enimg = RC4()
    enimg.write_key()
    frame = enimg.RC4_img("./1111.bmp")
    cv2.imwrite("myRC4en.bmp",frame)
    frame = enimg.RC4_img("myRC4en.bmp")
    cv2.imwrite("myRC4de.bmp",frame)
