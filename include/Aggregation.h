#pragma once
#include <algorithm>
#include <stdexcept>
using namespace std;

//this just returns the input parameter?
//what is the purpose of this? 
//Just so aggregate can take it as a function pointer instead of a variable?
template <class T>
T identity(T x) { return x; }


template <class S, class T>
//parameters:   S* a            array reference of type S
//              int size        size of array a
//              g(T x,T y)      returns x + y (by default)
//              f(S x)          returns x (by default)
//summary of function:
//if size > 0, set v to f(x) of first element of a
//then loop over remaining array, always getting f(a[i]) and operating it together with v
//in the default case, f just returns x, and g sums, therefore just summing the array
T aggregate(S* a, int size, T(*g)(T, T) = [](T x, T y) -> T { return x + y; }, T(*f)(S) = identity) {
    //if size parameter > 0
    if (size > 0) {
        //create a new variable v of type t
        //fill v with result of f(a[0])
        T v = f(a[0]);
        //iterate size-1 times
        for (int i = 1; i < size; i++) {
            //set v to g(v, f(a[i]))
            v = g(v, f(a[i]));
        }
        //return calculated v
        return v;
    } 
    //else can be left out here due to return in if
    //throw error if size is 0
    else throw logic_error(&"Received array of size " [size]);
}


template <class T>
T sum(T x, T y)
{
    return x + y;
}

template <class T>
T multiplication(T x, T y)
{
    return x * y;
}

template <class T>
T minumum(T x, T y)
{
    return min(x,y);
}

inline double divideBy10(int input)
{
    //this only leads to the correct result if the array size happens to be 10
    //in reality, this should be rewritten input/size, but since aggregate() is not allowed to be changed, i cannot supply the size as an additional function parameter
    //using lambdas, this is easily achievable, but im not sure how to accomplish this using the external function like this
    return double(input) / 10;
}

//works same as aggregate, but utilizes functors instead of function pointers
template<class S, class T, class gFunctor, class fFunctor>
T functorAggregate(S* a, int size, gFunctor g, fFunctor f)
{
    //if size parameter > 0
    if (size > 0) {
        //create a new variable v of type t
        //fill v with result of f(a[0])
        T v = f(a[0]);
        //iterate size-1 times
        for (int i = 1; i < size; i++) {
            //set v to g(v, f(a[i]))
            v = g(v, f(a[i]));
        }
        //return calculated v
        return v;
    } 
    //else can be left out here due to return in if
    //throw error if size is 0
    else throw logic_error(&"Received array of size " [size]);
}

template <class T>
class identityFunctor
{
public:
    T operator()(T x){ return x;}
};

template <class T>
class sumFunctor
{
public:
    T operator()(T x, T y){ return x + y;}
};

template <class T>
class multFunctor
{
public:
    T operator()(T x, T y){ return x * y;}
};

template <class T>
class minFunctor
{
public:
    T operator()(T x, T y){ return min(x, y);}
};

template <class T>
class divideByLengthFunctor
{
private:
    uint length;
public:
    divideByLengthFunctor(uint l){length = l;}
    T operator()(T x){ return T(x) / T(length);}
};