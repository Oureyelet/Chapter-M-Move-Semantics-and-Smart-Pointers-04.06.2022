#include <iostream>
#include <memory> // for std::make_shared // std::weak_ptr // std::shared_ptr
#include <string_view>

class Person
{
private:
    std::string m_name;
    //std::shared_ptr<Person> m_partner; // initially created empty
    std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

public:
    Person(std::string_view name)
        : m_name{ name }
    {
        std::cout << m_name << " created\n";
    }
    
    ~Person()
    {
        std::cout << " destroyed\n"; 
    }

    friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
    {
        if(!p1 || !p2)
            return false;

        p1->m_partner = p1;
        p2->m_partner = p2;
    
        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }
};

int main()
{
    std::cout << "Hello World" << '\n';

    auto lucy{ std::make_shared<Person>("Lucy") };// create a Person named "Lucy"
    auto ricky{ std::make_shared<Person>("Ricky") };// create a Person named "Ricky"

    partnerUp(lucy, ricky); // Make "Lucy" point to "Ricky" and vice-versa

    /*
    And that’s it. No deallocations took place. Uh. oh. What happened?
    After partnerUp() is called, there are two shared pointers pointing to “Ricky” (ricky, and Lucy’s m_partner) and two shared 
    pointers pointing to “Lucy” (lucy, and Ricky’s m_partner).
    At the end of main(), the ricky shared pointer goes out of scope first. When that happens, ricky checks if there are any other 
    shared pointers that co-own the Person “Ricky”. There are (Lucy’s m_partner). Because of this, it doesn’t deallocate “Ricky” 
    (if it did, then Lucy’s m_partner would end up as a dangling pointer). At this point, we now have one shared pointer to “Ricky” 
    (Lucy’s m_partner) and two shared pointers to “Lucy” (lucy, and Ricky’s m_partner).
    Next the lucy shared pointer goes out of scope, and the same thing happens. The shared pointer lucy checks if there are any 
    other shared pointers co-owning the Person “Lucy”. There are (Ricky’s m_partner), so “Lucy” isn’t deallocated. At this point, 
    there is one shared pointer to “Lucy” (Ricky’s m_partner) and one shared pointer to “Ricky” (Lucy’s m_partner).
    Then the program ends -- and neither Person “Lucy” or “Ricky” have been deallocated! Essentially, “Lucy” ends up keeping 
    “Ricky” from being destroyed, and “Ricky” ends up keeping “Lucy” from being destroyed.
    It turns out that this can happen any time shared pointers form a circular reference.
    */

    //Circular references:

    //A reductive case:

    //So what is std::weak_ptr for anyway?: std::weak_ptr was designed to solve the “cyclical ownership” problem described above. 

    //Using std::weak_ptr:

    

    return 0;
}