//
// Created by Umur Gedik on 5/4/16.
//

#ifndef SUP_COMMIT_H
#define SUP_COMMIT_H

#include <string>
#include <git2.h>
#include "Signature.h"

using namespace std;

class Repository;

struct Commit
{
    git_oid id;
    string message;
    string summary;
    Signature signature;

    Commit()
        : message{""}, summary{""}, signature{Signature::Null}
    { }

    Commit(const Repository &repo, git_commit *commit)
        : message{git_commit_message(commit)}, summary{git_commit_summary(commit)}, signature{git_commit_author(commit)}
    {
        id = *git_commit_id(commit);
        git_commit_free(commit);
    }

    Commit(const Commit &other)
        : message{other.message}, summary{other.summary}, signature{other.signature}
    {
        id = other.id;
    }

    static bool DefaultComparator(const Commit &left, const Commit &right)
    {
        return left.signature.when < right.signature.when;
    }

    static Commit FromGitReference(const class Repository &repo, git_reference *ref);

    static Commit FromGitOid(const class Repository &repo, const git_oid &oid);

    static Commit Null;

    bool operator==(const Commit &other);
};


#endif //SUP_COMMIT_H
