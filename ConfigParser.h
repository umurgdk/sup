//
// Created by Umur Gedik on 5/4/16.
//

#ifndef SUP_CONFIGPARSER_H
#define SUP_CONFIGPARSER_H

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/path.hpp>
#include "parsers/EntryMessageParser.h"
#include "parsers/EntryTypeParser.h"

using namespace std;
namespace pt = boost::property_tree;
namespace fs = boost::filesystem;

typedef struct SupConfig {
    EntryMessageParserOptions message_parser_options;
    EntryTypeParserOptions entry_type_parser_options;
    string issue_id_regex;

    string entry_template = "";
    string filter_regex = ".*";
    string tag_filter = "v*";
    string file_path;
    bool omit_newlines = false;
} SupConfig;

class ConfigParser
{
    static void ParseEntryTypeParserOptions(const pt::ptree &tree, EntryTypeParserOptions &options);
    static void ParseMessageParserOptions(const pt::ptree &pt, EntryMessageParserOptions &options);

public:

    static SupConfig Parse(const fs::path &path = ".sup");
};


#endif //SUP_CONFIGPARSER_H
