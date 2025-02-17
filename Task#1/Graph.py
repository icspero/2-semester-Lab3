import math

# Функция для вычисления значения функции
def function(x):
    if x == 0:
        return 0
    if x < 0:
        return -0.5 * x  # Линия слева
    if 0 < x < 2:
        return -math.sqrt(4 - x * x) + 2  # Нижняя часть полукруга
    if 2 <= x <= 4:
        return math.sqrt(4 - (x - 2) * (x - 2))  # Верхняя часть полукруга
    if x > 4:
        return -0.5 * x + 2  # Линия справа

# Функция округления до 0.001
def round_to_thousandth(value):
    return round(value, 3)

beg = float(input("Введите Xнач: "))
end = float(input("Введите Xкон: "))
dx = float(input("Введите шаг dx: "))

# Заголовок таблицы
print("Значения функции на заданном интервале:\n")
print(f"{'X':>6} | Y")
print("-------|-------")

x = beg
while x <= end:
    y = function(x)
    y = round_to_thousandth(y)
    print(f"{x:6.3f} | {y:.3f}")
    x += dx

