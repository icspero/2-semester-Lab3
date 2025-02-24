import random
import time

def powmod(a, x, mod):
    res = 1
    for _ in range(x):
        res = (res * a) % mod
    return res

def sieve_eratosthenes(n):
    is_prime = [True] * (n + 1)
    primes = []
    is_prime[0] = is_prime[1] = False
    
    for i in range(2, int(n**0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    
    for i in range(2, n + 1):
        if is_prime[i]:
            primes.append(i)
    
    return primes

def probability_test(num, k):
    if num in (2, 3):
        return True
    if num < 2 or num % 2 == 0:
        return False
    
    s, d = 0, num - 1
    while d % 2 == 0:
        d //= 2
        s += 1
    
    for _ in range(k):
        a = random.randint(2, num - 2)
        x = powmod(a, d, num)
        y = x
        
        for _ in range(s):
            y = powmod(x, 2, num)
            if y == 1 and x not in (1, num - 1):
                return False
            x = y
        
        if y != 1:
            return False
    
    return True

def canon(n, A):
    primes = sieve_eratosthenes(500)
    q = {}
    N = n - 1
    
    for p in primes:
        R, k = N, 0
        while R % p == 0:
            R //= p
            k += 1
        if k:
            q[p] = k
    
    check = []
    for p in q:
        for a in A:
            res = powmod(a, (n - 1) // p, n)
            check.append(res)
            if res != 1:
                return 1
    
    return 0 if all(c == 1 for c in check) else 1

def test_miller(n, t):
    A = [random.randint(2, n - 2) for _ in range(t)]
    
    if sum(powmod(a, n - 1, n) for a in A) != len(A):
        return False
    
    return canon(n, A) == 1

def print_table(prime_nums, prime_test_agree, prime_lost_count):
    col_width = 12
    n = len(prime_nums)
    
    def print_line():
        print("+" + ("-" * col_width + "+") * (n + 1))
    
    print_line()
    print("|" + f" {'№':<{col_width}}" + ''.join(f"| {i+1:<{col_width-1}}" for i in range(n)) + "|")
    print_line()
    print("|" + f" {'P':<{col_width}}" + ''.join(f"| {num:<{col_width-1}}" for num in prime_nums) + "|")
    print_line()
    print("|" + f" {'Тест':<{col_width}}" + ''.join(f"| {'+' if result else '-':<{col_width-1}}" for result in prime_test_agree) + "|")
    print_line()
    print("|" + f" {'K':<{col_width}}" + ''.join(f"| {k:<{col_width-1}}" for k in prime_lost_count) + "|")
    print_line()

def main():
    random.seed(time.time())
    sieve = sieve_eratosthenes(500)
    t, test_k = 5, 3
    
    prime_nums = []
    prime_lost_count = []
    prime_test_agree = []
    
    for _ in range(10):
        is_prime = False
        k = 0
        
        while not is_prime:
            m = 1
            for _ in range(2):
                m *= pow(sieve[random.randint(0, len(sieve) // 4)], random.randint(1, 2))
            
            n = 2 * m + 1
            
            if test_miller(n, t):
                prime_nums.append(n)
                is_prime = True
                prime_test_agree.append(probability_test(n, test_k))
            else:
                if probability_test(n, test_k):
                    k += 1
        
        prime_lost_count.append(k)
    
    print("".center(89, " "), "Тест Миллера")
    print_table(prime_nums, prime_test_agree, prime_lost_count)

if __name__ == "__main__":
    main()
