#include <algorithm>
#include <iostream>
#include "include/Aggregation.h"

int main()
{
    int myArray[20];
    std::cout << "myArray[" << sizeof(myArray)/sizeof(int) << "]={";
    for(int i = 0; i < sizeof(myArray)/sizeof(int); i++)
    {
        myArray[i] = i+1;
        std::cout << myArray[i] << ", ";
    }
    std::cout << "\b\b}\n\n";
    identityFunctor<int> identityF;

    //1
    //a) sum of myArray
    std::cout << "Calculating sum of array (expected 55 for a[10] | 210 for a[20])\n";
    //classic
    std::cout << "Classic: ";
    std::cout << aggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), sum, identity) << std::endl;
    //lambda
    std::cout << "Lambda:  ";
    std::cout << aggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), [](int x, int y) -> int { return x + y; }, [] (int x) -> int {return x;}) << std::endl;
    //2b) functor
    std::cout << "Functor: ";
    sumFunctor<int> sumF;
    std::cout << functorAggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), sumF, identityF) << std::endl;

    //b) product of myArray
    std::cout << "\nCalculating product of array (expected 3628800 for a[10] | 2432902008176640000 for a[20] (overflow))\n";
    //classic
    std::cout << "Classic: ";
    std::cout << aggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), multiplication, identity) << std::endl;
    //lambda
    std::cout << "Lambda:  ";
    std::cout << aggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), [](int x, int y) -> int { return x * y; }, [] (int x) -> int {return x;}) << std::endl;
    //2b) functor
    std::cout << "Functor: ";
    multFunctor<int> multF;
    std::cout << functorAggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), multF, identityF) << std::endl;

    //c) arithmetic mean of myArray
    std::cout << "\nCalculating arithmetic mean of array (expected 5.5 for a[10] | 10.5 for a[20])\n";
    //classic
    std::cout << "Classic: ";
    std::cout << aggregate<int, double>(myArray, sizeof(myArray)/sizeof(int), sum, divideBy10) << std::endl;
    //lambda
    std::cout << "Lambda:  ";
    std::cout << aggregate<int, double>(myArray, sizeof(myArray)/sizeof(int), [](double x, double y) -> double { return x + y; }, 
                                                                                      [](int x) -> double 
                                                                                      { return double(x) / (double(sizeof(myArray))/double(sizeof(int))); }) << std::endl;
    //2b) functor
    std::cout << "Functor: ";
    //redefine sumfunctor with T = double
    sumFunctor<double> sumF2;
    divideByLengthFunctor<double> divideF{sizeof(myArray)/sizeof(int)};
    std::cout << functorAggregate<int, double>(myArray, sizeof(myArray)/sizeof(int), sumF2, divideF) << std::endl;

    //c) minimum of myArray
    std::cout << "\nCalculating minimum of array (expected 1 for a[10] | 1 for a[20])\n";
    //classic
    std::cout << "Classic: ";
    std::cout << aggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), minumum, identity) << std::endl;
    //lambda
    std::cout << "Lambda:  ";
    std::cout << aggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), [](int x, int y) -> int {return min(x, y);}, [](int x) -> int {return x;}) << std::endl;
    //2b) functor
    std::cout << "Functor: ";
    minFunctor<int> minF;
    std::cout << functorAggregate<int, int>(myArray, sizeof(myArray)/sizeof(int), minF, identityF) << std::endl;

    return 0;
}