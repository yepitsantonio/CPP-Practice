#ifndef __FACTORIAL_H
#define __FACTORIAL_H
class Factorial
{
public:
    Factorial(int n);
    const int getResult();
    void operator()();

private:
    int number;
    int result;
};
#endif