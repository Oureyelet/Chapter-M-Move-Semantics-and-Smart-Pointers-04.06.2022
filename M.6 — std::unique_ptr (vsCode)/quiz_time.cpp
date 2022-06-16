#include <iostream>
#include <memory> // for std::unique_ptr

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction(int num = 0, int den = 1)
        : m_numerator{ num }, m_denominator{ den }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fr)
    {
        out << fr.m_numerator << '/' << fr.m_denominator << '\n';
        return out;
    }
};

void printFraction(const Fraction* ptr)
{
    if(ptr)
    {
        std::cout << *ptr;
    }
}

int main()
{
    /*
    Quiz time

    Question #1

    Convert the following program from using a normal pointer to using std::unique_ptr where appropriate:

    #include <iostream>

    class Fraction
    {
    private:
        int m_numerator{ 0 };
        int m_denominator{ 1 };

    public:
        Fraction(int numerator = 0, int denominator = 1) :
            m_numerator{ numerator }, m_denominator{ denominator }
        {
        }

        friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
        {
            out << f1.m_numerator << '/' << f1.m_denominator;
            return out;
        }
    };

    void printFraction(const Fraction* ptr)
    {
        if (ptr)
            std::cout << *ptr << '\n';
    }

    int main()
    {
        auto* ptr{ new Fraction{ 3, 5 } };

        printFraction(ptr);

        delete ptr;

        return 0;
    }
    */

    auto ptr{ std::make_unique<Fraction>(2, 5) };
    printFraction(ptr.get());

    return 0;
}