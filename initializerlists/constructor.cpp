#include <vector>
#include <map>
#include <string>
#include <iostream>

struct my_path
{
    my_path(std::initializer_list<std::string> dirs)
    {
        for(auto dir : dirs)
            m_Dir += "/" + dir;
    }

    std::string m_Dir;
};

int main()
{
    const my_path dir{"home", "richi", "sourcecode", "pointline"};
    std::cout << dir.m_Dir;
    return 0;
}

