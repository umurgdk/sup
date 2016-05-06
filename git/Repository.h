//
// Created by Umur Gedik on 5/3/16.
//

#ifndef SUP_REPOSITORY_H
#define SUP_REPOSITORY_H

#include <memory>
#include <string>

#include <git2.h>
#include <vector>
#include "ReferenceIterator.h"
#include "Tag.h"
#include "Commit.h"

using namespace std;

class Repository : public enable_shared_from_this<Repository>
{
    git_repository *m_repository;

    vector<Tag> GetTagsImplementation(ReferenceIterator &iter);

public:
    Repository(const string &path);
    virtual ~Repository();

    git_repository * GetGitPointer()const;

    vector<Tag> GetTags();
    vector<Tag> GetTags(const string &partial_glob);

    Tag GetLatestTag();
    Tag GetLatestTag(const string &glob);

    vector<Commit> GetCommitsInRange(const string &from, const string &to);
};


#endif //SUP_REPOSITORY_H
