#include <boost/range/concepts.hpp>
#include <type_traits>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>


template <typename T>
struct sfinae_true : std::true_type {};

struct is_iterator_tester {
    template <typename T>
    static sfinae_true<typename std::iterator_traits<T>::iterator_category> test(int);

    template <typename>
    static std::false_type test(...);
};

template <typename T>
struct is_iterator : decltype(is_iterator_tester::test<T>(0)) {};


template<class ContainerT, class StreamT,
        typename enabler = typename std::enable_if<is_iterator<decltype(std::begin(*static_cast<ContainerT*>(nullptr)))>::value, ContainerT>::type>
StreamT& operator<<(StreamT& strm, const ContainerT& cont)
{
	strm << '{';
	for(const auto& element : cont)
		strm << element << ' ';
	strm << '}';

	return strm;
}

struct Base
{
    virtual std::string Describe() const = 0;
};

std::ostream& operator<<(std::ostream& strm, const Base& base)
{
    strm << base.Describe() << " ";
}

struct SomeType : public Base
{
    SomeType(int p1, int p2) : one_(p1), another_(p2) { }

    virtual std::string Describe() const
    {
        std::stringstream sstr;
        sstr << '{' << one_ << ' ' << another_ << '}';
        return sstr.str();
    }

	int one_;
	int another_;
};

int main()
{
	std::vector<int> ints{8, 45, 87, 90, 99999};
	std::list<float> floats{3.14159, 2.71828, 0.57721, 1.618033};
	std::cout << ints << floats;

	SomeType some{456, 789};
	std::cout << some;

	return 0;
}

