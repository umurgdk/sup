//
// Created by Umur Gedik on 5/4/16.
//

#include <sstream>
#include <vector>
#include <regex>
#include "EntryTypeParser.h"

string EntryTypeParser::Parse(const string &content)
{
    istringstream stream{content};
    vector<string> lines;

    string line;
    while (getline(stream, line)) {
        lines.emplace_back(line);
    }

    if (m_options.line_based) {
        if (m_options.line_number <= lines.size()) {
            return lines[m_options.line_number - 1];
        }
    }

    if (m_options.regex_based) {
        string regex_subject = content;
        smatch match;
        regex parser{m_options.regex};

        if (m_options.search_in_line && m_options.line_number <= lines.size()) {
            regex_subject = lines[m_options.line_number - 1];
        }

        if (regex_search(regex_subject, match, parser)) {
            return match[1];
        }
    }

    return "feature";
}