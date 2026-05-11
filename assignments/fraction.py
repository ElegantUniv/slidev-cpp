from math import gcd


class Fraction:
    def __init__(self, numerator: int, denominator: int):
        if denominator == 0:
            raise ValueError("denominator cannot be zero")
        if denominator < 0:          # 분모는 항상 양수로 유지
            numerator, denominator = -numerator, -denominator
        g = gcd(abs(numerator), denominator)
        self.num = numerator // g
        self.den = denominator // g

    def __add__(self, other):
        return Fraction(self.num * other.den + other.num * self.den,
                        self.den * other.den)

    def __sub__(self, other):
        return Fraction(self.num * other.den - other.num * self.den,
                        self.den * other.den)

    def __mul__(self, other):
        return Fraction(self.num * other.num, self.den * other.den)

    def __truediv__(self, other):
        return Fraction(self.num * other.den, self.den * other.num)

    def __neg__(self):
        return Fraction(-self.num, self.den)

    def __iadd__(self, other):
        result = self + other        # __add__와 __init__의 정규화를 재사용
        self.num = result.num
        self.den = result.den
        return self

    def __eq__(self, other):
        return self.num == other.num and self.den == other.den  # 항상 기약분수이므로 직접 비교 가능

    def __lt__(self, other):
        return self.num * other.den < other.num * self.den

    def __bool__(self):
        return self.num != 0

    def __getitem__(self, index):
        if index == 0: return self.num
        if index == 1: return self.den
        raise IndexError("index must be 0 or 1")

    def __str__(self):
        if self.den == 1:
            return str(self.num)
        return f"{self.num}/{self.den}"

    def __repr__(self):
        return f"Fraction({self.num}, {self.den})"


if __name__ == "__main__":
    a = Fraction(1, 2)
    b = Fraction(1, 3)

    print(f"{a} + {b} = {a + b}")
    print(f"{a} - {b} = {a - b}")
    print(f"{a} * {b} = {a * b}")
    print(f"{a} / {b} = {a / b}")

    print(f"-{a} = {-a}")

    print(f"{a} == {Fraction(2, 4)} : {a == Fraction(2, 4)}")
    print(f"{a} <  {b} : {a < b}")

    if a:
        print(f"{a} is nonzero")
    if not Fraction(0, 1):
        print("0 is zero")

    a += b
    print(f"a += b : {a}")

    print(f"분자: {a[0]}, 분모: {a[1]}")

    print(Fraction(1, -2))   # 분모 음수 정규화: -1/2
    print(Fraction(6, 4))    # 기약분수 약분: 3/2
    print(Fraction(4, 2))    # 정수 출력: 2

    print(repr(a))           # __repr__ 확인
