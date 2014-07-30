#include <vector>
#include <map>
#include <string>

int main()
{
    const int ia[] = {1, 2, 3};
    const std::vector<int> iv = {1, 2, 3};
    const std::map<int, std::string> mis = {{1, "one"}
                                          , {2, "two"}}; 

    auto iil = {1, 2, 3};
    const std::vector<int> iv2 = iil;
    std::initializer_list<std::pair<int, std::string>> il 
                = {{1, "one"}, {2, "two"}}; 
//    const std::map<int, std::string> mis2 = il;

    return 0;
}

