#include <iostream>
#include <memory> // for std::make_unique

class Resoure
{
public:
    Resoure() { std::cout << "Created\n"; }
    ~Resoure() { std::cout << "Deleted\n"; }
};
//  
int main()
{
    // allocate a Resource object and have it owned by std::shared_ptr
    auto ptr1{ std::make_shared<Resoure>() };
    {
        auto ptr2{ ptr1 }; // create ptr2 using copy of ptr1

        std::cout << "Killing one shared pointer\n";
    }// ptr2 goes out of scope here, but nothing happens

    std::cout << "Killing another shared pointer\n";

    return 0;
}// ptr1 goes out of scope here, and the allocated Resource is destroyed