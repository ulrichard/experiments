#include "std_initializer_list.h"

template<class T>
constexpr initializer_list<T>::initializer_list() noexcept {}

template<class T>
constexpr size_t initializer_list<T>::size() const noexcept { return 0; }

template<class T>
constexpr const T* initializer_list<T>::begin() const noexcept { return nullptr; }

template<class T>
constexpr const T* initializer_list<T>::end() const noexcept { return nullptr; }

int main()
{
    initializer_list<int> il;

    return il.size();
}
