//
// Created by Umur Gedik on 5/4/16.
//

#include "IssueIdParser.h"

string IssueIdParser::Parse(const string &message)
{
    smatch match;

    if (regex_search(message, match, m_regex)) {
        return match[1];
    }

    return "";
}

