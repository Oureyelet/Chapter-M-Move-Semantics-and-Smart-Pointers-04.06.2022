#include <iostream>
#include <string>
#include <utility> // for std::move

template<typename T>
void myswap(T& a, T& b)
{
    T tmp{ a }; // invokes copy constructor
    a = b; // invokes copy assignment
    b = tmp; // invokes copy assignment
}

template<typename T>
void myswap_with_std_move(T& a, T& b)
{
    T tmp{ std::move(a) }; // invokes move constructor
    a = std::move(b); // invokes move assignment
    b = std::move(tmp); // invokes move assignment
}

int main()
{
    std::string x{ "abc" };
    std::string y{ "de" };

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';

    myswap(x, y);

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';

    //std::move:

    std::string x_001{ "abc" };
    std::string y_001{ "de" };

    std::cout << "x: " << x_001 << '\n';
    std::cout << "y: " << y_001 << '\n';

    myswap_with_std_move(x_001, y_001);

    std::cout << "x: " << x_001 << '\n';
    std::cout << "y: " << y_001 << '\n';
    
    //Another example: see our 'another_example.cpp'

    //Move functions should always leave your objects in a well-defined state:

    //Where else is std::move useful?:
    
    

    return 0;
}