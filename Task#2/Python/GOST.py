import random
import math
from typing import List

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

def GOST_341094(t: int, q: int) -> int:
    n = 0
    u = 0
    p = 0
    isPrime = False
    e = 0.0
    while True:
        e = random.random()
        while e > 1:
            e /= 10
        n = int(round(pow(2, t - 1) / q + round((pow(2, t - 1) * e) / q)))
        if n % 2 == 1:
            n += 1
        u = 0
        while not isPrime:
            p = (n + u) * q + 1
            if p > pow(2, t):
                break
            if powmod(2, p - 1, p) == 1 and powmod(2, n + u, p) != 1:
                isPrime = True
            else:
                u += 2
        if isPrime:
            break
    return p

def printTable(primeNums: List[int], primeTestAgree: List[bool]):
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

def main():
    random.seed()
    sieve = []
    primeNums = []
    primeTestAgree = []
    t = 15
    test_k = 3
    for _ in range(10):
        sieve = sieveEratosthenes(pow(2, t // 2))
        q = sieve[random.randint(0, len(sieve) - 1)]
        q = GOST_341094(t, q)
        primeNums.append(q)
        primeTestAgree.append(probability_Test(q, test_k))
    print("{:^85}".format("ГОСТ Р 34.10-94"))
    printTable(primeNums, primeTestAgree)

if __name__ == "__main__":
    main()