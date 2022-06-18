#include <iostream>
#include <memory> // for std::weak_ptr, std::shared_ptr
#include <string_view>

class Person
{
private:
    std::string m_name{};
    std::weak_ptr<Person> m_partner{}; // note: This is now a std::weak_ptr instead of std::shared_ptr

public:
    Person(std::string_view name)
        : m_name{ name }
    {
        std::cout << "Created\n";
    }

    ~Person()
    {
        std::cout << "Destroyed\n";
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

    // use lock() to convert weak_ptr to shared_ptr
    const std::shared_ptr<Person> getPartner() const { return m_partner.lock(); }
    std::string_view getName() const { return m_name; } 
};

int main()
{
    auto lucy{ std::make_shared<Person>("Lucy") };
    auto ricky{ std::make_shared<Person>("Ricky") };

    partnerUp(lucy, ricky);

    auto partner = ricky -> getPartner(); // get shared_ptr to Ricky's partner
    std::cout << ricky -> getName() << '\n';

    return 0;
}