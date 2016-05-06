//
// Created by Umur Gedik on 5/3/16.
//

#ifndef SUP_REFERENCEITERATOR_H
#define SUP_REFERENCEITERATOR_H


#include <memory>
#include <git2.h>

using namespace std;

class ReferenceIterator
{
    shared_ptr<class Repository> m_repository;
    git_reference_iterator *m_iterator = nullptr;
    git_reference *m_current_ref = nullptr;

    bool m_end_of_iterator = false;

public:
    ReferenceIterator(shared_ptr<class Repository> repository);
    ReferenceIterator(shared_ptr<class Repository> repository, const string &glob);
    ReferenceIterator(ReferenceIterator&& other)
    {
        m_repository = other.m_repository;
        m_iterator = other.m_iterator;
        m_current_ref = other.m_current_ref;

        other.m_iterator = nullptr;
        other.m_current_ref = nullptr;
    }

    ReferenceIterator(const ReferenceIterator&) = delete;

    ~ReferenceIterator();

    bool Next();
    bool IsBranch();
    bool IsTag();
    bool IsRemote();
    bool IsNote();
    bool IsValidName();

    template <class T>
    T Item()
    {
        return T::FromGitReference(*m_repository.get(), m_current_ref);
    }
};


#endif //SUP_REFERENCEITERATOR_H
