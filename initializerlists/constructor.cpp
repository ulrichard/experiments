#include <vector>
#include <map>
#include <string>

class my_path
{
public:
    my_path(std::initializer_list<std::string> dirs)
    {
        for(auto dir : dirs)
            m_Dir += "/" + dir;
    }
private:
    std::string m_Dir;
};

int main()
{
    const my_path dir{"home", "richi", "sourcecode", "pointline"};

    return 0;
}

