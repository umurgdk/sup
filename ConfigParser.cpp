//
// Created by Umur Gedik on 5/4/16.
//

#include <fstream>
#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <boost/filesystem/path.hpp>
#include "ConfigParser.h"
#include "parsers/EntryTypeParser.h"
#include "parsers/EntryMessageParser.h"

SupConfig ConfigParser::Parse(const fs::path &path)
{
    std::ifstream fs{path.string()};

    pt::ptree tree;
    pt::read_json(fs, tree);

    SupConfig config;

    auto issue_type_tree = tree.get_child_optional("issueType");
    if (issue_type_tree) {
        ParseEntryTypeParserOptions(*issue_type_tree, config.entry_type_parser_options);
    }

    auto body_tree = tree.get_child_optional("body");
    if (body_tree) {
        ParseMessageParserOptions(*body_tree, config.message_parser_options);
    }

    config.issue_id_regex = tree.get<string>("issueIdRegex", "#(\\d+)");
    config.entry_template = tree.get<string>("template", "[$issueId] $body");
    config.omit_newlines = tree.get<bool>("omitNewlinesInBody", false);
    config.filter_regex = tree.get<string>("filter", ".*");
    config.tag_filter = tree.get<string>("tagFilter", "v*");
    config.file_path = tree.get<string>("file", "CHANGELOG.md");
    config.group_by_issue_type = tree.get<bool>("groupByIssueType", true);

    return config;
}

void ConfigParser::ParseEntryTypeParserOptions(const pt::ptree &tree, EntryTypeParserOptions &options)
{
    auto regex = tree.get_optional<string>("regex");
    if (regex) {
        options.regex = *regex;
        options.regex_based = true;
    }

    auto line_number = tree.get_optional<int>("lineNumber");
    if (line_number) {
        options.line_number = *line_number;
        options.line_based = true;
        options.regex_based = false;
    }

    auto searchAt = tree.get_optional<int>("searchAt");
    if (regex && searchAt) {
        options.line_number = *searchAt;
        options.line_based = false;
        options.regex_based = true;
    }
}

void ConfigParser::ParseMessageParserOptions(const boost::property_tree::ptree &pt, EntryMessageParserOptions &options)
{
    auto line_number = pt.get_optional<int>("lineNumber");
    if (line_number) {
        options.line_number = *line_number;
        options.regex_based = false;
        options.one_line = true;
        return;
    }

    auto regex = pt.get_optional<string>("regex");
    if (regex) {
        options.regex = *regex;
        options.regex_based = true;
        return;
    }

    auto start_from = pt.get_optional<int>("startingAt");
    if (start_from) {
        options.from_line = *start_from;
    }

    auto delimiter = pt.get_optional<string>("endOfBody");
    if (delimiter) {
        options.delimiter = *delimiter;
        options.until_delimiter = true;
    }
}





















