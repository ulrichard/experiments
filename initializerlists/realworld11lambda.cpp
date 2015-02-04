#include "realworld.h"

const std::set<FileClass> Directories::s_LangDepFileClasses = []()
        {
            std::set<FileClass> langDep;

            langDep.insert(eFileClass_Support);
            langDep.insert(eFileClass_Templates);

            return langDep;
        }();

int main()
{

    return 0;
}

