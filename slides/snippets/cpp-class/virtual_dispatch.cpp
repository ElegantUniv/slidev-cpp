#include <cstdio>
#include <string>

class Animal {
public:
    std::string name;
    Animal(const std::string& n) : name(n) {}
    virtual void speak() const { printf("%s: ...\n", name.c_str()); }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    Dog(const std::string& n) : Animal(n) {}
    void speak() const override { printf("%s: 왈왈!\n", name.c_str()); }
};

class Cat : public Animal {
public:
    Cat(const std::string& n) : Animal(n) {}
    void speak() const override { printf("%s: 야옹!\n", name.c_str()); }
};

void greet(const Animal& a) {
    a.speak();  // 실제 타입에 따라 Dog 또는 Cat 버전 호출
}

int main() {
    Dog dog("멍멍이");
    Cat cat("냥냥이");
    Dog dog2("바둑이");

    Animal* zoo[] = { &dog, &cat, &dog2 };
    for (Animal* a : zoo) greet(*a);
    // 출력: 멍멍이: 왈왈!  냥냥이: 야옹!  바둑이: 왈왈!
}
