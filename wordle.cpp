#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    unsigned int count = 0;
    set<string> result;
    string temp_string = in;
    for (unsigned int cnt = 0; cnt < in.size(); ++cnt)
    {
        if (in.at(cnt) == '-')
        {
            count++;
        }
    }
    if (!count)
    {
        if (dict.find(temp_string) != dict.end() && floating == "")
    {
        result.insert(in);
    }
    return result;
    }
    
    if (count < floating.size())
    {
        return result;
    }
   

 for (unsigned int i = 0; i < temp_string.size(); ++i)
    {
        if (temp_string[i] == '-')
        {
            for (unsigned int j = 0; j < 26; ++j)
            {
                char c = 'a' + j;
                string pass_on = floating;

                for (unsigned int k = 0; k < floating.size(); ++k)
                {
                    if (floating.at(k) == c)
                    {
                        pass_on.erase(k, 1);
                        break;
                    }
                }
                temp_string[i] = c;
                set<string> produced_strings = wordle(temp_string, pass_on, dict);
                result.insert(produced_strings.begin(), produced_strings.end());
            }
        }
    }


    return result;


}