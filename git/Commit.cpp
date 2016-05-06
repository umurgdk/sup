//
// Created by Umur Gedik on 5/4/16.
//

#include "Repository.h"
#include "Commit.h"

Commit Commit::Null{};

Commit Commit::FromGitReference(const class Repository &repo, git_reference *ref)
{
    git_oid oid;
    git_reference_name_to_id(&oid, repo.GetGitPointer(), git_reference_name(ref));

    return Commit::FromGitOid(repo, oid);
}

Commit Commit::FromGitOid(const class Repository &repo, const git_oid &oid)
{
    git_commit *commit;

    if (git_commit_lookup(&commit, repo.GetGitPointer(), &oid) != GIT_OK) {
        string message{"Git commit lookup failed for oid: "};
        message += git_oid_tostr_s(&oid);
        throw message;
    }

    return Commit{repo, commit};
}

bool Commit::operator==(const Commit &other)
{
    return false;
}


