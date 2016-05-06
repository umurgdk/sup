//
// Created by Umur Gedik on 5/4/16.
//

#ifndef SUP_ENTRYTYPEPARSER_H
#define SUP_ENTRYTYPEPARSER_H

#include <string>

using namespace std;

typedef struct EntryTypeParserOptions {
    bool regex_based = false;
    bool line_based = false;
    bool search_in_line = false;
    int line_number = 0;
    string regex = "(feature|bugfix)/";
} EntryTypeParserOptions;

class EntryTypeParser
{
    EntryTypeParserOptions m_options;

public:
    EntryTypeParser(const EntryTypeParserOptions &options)
        : m_options{options}
    { }

    string Parse(const string &content);
};


#endif //SUP_ENTRYTYPEPARSER_H
