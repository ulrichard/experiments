// standard library
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <set>
#include <algorithm>

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8/////////9/////////A
class SubstChar
{
public:
	SubstChar(int rot) : rot_(rot) { }
	char operator()(char cc)
	{
		if(cc >= 'a' && cc <= 'z')
			return (cc - 'a' + rot_) % 26 + 'a';
		if(cc >= 'A' && cc <= 'Z')
			return (cc - 'A' + rot_) % 26 + 'A';
		return cc;
	}
private:
	const int rot_;
};
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8/////////9/////////A
int main(int argc, char* argv[])
{
    const std::string inpStr("Esp qtcde nzyqpcpynp zy esp ezatn zq Lcetqtntlw Tyepwwtrpynp hld spwo le Olcexzfes Nzwwprp ty estd jplc.");

    // read the dictionary
	std::ifstream ifs("/usr/share/dict/american-english");
	std::set<std::string> englishWords;
	char buf[128];
	while(!ifs.eof())
		if(ifs.getline(buf, sizeof(buf)))
			englishWords.insert(buf);

	std::string bestSentence;
	size_t      bestScore = 0;
	for(size_t i=0; i<26; ++i)
	{
	    // move the characters
		std::stringstream sstr;
		std::transform(inpStr.begin(), inpStr.end(), std::ostream_iterator<char>(sstr, ""), SubstChar(i));

        // separate the words
		std::set<std::string> queryWords;
		std::copy(std::istream_iterator<std::string>(sstr), std::istream_iterator<std::string>(),
				  std::inserter(queryWords, queryWords.end()));

        // find the words in the dictionary
		std::vector<std::string> matches;
		std::set_intersection(englishWords.begin(), englishWords.end(),
							  queryWords.begin(),   queryWords.end(),
							  std::back_inserter(matches));

		if(matches.size() > bestScore)
		{
			bestScore = matches.size();
			sstr.seekg(0);
			bestSentence = sstr.str();
		}
	}

	std::cout << bestSentence << std::endl;

    return 0;
}
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8/////////9/////////A
// Answer: the conference was in 1956



