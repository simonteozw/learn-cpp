#include<stdio.h>

enum Operation { Add, Subtract, Multiply, Divide };

struct Calculator {
    Calculator(Operation x) {
        op = x;
    }

    ~Calculator() {
        printf("Destruction occurring now\n");
    }

    int calculate(int a, int b) {
        switch (op){
            case Add:
                return a + b;
            case Subtract:
                return a - b;
            case Multiply:
                return a * b;
            default:
                return a / b;
        }
    }

    private:
        Operation op;
};

int main() {
    Calculator c1 = Calculator(Add), c2 = Calculator(Subtract), c3 = Calculator(Multiply), c4 = Calculator(Divide);
    int a = 4, b = 2;
    printf("%d, %d, %d, %d\n", c1.calculate(a, b), c2.calculate(a, b), c3.calculate(a, b), c4.calculate(a, b));
    return 0;
}