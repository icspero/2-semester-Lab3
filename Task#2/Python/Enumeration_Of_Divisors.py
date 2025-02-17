import math

# Функция перебора делителей
def dividers(num):
    k = 0
    if num == 1:
        print("Not prime, not composite")
        return 0
    for i in range(2, int(math.sqrt(num)) + 1):
        if num % i == 0:
            k += 1
    if k == 0:
        print("Is prime")
    else:
        print("Not prime")
    return 0

num = int(input("Enter the number: "))
dividers(num)

