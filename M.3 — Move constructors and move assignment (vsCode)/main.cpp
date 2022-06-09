#include <iostream>

template<class T>
class Auto_prt4
{
    T* m_ptr;
public:
    Auto_prt4(T* ptr = nullptr)
        : m_ptr{ ptr }
    {
    }

    ~Auto_prt4()
    {
        delete m_ptr;
    }

    // Copy constructor
	// Do deep copy of a.m_ptr to m_ptr
    Auto_prt4(const Auto_prt4& a)
    {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }

    // Move constructor
	// Transfer ownership of a.m_ptr to m_ptr
    Auto_prt4(Auto_prt4&& a) noexcept
        :m_ptr{ a.m_ptr }
    {
        a.m_ptr = nullptr;
    }

    // Copy assignment
	// Do deep copy of a.m_ptr to m_ptr
    Auto_prt4& operator=(const Auto_prt4& a)
    {
        if(&a == nullptr)
            return *this;
    
        // Release any resource we're holding
        delete m_ptr;

        // Copy the resource
        m_ptr = new T;
        *m_ptr = *a.m_ptr;

        return *this;
    }

    // Move assignment
	// Transfer ownership of a.m_ptr to m_ptr
    Auto_prt4& operator=(Auto_prt4&& a) noexcept
    {
        // Self-assignment detection
        if(&a == this)
            return *this;
        
        // Release any resource we're holding
        delete m_ptr;

        // Transfer ownership of a.m_ptr to m_ptr
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T& operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_prt4<Resource> generateResource()
{
    Auto_prt4<Resource> res{ new Resource() };

    return res;// this return value will invoke the move constructor
}

int main()
{
    //Copy constructors and copy assignment:
    
    //Move constructors and move assignment:

    Auto_prt4<Resource> mainres;

    mainres = generateResource();// this assignment will invoke the move assignment


    //read again from "d move assignment operator are simple. Instead of deep cop"

    return 0;
}