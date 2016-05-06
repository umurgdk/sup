//
// Created by Umur Gedik on 5/4/16.
//

#include <sstream>
#include <vector>
#include <regex>
#include <numeric>
#include "EntryMessageParser.h"
#include "../ChangeLogEntry.h"

string EntryMessageParser::Parse(const string &message)
{
    istringstream stream{message};
    vector<string> lines;

    string line;
    while (getline(stream, line)) {
        lines.emplace_back(line);
    }

    if (m_options.one_line) {
        if (m_options.line_number <= lines.size()) {
            return lines[m_options.line_number - 1];
        }
    }

    if (m_options.until_delimiter) {
        int current_line_number = m_options.from_line - 1;
        vector<string> collected_lines;

        while(current_line_number < lines.size() && lines[current_line_number] != m_options.delimiter) {
            collected_lines.emplace_back(lines[current_line_number]);
            current_line_number += 1;
        }

        string result = "";
        for (int i = 0; i < collected_lines.size(); i++) {
            result += collected_lines[i];

            if (i < collected_lines.size() - 1) {
                result += "\n";
            }
        }

        return result;
    }

    if (m_options.regex_based) {
        smatch match;
        regex parser{m_options.regex};

        if (regex_search(message, match, parser)) {
            return match[1];
        }
    }

    return "";
}