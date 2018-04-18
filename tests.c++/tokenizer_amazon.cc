// c++ -O2 -std=c++1y -Wall -Werror tokenizer tokenizer.cc
#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

class dictionary_t
{
public:
    bool is_valid(const string &word) const
    {
        return dict_.find(word) != dict_.end();
    }

private:
    const set<string> dict_{"be", "bed", "bath", "and", "behaviour", "this", "is", "not", "valid", "neither"};

};


class Tokenizer
{
public:
    Tokenizer(dictionary_t &dict): dict_(dict) {}
    bool operator() (const string &s)
    {
        return tokenizer_(s, 0, s.size());
    }

private:
    dictionary_t dict_;

    bool tokenizer_(const string &full_s, size_t start, size_t len)
    {
        auto   s = full_s.substr(start, len);
        size_t new_start;
        size_t new_len;

        if (dict_.is_valid(s))
        {
            new_start = start + len;
            new_len   = full_s.size() - new_start;
            if (0 == new_len) return true;

        }
        else
        {
            new_start = start;
            new_len   = len - 1;

            if (0 == new_len) return false;
        }

        return tokenizer_(full_s, new_start, new_len);
    }
};


int main()
{
    dictionary_t dict;
    Tokenizer tokenizer{dict};

    map<string, bool> test_strings {
        {"bedbathandbehaviour", true},
        {"thisisnotvalidd", false},
        {"tisneither", false}
    };


    for (auto const &s : test_strings) {
        if (s.second != tokenizer(s.first)) {
            cout << "** Error checking: " + s.first + " should be " << s.second << endl;
        }
        else {
            cout << "Great result for " + s.first + "!!" << endl;
        }
    }


    return 0;
}
