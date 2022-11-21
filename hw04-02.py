import math


def mod7(x: int) -> int:
    rem = 0
    i = 0
    while rem != x:
        rem += (int(x/7**i) % 7) * 7**i
        i += 1
    return rem


print(mod7(10000))
