//
// Created by Umur Gedik on 5/3/16.
//

#include <iostream>
#include "Repository.h"
#include "RevWalker.h"

Repository::Repository(const string &path)
{
    if (git_repository_open(&m_repository, path.c_str()) != GIT_OK) {
        throw "Failed to open repository";
    }
}

Repository::~Repository()
{
    git_repository_free(m_repository);
}

git_repository * Repository::GetGitPointer()const
{
    return this->m_repository;
}

vector<Tag> Repository::GetTags()
{
    ReferenceIterator iterator{shared_from_this()};
    return GetTagsImplementation(iterator);
}

vector<Tag> Repository::GetTags(const string &partial_glob)
{
    string glob{"refs/tags/"};
    glob += partial_glob;

    ReferenceIterator iterator{shared_from_this(), glob};
    return GetTagsImplementation(iterator);
}

vector<Tag> Repository::GetTagsImplementation(ReferenceIterator &iterator)
{
    vector<Tag> tags;

    while (iterator.Next()) {
        if (!iterator.IsTag()) {
            continue;
        }

        tags.push_back(iterator.Item<Tag>());
    }

    sort(tags.begin(), tags.end(), Tag::DefaultComparator);

    return tags;
}

Tag Repository::GetLatestTag()
{
    auto tags = GetTags();

    if (tags.size() == 0)
        return Tag::Null;

    return tags[tags.size() - 1];
}

Tag Repository::GetLatestTag(const string &glob)
{
    auto tags = GetTags(glob);

    if (tags.size() == 0)
        return Tag::Null;

    return tags[tags.size() - 1];
}

vector<Commit> Repository::GetCommitsInRange(const string &from, const string &to)
{
    RevWalker walker{shared_from_this()};
    walker.PushRange(from, to);

    vector<Commit> commits;

    while (walker.Next()) {
        commits.emplace_back(walker.Item<Commit>());
    }

    sort(commits.begin(), commits.end(), Commit::DefaultComparator);

    return commits;
}










