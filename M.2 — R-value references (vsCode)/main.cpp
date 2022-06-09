#include <iostream>

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{};

public:
    Fraction(int num = 0, int den = 1 )
        : m_numerator{ num }, m_denominator{ den }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fr)
    {
        out << fr.m_numerator << '/' << fr.m_denominator << '\n';
        return out;
    }

};

void fun(const int &lref)// l-value arguments will select this function
{
    std::cout << "l-value reference to const\n";
}

void fun(int &&rref)// r-value arguments will select this function
{
    std::cout << "r-value reference\n"; 
}

int main()
{
    //L-values and r-values:

    //L-value references:

    //R-value references:
    int x{ 5 };
    int &lref_x{ x }; // l-value reference initialized with l-value x
    int &&rref_x{ 5 };// r-value reference initialized with r-value 5

    auto &&rref{ Fraction{ 3, 5 } }; // r-value reference to temporary Fraction

    // f1 of operator<< binds to the temporary, no copies are created.
    std::cout << rref;

    int &&rref_2{ 5 };// because we're initializing an r-value reference with a literal, a temporary with value 5 is created here
    rref_2 = 10;
    std::cout << rref_2 << '\n';

    //R-value references as function parameters:
    int y{ 5 };
    fun(y);//l-value argument calls l-value version of function
    fun(5);// r-value argument calls r-value version of function

    //One interesting note:
    int &&ref_z{ 5 };
    fun(ref_z);

    //Returning an r-value reference:

    //Quiz Time:
    /*
    State which of the following lettered statements will not compile:
    */

    int x_12{};

	// l-value references
	int &ref1{ x_12 }; // A
	//int &ref2{ 5 }; // B

	const int &ref3{ x_12 }; // C
	const int &ref4{ 5 }; // D

	// r-value references
	//int &&ref5{ x_12 }; // E
	int &&ref6{ 5 }; // F

	//const int &&ref7{ x_12 }; // G
	const int &&ref8{ 5 }; // H


    return 0;
}// rref (and the temporary Fraction) goes out of scope here