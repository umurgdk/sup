//
// Created by Umur Gedik on 5/3/16.
//

#include "RevWalker.h"

RevWalker::RevWalker(weak_ptr<Repository> repository)
        : m_repository(repository)
{
    if (auto repo = m_repository.lock()) {
        git_revwalk_new(&m_revwalk, repo->GetGitPointer());
    }
}

RevWalker::~RevWalker()
{
    if (m_revwalk != nullptr) {
        git_revwalk_free(m_revwalk);
    }
}

void RevWalker::PushRange(const string &from, const string &to)
{
    git_revwalk_push_range(m_revwalk, (from + ".." + to).c_str());
}

bool RevWalker::Next()
{
    return git_revwalk_next(&m_current_oid, m_revwalk) == GIT_OK;
}



