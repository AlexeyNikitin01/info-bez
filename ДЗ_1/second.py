"""
КТО(подается 2 вектора: вектор значений, вектор модулей)
"""
from functools import reduce

from first import gcdex


def chinese_remainder(pairs):
    mod_list, remainder_list = [p[0] for p in pairs], [p[1] for p in pairs]
    mod_product = reduce(lambda x, y: x * y, mod_list)
    mi_list = [mod_product // x for x in mod_list]
    mi_inverse = [gcdex(mi_list[i], mod_list[i])[0] for i in range(len(mi_list))]
    x = 0
    for i in range(len(remainder_list)):
        x += mi_list[i] * mi_inverse[i] * remainder_list[i]
        x %= mod_product
    return x


if __name__ == '__main__':
    print(chinese_remainder([(3, 2), (5, 3), (7, 2)]))
