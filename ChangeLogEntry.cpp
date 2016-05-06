//
// Created by Umur Gedik on 5/4/16.
//

#include <map>
#include "ChangeLogEntry.h"

ChangeLogEntry ChangeLogEntry::FromString(const EntryTypeParserOptions &type_options,
                                          const EntryMessageParserOptions &message_options,
                                          const string &issue_id_regex,
                                          const string &content)
{
    ChangeLogEntry entry;

    EntryTypeParser type_parser{type_options};
    EntryMessageParser message_parser{message_options};
    IssueIdParser issue_id_parser{issue_id_regex};

    entry.type = type_parser.Parse(content);
    entry.body = message_parser.Parse(content);
    entry.issue_id = issue_id_parser.Parse(content);

    return entry;
}
