// boost
//#include <boost/range/algorithm.hpp>
#include <boost/tokenizer.hpp>
#include <boost/multi_array.hpp>
#include <boost/foreach.hpp>
#include <boost/array.hpp>
#include <boost/cstdint.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/algorithm/string.hpp>
// standard library
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

namespace bll = boost::lambda;
using namespace boost::lambda;
using boost::algorithm::to_lower_copy;

static const size_t numColumn = 19;
static const size_t numRow    = 8;
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8/////////9/////////A
class ScrambledText
{
public:
    static const ScrambledText& getInst()
    {
        if(NULL == pInst_)
            pInst_ = new ScrambledText();
        return *pInst_;
    }

    const boost::multi_array<std::string, 2>& words() const { return wordMatrix_; }

private:
    ScrambledText() : wordMatrix_(boost::extents[numRow][numColumn])
    {
        // prepare the input text
        static const std::string inpStr =   "|de| | f|Cl|nf|ed|au| i|ti| |ma|ha|or|nn|ou| S|on|nd|on|\n"
                                            "|ry| |is|th|is| b|eo|as| | |f |wh| o|ic| t|, | |he|h |\n"
                                            "|ab| |la|pr|od|ge|ob| m|an| |s |is|el|ti|ng|il|d |ua|c |\n"
                                            "|he| |ea|of|ho| m| t|et|ha| | t|od|ds|e |ki| c|t |ng|br|\n"
                                            "|wo|m,|to|yo|hi|ve|u | t|ob| |pr|d |s |us| s|ul|le|ol|e |\n"
                                            "| t|ca| t|wi| M|d |th|\"A|ma|l |he| p|at|ap|it|he|ti|le|er|\n"
                                            "|ry|d |un|Th|\" |io|eo|n,|is| |bl|f |pu|Co|ic| o|he|at|mm|\n"
                                            "|hi| | |in| | | t| | | | |ye| |ar| |s | | |. |";

        std::vector<std::string> lines;
        boost::tokenizer<boost::char_separator<char> > tokens(inpStr, boost::char_separator<char>("\n"));

        size_t lineNr = 0;
        BOOST_FOREACH(const std::string& line, tokens)
        {
            if(line.empty() || lineNr >= numRow)
                break;
            boost::tokenizer<boost::char_separator<char> > tokens2(line, boost::char_separator<char>("|"));
            size_t columnNr = 0;
            BOOST_FOREACH(const std::string& val, tokens2)
                if(columnNr < numColumn)
                    wordMatrix_[lineNr][columnNr++] = to_lower_copy(val);
            ++lineNr;
        }
    }

    static ScrambledText*              pInst_;
    boost::multi_array<std::string, 2> wordMatrix_;
};
ScrambledText* ScrambledText::pInst_ = 0;
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8/////////9/////////A
class Dictionary
{
public:
    static const Dictionary& getInst()
    {
        if(NULL == pInst_)
            pInst_ = new Dictionary();
        return *pInst_;
    }

