#include <iostream>
#include <memory> // for std::unique_ptr

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
    /*
    Whole knowledge information coming from:
    https://www.learncpp.com/cpp-tutorial/stdunique_ptr/
    */

    //std::unique_ptr:

    std::unique_ptr<Resource> res{ new Resource() };// allocate a Resource object and have it owned by std::unique_ptr


    return 0;
}// res goes out of scope here, and the allocated Resource is destroyed