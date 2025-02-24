import random
import math
from typing import List, Tuple

def powmod(a: int, x: int, mod: int) -> int:
    res = 1
    for _ in range(x):
        res = res * a
        res = res % mod
    return res

def sieveEratosthenes(n: int) -> List[int]:
    is_prime = [True] * (n + 1)
    primes = []
    
    is_prime[0] = is_prime[1] = False  # 0 и 1 не являются простыми
    
    for i in range(2, int(math.sqrt(n)) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False  # отмечаем все кратные i как составные
    
    for i in range(2, n + 1):
        if is_prime[i]:
            primes.append(i)
    
    return primes

def probability_Test(num: int, k: int) -> bool:  # Миллер-Рабин
    if num == 2 or num == 3:
        return True
    if num < 2 or num % 2 == 0:
        return False
    s = 0
    d = num - 1
    while d % 2 == 0:
        d //= 2
        s += 1
    for _ in range(k):
        a = random.randint(2, num - 2)  # от 2 до num - 2
        x = powmod(a, d, num)
        y = 0
        for _ in range(s):
            y = powmod(x, 2, num)
            if y == 1 and x != 1 and x != (num - 1):
                return False
            x = y
        if y != 1:
            return False
    return True

def NOD(a: int, p: int) -> int:  # проверка на взаимно простые числа
    while p != 0:  # поиск НОД (обобщенный алгоритм Евклида)
        r = p  # a и r переносят числа
        p = a % p  # каждую итерацию после первой берем остаток от пред. делителя и остатка
        a = r  # a%b = c >> b%c = g >> c%g = d
    return a

def canon(n: int) -> List[int]:
    prime = sieveEratosthenes(2000)
    q = []
    N = n - 1

    for p in prime:
        R = N
        k = 0
        if R % p == 0:
            while R % p == 0:
                R //= p
                k += 1
            for _ in range(k):
                q.append(p)
        else:
            continue

    F = []

    while True:
        r = 1
        f = 1
        
        F.append(q[-1])
        q.pop()

        for factor in F:
            f *= factor

        for factor in q:
            r *= factor

        if f > r and r % 2 == 0:
            return F
        else:
            continue

def test_Poclington(n: int, t: int) -> bool:
    A = []
    check = []

    if n == 1 or n == 0:
        return False

    prime = sieveEratosthenes(8)
    if n in prime:
        return True

    for _ in range(t):
        A.append(random.randint(2, n - 2))

    for a in A:
        res = powmod(a, n - 1, n)
        if res != 1:
            return False

    F = canon(n)

    for a in A:
        temp_a = a
        for f in F:
            res = powmod(temp_a, (n - 1) // f, n)
            if res == 1:
                break
            else:
                check.append(res)

    for c in check:
        if c == 1:
            return False
        else:
            return True

    return False

def bitLen(number: int) -> int:
    bitCount = 0
    while number != 0:
        bitCount += 1
        number //= 2
    return bitCount

def printTable(primeNums: List[int], primeTestAgree: List[bool], primeLostCount: List[int]):
    n = len(primeNums)
    colWidth = 12

    def printLine(count: int):
        print("+", end="")
        for _ in range(count + 1):
            print("-" * colWidth + "+", end="")
        print()

    printLine(n)
    print("| {:<{}}".format("№", colWidth + 1), end="")
    for i in range(n):
        print("| {:<{}}".format(i + 1, colWidth - 1), end="")
    print("|")

    printLine(n)

    print("| {:<{}}".format("P", colWidth - 1), end="")
    for num in primeNums:
        print("| {:<{}}".format(num, colWidth - 1), end="")
    print("|")
    printLine(n)

    print("| {:<{}}".format("Тест", colWidth + 3), end="")
    for result in primeTestAgree:
        print("| {:<{}}".format("+" if result else "-", colWidth - 1), end="")
    print("|")
    printLine(n)

    print("| {:<{}}".format("K", colWidth - 1), end="")
    for k in primeLostCount:
        print("| {:<{}}".format(k, colWidth - 1), end="")
    print("|")
    printLine(n)

def main():
    t = 5
    test_k = 3
    primeNums = []
    primeLostCount = []
    primeTestAgree = []

    for _ in range(10):
        isPrime = False
        k = 0
        while not isPrime:
            bit = random.randint(6, 16)

            F = 1
            sieve = sieveEratosthenes(500)

            while F < 2 ** (bit // 2) or F > 2 ** (bit // 2 + 1):
                temp = random.choice(sieve)
                F *= temp

                if F > 2 ** (bit // 2 + 1):
                    F = 1

            n = 0
            r = random.randint(2 ** (bit // 2 - 1), 2 ** (bit // 2) - 1)
            if r % 2 == 0:
                n = r * F
                if bitLen(n) == bit:
                    n += 1

            if n in primeNums:
                continue

            if n != 1 and test_Poclington(n, t):
                primeNums.append(n)
                isPrime = True
                if probability_Test(n, test_k):
                    primeTestAgree.append(True)
                else:
                    primeTestAgree.append(False)
            else:
                if probability_Test(n, test_k):
                    k += 1

        primeLostCount.append(k)

    print("{:^95}".format("Тест Поклингтона"))
    printTable(primeNums, primeTestAgree, primeLostCount)

if __name__ == "__main__":
    main()