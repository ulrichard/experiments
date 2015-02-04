#include "realworld.h"

std::set<FileClass> FillLangDepFileClasses()
{
    std::set<FileClass> langDep;

    langDep.insert(eFileClass_Support);
    langDep.insert(eFileClass_Templates);

    return langDep;
}

const std::set<FileClass> Directories::s_LangDepFileClasses
                                 = FillLangDepFileClasses();

int main()
{

    return 0;
}

