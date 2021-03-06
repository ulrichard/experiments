#include <vector>
#include <map>
#include <string>

int main()
{
    auto iil = {1, 2, 3};
    const std::vector<int> iv2 = iil;


    auto il1 = {std::pair<const int, std::string>(1, "one"), 
                std::pair<const int, std::string>(2, "two")};
    const std::map<int, std::string> mis1(il1);

    typedef std::initializer_list<std::pair<const int, std::string>> InitListMap;
    InitListMap il2 = {{1, "one"}, {2, "two"}};
    const std::map<int, std::string> mis2{il2};

    return 0;
}

