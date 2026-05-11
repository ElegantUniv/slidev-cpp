#include <iostream>
#include <numeric>    // std::gcd (C++17)
#include <stdexcept>

class Fraction {
public:
    Fraction(int numerator, int denominator) : num_(numerator), den_(denominator) {
        if (den_ == 0)
            throw std::invalid_argument("denominator cannot be zero");
        if (den_ < 0) {          // 분모는 항상 양수로 유지
            num_ = -num_;
            den_ = -den_;
        }
        reduce();
    }

    Fraction operator+(const Fraction& rhs) const {
        return Fraction(num_ * rhs.den_ + rhs.num_ * den_, den_ * rhs.den_);
    }
    Fraction operator-(const Fraction& rhs) const {
        return Fraction(num_ * rhs.den_ - rhs.num_ * den_, den_ * rhs.den_);
    }
    Fraction operator*(const Fraction& rhs) const {
        return Fraction(num_ * rhs.num_, den_ * rhs.den_);
    }
    Fraction operator/(const Fraction& rhs) const {
        return Fraction(num_ * rhs.den_, den_ * rhs.num_);
    }

    Fraction operator-() const {
        return Fraction(-num_, den_);
    }

    Fraction& operator+=(const Fraction& rhs) {
        *this = *this + rhs;   // operator+와 생성자의 정규화를 재사용
        return *this;
    }

    bool operator==(const Fraction& rhs) const {
        return num_ == rhs.num_ && den_ == rhs.den_;  // 항상 기약분수이므로 직접 비교 가능
    }
    bool operator!=(const Fraction& rhs) const { return !(*this == rhs); }
    bool operator<(const Fraction& rhs) const {
        return num_ * rhs.den_ < rhs.num_ * den_;
    }

    explicit operator bool() const { return num_ != 0; }

    int operator[](int index) const {
        if (index == 0) return num_;
        if (index == 1) return den_;
        throw std::out_of_range("index must be 0 or 1");
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        if (f.den_ == 1) os << f.num_;
        else             os << f.num_ << "/" << f.den_;
        return os;
    }

private:
    int num_;
    int den_;

    void reduce() {
        int g = std::gcd(std::abs(num_), den_);
        num_ /= g;
        den_ /= g;
    }
};

int main() {
    Fraction a(1, 2);
    Fraction b(1, 3);

    std::cout << a << " + " << b << " = " << (a + b) << std::endl;
    std::cout << a << " - " << b << " = " << (a - b) << std::endl;
    std::cout << a << " * " << b << " = " << (a * b) << std::endl;
    std::cout << a << " / " << b << " = " << (a / b) << std::endl;

    std::cout << "-" << a << " = " << (-a) << std::endl;

    std::cout << a << " == " << Fraction(2, 4) << " : "
              << std::boolalpha << (a == Fraction(2, 4)) << std::endl;
    std::cout << a << " <  " << b << " : "
              << std::boolalpha << (a < b) << std::endl;

    if (a) std::cout << a << " is nonzero" << std::endl;
    if (!Fraction(0, 1)) std::cout << "0 is zero" << std::endl;

    a += b;
    std::cout << "a += b : " << a << std::endl;

    std::cout << "분자: " << a[0] << ", 분모: " << a[1] << std::endl;

    std::cout << Fraction(1, -2) << std::endl;   // 분모 음수 정규화: -1/2
    std::cout << Fraction(6, 4)  << std::endl;   // 기약분수 약분: 3/2
    std::cout << Fraction(4, 2)  << std::endl;   // 정수 출력: 2
}
