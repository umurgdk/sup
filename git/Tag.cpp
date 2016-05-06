//
// Created by Umur Gedik on 5/3/16.
//

#include <iostream>
#include "Repository.h"
#include "Tag.h"

Tag Tag::Null{};

Tag Tag::FromGitReference(const Repository &repo, git_reference *ref)
{
    git_oid oid;
    git_reference_name_to_id(&oid, repo.GetGitPointer(), git_reference_name(ref));

    return Tag::FromGitOid(repo, oid);
}

Tag Tag::FromGitOid(const Repository &repo, const git_oid &oid)
{
    git_tag *tag;

    if (git_tag_lookup(&tag, repo.GetGitPointer(), &oid) != GIT_OK) {
        return Tag::Null;
    }

    return Tag{repo, tag};
}

bool Tag::operator==(const Tag &other)
{
    return name == other.name && signature == other.signature;
}








