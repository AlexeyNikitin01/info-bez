"""
функция нахождение обратного числа через расширенный алгоритм евклида
"""


def gcdex(a, b):
    if b == 0:
        return a, 1, 0
    else:
        d, x, y = gcdex(b, a % b)
        return d, y, x - y * (a // b)


if __name__ == "__main__":
    print(gcdex(10, 2))  # 2, 0, 1
