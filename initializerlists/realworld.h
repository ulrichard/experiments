#include <set>

enum FileClass
{
    eFileClass_Settings,
    eFileClass_Material,
    eFileClass_Support,
    eFileClass_Templates,
    eFileClass_Python
};

class Directories
{

private:
    static const std::set<FileClass> s_LangDepFileClasses;
};

