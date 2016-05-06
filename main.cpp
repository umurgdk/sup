#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include <map>
#include <memory>

#include <git2.h>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

#include "git/Repository.h"
#include "ConfigParser.h"
#include "ChangeLogEntry.h"

using namespace std;
using namespace boost;

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char **argv)
{
    po::options_description description("Allowed options");
    description.add_options()
        ("help", "prints this message")
        ("repository", po::value<string>()->default_value("."), "path to repository")
        ("version", po::value<string>(), "new version number to be rendered as title");

    po::variables_map options;
    po::store(po::parse_command_line(argc, argv, description), options);

    if (!options.count("version")) {
        cout << "version number is required for generated changlelog." << '\n';
        cout << description << '\n';
        return 1;
    }

    string repository_path{options["repository"].as<string>()};
    string version{options["version"].as<string>()};

    git_libgit2_init();

    auto supfile_path = fs::absolute(fs::path(options["repository"].as<string>()) / fs::path(".sup"), fs::current_path());

    if (!fs::exists(supfile_path)) {
        cout << "ERROR: Sup file not found! (" << supfile_path << ")" << endl;
    }

    SupConfig config = ConfigParser::Parse(supfile_path);

    std::shared_ptr<Repository> repository{new Repository(repository_path)};
    auto tag = repository->GetLatestTag(config.tag_filter);

    if (tag == Tag::Null) {
        cout << "No tags found!" << endl;
        return 0;
    }

    cout << "Inspecting commits between: " << tag.name << "..HEAD" << endl;

    vector<Commit> commits = repository->GetCommitsInRange(tag.name, "HEAD");
    map<string, stringstream> output_by_issue_types;
    stringstream output;

    output << "# " << version << '\n';

    regex merge_regex{config.filter_regex};
    smatch matcher;
    int collected_entries_count = 0;
    for (const auto &commit : commits) {
        if (!regex_search(commit.message, matcher, merge_regex)) {
            continue;
        }

        auto entry = ChangeLogEntry::FromString(config.entry_type_parser_options, config.message_parser_options, config.issue_id_regex,
                                                commit.message);
        auto new_template = config.entry_template;

        if (config.group_by_issue_type && output_by_issue_types.count(entry.type) == 0) {
            output_by_issue_types[entry.type] = stringstream{};
        }

        if (config.omit_newlines) {
            replace_all(entry.body, "\n", " ");
        }

        replace_all(new_template, "$issueId", entry.issue_id);
        replace_all(new_template, "$body", entry.body);
        replace_all(new_template, "$issueType", entry.type);

        collected_entries_count += 1;

        if (config.group_by_issue_type) {
            output_by_issue_types[entry.type] << new_template << '\n';
        } else {
            output << new_template << '\n';
        }
    }

    if (collected_entries_count == 0) {
        cout << "No commits added to changelog!" << endl;
        return 0;
    }

    if (config.group_by_issue_type) {
        for (const auto &pair : output_by_issue_types) {
            output << "### " << pair.first << '\n' << pair.second.str() << '\n';
        }
    }

    auto markdown_path = supfile_path.parent_path() / fs::path(config.file_path);

    ifstream file_to_read{markdown_path.string()};

    std::string str = "";

    if (file_to_read.good()) {
        file_to_read.seekg(0, std::ios::end);
        str.reserve(file_to_read.tellg());
        file_to_read.seekg(0, std::ios::beg);

        str.assign((std::istreambuf_iterator<char>(file_to_read)),
                   std::istreambuf_iterator<char>());

        output << str;
    }

    file_to_read.close();

    ofstream file_to_write{markdown_path.string()};
    file_to_write << output.str();

    return 0;
}