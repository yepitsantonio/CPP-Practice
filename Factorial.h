#ifndef __FACTORIAL_H
#define __FACTORIAL_H
class Factorial
{
public:
    Factorial(int n);
    void operator()();

private:
    int number;
    long long int result;
};
#endif