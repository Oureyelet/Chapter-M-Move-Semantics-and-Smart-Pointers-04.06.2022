#include <iostream>
#include <memory> // for std::unique_ptr // std::make_unique
#include <utility> // for std::move

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }

    friend std::ostream& operator<<(std::ostream& out, const Resource& res)
    {
        out << "I'm a resource";
        return out;
    }
};

template<typename T>
class Fraction
{
private:
    T m_numerator{ 0 };
    T m_denominator{ 1 };

public:
    Fraction(T numerator = 0, T denominator = 1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac)
    {
        out << frac.m_numerator << '/' << frac.m_denominator << '\n';
        return out;
    }


};

std::unique_ptr<Resource> createResource()
{
    return std::make_unique<Resource>();
}

void takeOwnership(std::unique_ptr<Resource> res)
{
    if(res)
        std::cout << *res << '\n';
}// the Resource is destroyed here


// The function only uses the resource, so we'll accept a pointer to the resource, 
//not a reference to the whole std::unique_ptr<Resource>
void useResource(Resource* res)
{
    if(res)
        std::cout << *res << '\n';
}

int main()
{
    /*
    Whole knowledge information coming from:
    https://www.learncpp.com/cpp-tutorial/stdunique_ptr/
    */

    //std::unique_ptr:

    std::unique_ptr<Resource> res1{ new Resource{} };// Resource created here and allocate a Resource object and have it owned by std::unique_ptr
    std::unique_ptr<Resource> res2{};// Start as nullptr

    std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
    std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");
 
    // res2 = res1; // Won't compile: copy assignment is disabled
    res2 = std::move(res1);// res2 assumes ownership, res1 is set to null

    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
    std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");

    //Accessing the managed object (and check if std::unique_ptr is managing):
    
    std::unique_ptr<Resource> res3{ new Resource{} };

    if(res3)// use implicit cast to bool to ensure res contains a Resource
        std::cout << *res3 << '\n';// print the Resource that res is owning

    //std::unique_ptr and arrays:

    //std::make_unique:

    auto f1{ std::make_unique<Fraction<int>>(3, 5) };// Create a single dynamically allocated Fraction with numerator 3 and denominator 5
	// We can also use automatic type deduction to good effect here
    std::cout << *f1 << '\n';


    auto f2{ std::make_unique<Fraction<int>[]>(4) };// Create a dynamically allocated array of Fractions of length 4
    std::cout << f2[0] << '\n';


    /*
    Best practice

    Use std::make_unique() instead of creating std::unique_ptr and using new yourself.
    */

    //The exception safety issue in more detail:

    //Returning std::unique_ptr from a function:

    auto ptr{ createResource() };
    ///...some coe...

    //Passing std::unique_ptr to a function:
    auto ptr2{ std::make_unique<Resource>() };

    //    takeOwnership(ptr); // This doesn't work, need to use move semantics
    takeOwnership(std::move(ptr2)); // ok: use move semantics

    std::cout << "Ending program" << '\n';

    //To get a raw resource pointer from a std::unique_ptr, you can use the get() member function:
    auto myPTR{ std::make_unique<Resource>() };

    useResource(myPTR.get());// note: get() used here to get a pointer to the Resource

    std::cout << "Ending program" << '\n';

    //std::unique_ptr and classes:

    //Misusing std::unique_ptr:
    



    return 0;
}// res goes out of scope here, and the allocated Resource is destroyed
// The Resource is destroyed here