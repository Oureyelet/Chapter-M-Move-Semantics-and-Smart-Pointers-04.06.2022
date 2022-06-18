#include <iostream>
#include <memory>

class Resource
{
public:
    std::weak_ptr<Resource> m_ptr{};

    Resource() { std::cout << "Created\n"; }
    ~Resource() { std::cout << "Destroyed\n"; }

    const std::shared_ptr<Resource> get_ptr() const { return m_ptr.lock(); }
};

int main()
{
    /*
    Quiz time:

    Fix the “reductive case” from:
    https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/
    program so that the Resource is properly deallocated
    */

    auto ptr1{ std::make_shared<Resource>() };

    auto ptr2 = ptr1 -> get_ptr();

    ptr1 = ptr2;



    return 0;
}