    const std::set<std::string>&         words()    const { return words_; }
    const std::set<std::string>&         trigrams() const { return trigrams_; }
    const std::map<std::string, size_t>& trigramCounts() const { return trigramCounts_; }
    const std::set<std::string>&         bonusWords() const { return bonusWords_; }

private:
    Dictionary()
    {
        // read the dictionary
        std::ifstream ifs("/usr/share/dict/american-english");
//        std::ifstream ifs("/usr/share/dict/swiss");

        char buf[128];
        while(!ifs.eof())
            if(ifs.getline(buf, sizeof(buf)))
            {
                const std::string word(to_lower_copy(std::string(buf)));
                words_.insert(word);

                // extract trigrams
                for(size_t i=0; i + 3 < word.length(); ++i)
                {
                    const std::string trigram(word.substr(i, i + 3));
                    trigrams_.insert(trigram);
                    ++trigramCounts_[trigram];
                }
            }

        bonusWords_.insert("artificial");
        bonusWords_.insert("intelligence");
        bonusWords_.insert("stanford");
        bonusWords_.insert("stanley");
        bonusWords_.insert("darpa");
        bonusWords_.insert("challenge");
        bonusWords_.insert("markov");
        bonusWords_.insert("bayes");
        bonusWords_.insert("assumption");
        bonusWords_.insert("statistic");
        bonusWords_.insert("statistical");
        bonusWords_.insert("search");
        bonusWords_.insert("beam");
        bonusWords_.insert("particla");
        bonusWords_.insert("conference");
        bonusWords_.insert("value");
        bonusWords_.insert("greedy");
        bonusWords_.insert("graph");
        bonusWords_.insert("robot");
        bonusWords_.insert("agent");
        bonusWords_.insert("filter");
        bonusWords_.insert("weight");
        bonusWords_.insert("importance");
        bonusWords_.insert("important");
        bonusWords_.insert("contribute");
        bonusWords_.insert("contribution");
        bonusWords_.insert("observe");
        bonusWords_.insert("observable");
        bonusWords_.insert("observation");
        bonusWords_.insert("action");
        bonusWords_.insert("sensor");
        bonusWords_.insert("network");
        bonusWords_.insert("neural");
        bonusWords_.insert("logic");
        bonusWords_.insert("logical");
        bonusWords_.insert("board");
        bonusWords_.insert("game");
        bonusWords_.insert("theory");
        bonusWords_.insert("atomic");
        bonusWords_.insert("factored");
        bonusWords_.insert("structured");
        bonusWords_.insert("learned");
        bonusWords_.insert("learning");
        bonusWords_.insert("algorithm");
        bonusWords_.insert("success");
        bonusWords_.insert("successfull");
        bonusWords_.insert("implies");
        bonusWords_.insert("equivalent");
        bonusWords_.insert("deterministic");
        bonusWords_.insert("stochastic");
        bonusWords_.insert("classical");
        bonusWords_.insert("planning");
        bonusWords_.insert("normalize");
        bonusWords_.insert("normalized");
        bonusWords_.insert("accomplish");
        bonusWords_.insert("accomplishment");
        bonusWords_.insert("experiment");
        bonusWords_.insert("thank");
        bonusWords_.insert("professor");
        bonusWords_.insert("student");
        bonusWords_.insert("course");
        bonusWords_.insert("task");
        bonusWords_.insert("clone");
        bonusWords_.insert("cloned");
        bonusWords_.insert("construct");
        bonusWords_.insert("boolean");
        bonusWords_.insert("discover");
        bonusWords_.insert("discovered");
        bonusWords_.insert("develop");
        bonusWords_.insert("developed");
        bonusWords_.insert("research");
        bonusWords_.insert("proposition");
        bonusWords_.insert("propositional");
        bonusWords_.insert("calculate");
        bonusWords_.insert("calculus");
        bonusWords_.insert("isolate");
        bonusWords_.insert("isolated");
        bonusWords_.insert("environment");
        bonusWords_.insert("probability");
        bonusWords_.insert("neighbour");
        bonusWords_.insert("nearest");
        bonusWords_.insert("autonomous");
        bonusWords_.insert("driver");
        bonusWords_.insert("lesson");
        bonusWords_.insert("unit");
        bonusWords_.insert("work");
        bonusWords_.insert("space");
        bonusWords_.insert("dimension");
        bonusWords_.insert("estimate");
        bonusWords_.insert("estimated");
        bonusWords_.insert("claude");
        bonusWords_.insert("shannon");
        bonusWords_.insert("scientific");
        bonusWords_.insert("paper");
        bonusWords_.insert("published");
        bonusWords_.insert("found");
        bonusWords_.insert("elwood");

    }

