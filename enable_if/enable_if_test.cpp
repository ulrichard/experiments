#include <boost/range/concepts.hpp>
#include <type_traits>
#include <iostream>
#include <vector>

template<class ContainerT, class StreamT/*, std::enable_if<boost::ForwardRangeConcept<ContainerT>*/>
StreamT& operator<<(StreamT& strm, const ContainerT& cont)
{
	strm << '{';
	for(const auto& element : cont)
		strm << element;
	strm << '}';
}

struct SomeType
{
	int one;
	int another;
};

int main()
{
	std::vector<int> numbers{8, 45, 87, 90, 99999};
	std::cout << numbers;

	SomeType some{456, 789};
	std::cout << some;
	
	return 0;
}

