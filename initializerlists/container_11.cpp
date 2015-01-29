#include <vector>
#include <map>
#include <string>

int main()
{
    // the containers can be const now
    const int ia[]{1, 2, 3};
    const std::vector<int> iv{1, 2, 3};
    const std::map<int, std::string> mis{{1, "one"}
                                       , {2, "two"}}; 
    return 0;
}

