//
// Created by Umur Gedik on 5/4/16.
//

#ifndef SUP_ISSUEIDPARSER_H
#define SUP_ISSUEIDPARSER_H

#include <regex>

using namespace std;

class IssueIdParser
{
    regex m_regex;

public:
    IssueIdParser(const string &regex)
        : m_regex{regex}
    { }

    string Parse(const string &message);
};


#endif //SUP_ISSUEIDPARSER_H
