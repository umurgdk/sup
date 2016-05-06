//
// Created by Umur Gedik on 5/3/16.
//

#ifndef SUP_REVWALKER_H
#define SUP_REVWALKER_H


#include <git2.h>
#include <memory>
#include "Repository.h"

class RevWalker
{
    weak_ptr<Repository> m_repository;
    git_revwalk *m_revwalk;
    git_oid m_current_oid;

public:
    RevWalker(weak_ptr<Repository> repository);
    RevWalker(RevWalker&& other)
    {
        m_repository = other.m_repository;
        m_revwalk = other.m_revwalk;
        m_current_oid = other.m_current_oid;

        other.m_revwalk = nullptr;
    }

    RevWalker(const RevWalker&) = delete;

    ~RevWalker();

    void PushRange(const string &from, const string &to);
    bool Next();

    template <class T>
    T Item()
    {
        if (auto repo = m_repository.lock()) {
            return T::FromGitOid(*repo, m_current_oid);
        }

        return T::Null;
    }
};


#endif //SUP_REVWALKER_H
