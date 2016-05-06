//
// Created by Umur Gedik on 5/4/16.
//

#ifndef SUP_ENTRYMESSAGEPARSER_H
#define SUP_ENTRYMESSAGEPARSER_H

#include <string>

using namespace std;

typedef struct
{
    bool regex_based = false;
    bool one_line = false;
    bool until_delimiter = true;
    int line_number = 0;
    int from_line = 2;
    string delimiter = "---";
    string regex = ".*";
} EntryMessageParserOptions;

class EntryMessageParser
{
    EntryMessageParserOptions m_options;

public:
    EntryMessageParser(const EntryMessageParserOptions &options)
        : m_options{options}
    { }

    string Parse(const string &message);
};


#endif //SUP_ENTRYMESSAGEPARSER_H
