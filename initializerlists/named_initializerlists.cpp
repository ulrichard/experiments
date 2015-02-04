#include <vector>
#include <map>
#include <string>

int main()
{
    auto iil = {1, 2, 3};
    const std::vector<int> iv2 = iil;

    // unable to deduce initializer_list<_Tp> from ...
//  auto il0 = {{1, "one"}, {2, "two"}}; 

    auto il1 = {std::make_pair(1, "one"), std::make_pair(2, "two")};
    //  no known conversion for argument 1 from ... to ...
//  const std::map<int, std::string> mis1(il1);

    return 0;
}

