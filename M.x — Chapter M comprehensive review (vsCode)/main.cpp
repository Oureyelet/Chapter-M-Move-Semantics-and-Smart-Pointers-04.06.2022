#include <iostream>
#include <memory> // for std::shared_ptr

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
    //Quiz time:

    auto res{ std::make_shared<Resource>() };
    auto ptr1{ res };


    return 0;
}