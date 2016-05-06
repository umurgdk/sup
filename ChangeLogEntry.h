//
// Created by Umur Gedik on 5/4/16.
//

#ifndef SUP_CHANGELOGENTRY_H
#define SUP_CHANGELOGENTRY_H

#include <string>
#include "git/Commit.h"
#include "parsers/EntryTypeParser.h"
#include "parsers/EntryMessageParser.h"
#include "parsers/IssueIdParser.h"

using namespace std;

struct ChangeLogEntry
{
    string type;
    string issue_id;
    string body;

    static ChangeLogEntry FromString(const EntryTypeParserOptions &type_options,
                                     const EntryMessageParserOptions &message_options,
                                     const string &issue_id_regex,
                                     const string &content);
};


#endif //SUP_CHANGELOGENTRY_H
