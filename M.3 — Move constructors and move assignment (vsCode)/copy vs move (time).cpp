#include <iostream>
#include <chrono> // for std::chrono functions

template<typename T>
class DynamicArray
{
private:
    T* m_array;
    int m_length;

public:
    DynamicArray(int length)
        : m_array{new T[length]}, m_length{length}
    {
    }

    ~DynamicArray()
    {
        delete[] m_array;
    }

/* We used this only for test now we can make sure the copy constructors not happen see below...

    // Copy constructor
    DynamicArray(const DynamicArray& arr)
        : m_length{ arr.m_length }
    {
        m_array = new T[m_length];
        for(int i{ 0 }; i < m_length; ++i)
            m_array[i] = arr.m_array[i];
    }

*/
    // Copy constructor - not happen never again...
    DynamicArray(const DynamicArray& arr) = delete;

    // Move constructor
    DynamicArray(DynamicArray&& arr) noexcept
        : m_array{ arr.m_array }, m_length{ arr.m_length }
    {
        arr.m_length = 0;
        arr.m_array = nullptr;
    }

    

/*We used this only for test now we can make sure the copy constructors not happen see below...
    // Copy assignment
    DynamicArray& operator=(const DynamicArray& arr)
    {
        if(&arr == this)
            return *this;

        delete[] m_array;

        m_length = arr.m_length;
        m_array = new T[m_length];

        for(int i{ 0 }; i < m_length; ++i)
            m_array[i] = arr.m_array[i];

        return *this;
    }
*/
    // Copy assignment  - not happen never again...
    DynamicArray& operator=(const DynamicArray* arr) = delete;

    // Move assignment
    DynamicArray& operator=(DynamicArray&& arr) noexcept
    {
        if(&arr == this)
            return *this;
        
        delete[] m_array;

        m_length = arr.m_length;
        m_array = arr.m_array;
        m_length = 0;
        m_array = nullptr;

        return *this;
    }


    int getLength() const { return m_length; }
    T& operator[](int length) { return m_array[length]; }
    const T& operator[](int length) const { return m_array[length]; }
};

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg { clock_t::now() };

public:
    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};

// Return a copy of arr with all of the values doubled
DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int>& arr)
{
    DynamicArray<int> dbl{ arr.getLength() };
    for(int i{ 0 }; i < arr.getLength(); ++i)
        dbl[i] = arr[i] * 2;

    return dbl;
}

int main()
{
    Timer t;

    DynamicArray<int> arr{1000000};

    for(int i{ 0 }; i < arr.getLength(); ++i)
        arr[i] = i;

    arr = cloneArrayAndDouble(arr);

    // std::cout << t.elapsed() << " seconds" << '\n'; // 0.0456261 seconds (with copy constructor and copy assignment)

    std::cout << t.elapsed() << " seconds" << '\n'; // 0.0353925 seconds
    
    double copy{ 0.0456261 };
    double move{ t.elapsed() };
    double proc{};
    proc = 100 - ((move*100) / copy);
    std::cout << "Move is "<< proc << "%" <<  " faster" << '\n'; 



    return  0;
}