    static Dictionary*            pInst_;
    std::set<std::string>         words_;
    std::set<std::string>         trigrams_;
    std::map<std::string, size_t> trigramCounts_;  // with occurrence count
    std::set<std::string>         bonusWords_;
};
Dictionary* Dictionary::pInst_ = 0;
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8/////////9/////////A
class Particle // or organism in GA/EA terms
{
public:
    Particle(const bool preorder = true)
    {
        // initialize randomized
        for(uint8_t i=0; i<numColumn; ++i)
            order_[i] = i;
        std::random_shuffle(order_.begin(), order_.end());

        if(preorder)
        {
            boost::array<uint8_t, numColumn>::iterator it1 = order_.begin(), it2 = order_.begin();
            // move the elements with only spaces right of the others
            it1 = std::stable_partition(order_.begin(), order_.end(), bind(&Particle::GetSnippet, this, numRow-1, _1) != std::string(" "));

            // move the snippet ". " in the last line to the border between text and blank
            it2 = std::find_if(order_.begin(), order_.end(), bind(&Particle::GetSnippet, this, numRow-1, _1) == std::string(". "));
            std::swap(*--it1, *it2);

            // move the snippet "Cl" in the first line to the beginning, as it is the only one starting with a capital letter
            it1 = std::find_if(order_.begin(), order_.end(), bind(&Particle::GetSnippet, this, 0, _1) == std::string("cl"));
            std::swap(*it1, *order_.begin());
        }

        score_ = eval();
    }

    Particle(const Particle& rhs)
    {
        std::copy(rhs.order().begin(), rhs.order().end(), order_.begin());
        score_ = eval();
    }

    template<class ForwardRangeT>
    Particle(const ForwardRangeT& order)
    {
        std::copy(order.begin(), order.end(), order_.begin());
        score_ = eval();
    }

    const Particle& operator=(const Particle& rhs)
    {
        Particle cpy(rhs);
        std::copy(cpy.order().begin(), cpy.order().end(), order_.begin());
        score_ = cpy.score();
    }

    Particle mutate() const
    {
        std::vector<uint8_t> order;
        std::copy(order_.begin(), order_.end(), std::back_inserter(order));

        const size_t numMutations = (rand() % 2 ? 1 : 1 + rand() % 3);
        for(size_t i=0; i<numMutations; ++i)
        {
            const size_t frompos = rand() % numColumn;
            size_t       topos   = rand() % numColumn;
            const size_t width   = std::min<size_t>(std::min<size_t>(1 + rand() % 6, numColumn - frompos), numColumn - topos);

            std::vector<size_t> tmpval;
            std::copy(order.begin() + frompos, order.begin() + frompos + width, std::back_inserter(tmpval));
            order.erase(order.begin() + frompos, order.begin() + frompos + width);
            if(topos > frompos + width)
                topos -= width;
            order.insert(order.begin() + topos, tmpval.begin(), tmpval.end());
        }

        return Particle(order);
    }

    size_t score() const { return score_; }

    const boost::array<uint8_t, numColumn>& order() const { return order_; }

    std::string text() const
    {
        // unscrable the text with the given ordering
        std::stringstream sstr;
        for(size_t i=0; i<numRow; ++i)
        {
            for(size_t j=0; j<numColumn; ++j)
                sstr << ScrambledText::getInst().words()[i][order_[j]];
//            sstr << " ";
        }
        return sstr.str();
    }

