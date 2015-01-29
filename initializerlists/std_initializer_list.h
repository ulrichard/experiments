#include <cstddef>

template<class _E>
class initializer_list
{
public:
    typedef _E 		value_type;
    typedef const _E& reference;
    typedef const _E& const_reference;
    typedef size_t 	size_type;
    typedef const _E* iterator;
    typedef const _E* const_iterator;
public:
    constexpr initializer_list() noexcept;
    constexpr size_type      size() const noexcept;
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator end() const noexcept;
private:
    // The compiler can call a private constructor. 
    constexpr initializer_list(const_iterator __a, size_type __l);
};

