#include <iostream>

struct Resource_u
{

};


void someFunction()
{
    Resource_u* ptr = new Resource_u();// Resource is a struct or class

    // do stuff with ptr here

    delete ptr;
}

void someFunction2()
{
    Resource_u* ptr = new Resource_u(); 

    int x{};
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if(x == 0)
        return;// the function returns early, and ptr won’t be deleted!
        //or throw 0;

    // do stuff with ptr here
    
    delete ptr;
}

template<typename T>
class Auto_ptr1
{
private:
    T* m_ptr{};

public:
    // Pass in a pointer to "own" via the constructor
    Auto_ptr1(T* ptr = nullptr)
        : m_ptr{ ptr }
    {
    }

    // The destructor will make sure it gets deallocated
    ~Auto_ptr1()
    {
        delete m_ptr;
    }

    // A copy constructor that implements move semantics
    Auto_ptr1(Auto_ptr1& a)// note: not const
    {
        m_ptr = a.m_ptr;// transfer our dumb pointer from the source to our local object

        a.m_ptr = nullptr;// make sure the source no longer owns the pointer
    }

    // An assignment operator that implements move semantics
    Auto_ptr1 operator=(Auto_ptr1& a)// note: not const
    {
        if(&a == this)
            return *this;

        delete m_ptr;// make sure we deallocate any pointer the destination is already holding first

        m_ptr = a.m_ptr;// then transfer our dumb pointer from the source to the local object

        a.m_ptr = nullptr;// make sure the source no longer owns the pointer
        return *this;
    }

    // Overload dereference and operator-> so we can use Auto_ptr1 like m_ptr.
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

// A sample class to prove the above works
class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }
};

void soneFunction_with_smart_pointer()
{
    Auto_ptr1<Resource> ptr{ new Resource() };// ptr now owns the Resource

    int x{};
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if(x == 0)
        return;// the function returns early

    // do stuff with ptr here
    ptr->sayHi();
}

int main()
{
    std::cout << "Hello World\n";

    //Smart pointer classes to the rescue?:
    //Auto_ptr1<Resource> res{ new Resource() };// Note the allocation of memory here

     // ... but no explicit delete needed

    // Also note that the Resource in angled braces doesn't need a * symbol, since that's supplied by the template

    // Such a class is called a smart pointer.

    //soneFunction_with_smart_pointer();

    //A critical flaw:

    //Auto_ptr1<Resource> ptr_11{ new Resource() }; CRASH !
    //Auto_ptr1<Resource> ptr_12{ ptr_11 }; CRASH !

    //Move semantics:
    Auto_ptr1<Resource> res1{ new Resource() };
    Auto_ptr1<Resource> res2;// Start as nullptr

    std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n"); 

    res2 = res1; // res2 assumes ownership, res1 is set to null

    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n"); 


    return 0;
}// res goes out of scope here, and destroys the allocated Resource for us