    void report() const
    {
        std::copy(order_.begin(), order_.end(), std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
    }

private:
    const std::string GetSnippet(size_t line, size_t pos) const
    {
        const std::string str(ScrambledText::getInst().words()[line][pos]);
        return str;
    }

    template<class PairT>
    struct pair_first
    {
        typedef typename PairT::first_type result_type;
        result_type& operator()(const PairT& pp) { return pp.first; }
    };

    size_t eval() const
    {
        // try to unscramble the text with the given ordering
        std::stringstream sstr;
        for(size_t i=0; i<numRow; ++i)
        {
            for(size_t j=0; j<numColumn; ++j)
                sstr << GetSnippet(i, order_[j]);
//            sstr << " ";
        }

        // separate the words
        std::set<std::string> queryWords;
        std::copy(std::istream_iterator<std::string>(sstr), std::istream_iterator<std::string>(),
                  std::inserter(queryWords, queryWords.end()));

        return calcScore(queryWords);
    }

    size_t evalLastLine() const
    {
        // try to unscramble the last line with the given ordering
        std::stringstream sstr;
        // second last line : search backwards to the first blank
        for(size_t i=numRow-1; i>0; --i)
        {
            const std::string str(ScrambledText::getInst().words()[numRow-2][order_[i]]);
            if(!isalnum(str[1]))
            {
                for(size_t j=i+1; j<numColumn; ++j)
                    sstr << GetSnippet(numRow-2, order_[j]);
                break;
            }
            else if(!isalnum(str[0]))
            {
               for(size_t j=i; j<numColumn; ++j)
                    sstr << GetSnippet(numRow-2, order_[j]);
               break;
            }
        }
        // add the last line
        for(size_t j=0; j<numColumn; ++j)
            sstr << GetSnippet(numRow-1, order_[j]);

        // separate the words
        std::set<std::string> queryWords;
        std::copy(std::istream_iterator<std::string>(sstr), std::istream_iterator<std::string>(),
                  std::inserter(queryWords, queryWords.end()));

        return calcScore(queryWords);
    }

    size_t calcScore(const std::set<std::string>& queryWords) const
    {
        // find the words in the dictionary
        std::vector<std::string> matchWords;
        std::set_intersection(Dictionary::getInst().words().begin(), Dictionary::getInst().words().end(),
                              queryWords.begin(),   queryWords.end(),
                              std::back_inserter(matchWords));

        const size_t wordcount = matchWords.size();

        // don't count short words
        matchWords.erase(std::remove_if(matchWords.begin(), matchWords.end(), bind(&std::string::length, _1) < 3), matchWords.end());

        // sum up the lengths of all matching words
        const size_t charcount = std::accumulate(matchWords.begin(), matchWords.end(), 0, _1 + bind(&std::string::length, _2));

        // extract trigrams
        std::set<std::string> trigrams;
        BOOST_FOREACH(const std::string& word, queryWords)
            for(size_t i=0; i + 3 < word.length(); ++i)
                trigrams.insert(word.substr(i, i + 3));

        // find the trigrams in the dictionary
        std::vector<std::string> matchTrigrams;
        std::set_intersection(Dictionary::getInst().trigrams().begin(), Dictionary::getInst().trigrams().end(),
                              queryWords.begin(),   queryWords.end(),
                              std::back_inserter(matchTrigrams));

        const size_t trigramcount = matchTrigrams.size();

        // sum up the trigram scores
        size_t trigramscores = 0;
        BOOST_FOREACH(const std::string& trigram, matchTrigrams)
            trigramscores += Dictionary::getInst().trigramCounts().find(trigram)->second;

        // look for bonusWords
        std::vector<std::string> bonusWords;
        std::set_intersection(Dictionary::getInst().bonusWords().begin(), Dictionary::getInst().bonusWords().end(),
                              queryWords.begin(),   queryWords.end(),
                              std::back_inserter(bonusWords));

        const size_t bonusCount = bonusWords.size();

        return 40 * (wordcount + charcount) + trigramscores + 80 * bonusCount;
    }

    boost::array<uint8_t, numColumn> order_;
    size_t                           score_;
};
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8/////////9/////////A
int main(int argc, char* argv[])
{
    static const size_t populationSize = 50;

    // initialize a population of particles (or organisms or beams)
    boost::array<Particle, populationSize> Particles;

    std::sort(Particles.begin(), Particles.end(), bind(&Particle::score, _1) > bind(&Particle::score, _2));
    size_t bestScore = Particles.begin()->score();
    size_t stagnatedTurns = 0;


    // then evaluate on the full text
    for(size_t i=0; i < 5 || bestScore < 6000; ++i)
    {
        // mutate the particles
        for(size_t j=0; j<5; ++j)
            Particles[40+j] = Particles[j].mutate();
        for(size_t j=0; j<10; ++j)
            Particles[30+j] = Particles[j].mutate();
        for(size_t j=5; j<30; ++j)
            Particles[j] = Particles[j].mutate();
        for(size_t j=45; j<populationSize; ++j)
            Particles[j] = Particle(false);

        std::sort(Particles.begin(), Particles.end(), bind(&Particle::score, _1) > bind(&Particle::score, _2));

        if(Particles.begin()->score() > bestScore)
            bestScore = Particles.begin()->score();
        else
            ++stagnatedTurns;

        std::cout << "Turn " << i << " worst " << Particles.back().score() << " best " << bestScore
                  << " for " << Particles.begin()->text().substr(0, 46) << std::endl;
    }

    std::cout << std::endl << std::endl << "found a solution: " << std::endl << Particles.begin()->text();

    return 0;
}
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8/////////9/////////A
// Answer:



