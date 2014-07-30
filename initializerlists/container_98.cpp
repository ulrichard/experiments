#include <vector>
#include <map>
#include <string>

int main()
{
    const int ia[] = {1, 2, 3};

    std::vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);

    std::map<int, std::string> mis;
    mis[1] = "one";
    mis.insert(std::make_pair(2, "two"));

    return 0;
}

