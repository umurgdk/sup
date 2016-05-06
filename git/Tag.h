//
// Created by Umur Gedik on 5/3/16.
//

#ifndef SUP_TAG_H
#define SUP_TAG_H

#include <iostream>
#include <string>
#include <git2.h>

#include "Signature.h"

using namespace std;

struct Tag
{
    string name;
    string message;
    Signature signature;

    Tag()
        : name{""}, message{""}, signature{Signature::Null}
    { }

    Tag(const class Repository &owner, git_tag *tag)
        : name{git_tag_name(tag)}, message{git_tag_message(tag)}, signature{git_tag_tagger(tag)}
    {
        git_tag_free(tag);
    }

    Tag(const Tag &other)
        : name{other.name}, message{other.message}, signature{other.signature}
    { }

    static bool DefaultComparator(const Tag &left, const Tag &right)
    {
        return left.signature.when < right.signature.when;
    }

    static Tag FromGitReference(const class Repository &repo, git_reference *ref);

    static Tag FromGitOid(const class Repository &repo, const git_oid &oid);

    static Tag Null;

    bool operator==(const Tag &other);
};

#endif //SUP_TAG_H
