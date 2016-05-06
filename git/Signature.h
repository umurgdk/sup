//
// Created by Umur Gedik on 5/3/16.
//

#ifndef SUP_SIGNATURE_H
#define SUP_SIGNATURE_H

#include <string>
#include <git2.h>

using namespace std;

struct Signature
{
    string name;
    string email;
    int64_t when;

    Signature() : name{""}, email{""}, when{0}
    { }

    Signature(const git_signature *signature)
        : name{signature->name}, when{signature->when.time}, email{signature->email}
    { }

    Signature(const Signature &other)
        : name{other.name}, email{other.email}, when{other.when}
    { }

    bool operator==(const Signature &other)
    {
        return name == other.name && email == other.email && when == other.when;
    }

    static const Signature Null;
};

#endif //SUP_SIGNATURE_H
