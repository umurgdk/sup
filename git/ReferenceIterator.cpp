//
// Created by Umur Gedik on 5/3/16.
//

#include <iostream>
#include "ReferenceIterator.h"
#include "Repository.h"

ReferenceIterator::ReferenceIterator(shared_ptr<Repository> repository)
    : m_repository{repository}
{
    git_reference_iterator_new(&m_iterator, m_repository->GetGitPointer());
}

ReferenceIterator::ReferenceIterator(shared_ptr<Repository> repository, const string &glob)
    : m_repository{repository}
{
    git_reference_iterator_glob_new(&m_iterator, m_repository->GetGitPointer(), glob.c_str());
}

ReferenceIterator::~ReferenceIterator()
{
    if (m_current_ref != nullptr && !m_end_of_iterator) {
        git_reference_free(m_current_ref);
    }

    if (m_iterator != nullptr) {
        git_reference_iterator_free(m_iterator);
    }
}

bool ReferenceIterator::Next()
{
    if (m_current_ref != nullptr) {
        git_reference_free(m_current_ref);
    }

    bool success = git_reference_next(&m_current_ref, m_iterator) == GIT_OK;
    m_end_of_iterator = !success;

    return success;
}


bool ReferenceIterator::IsBranch()
{
    return git_reference_is_branch(m_current_ref) == 1;
}

bool ReferenceIterator::IsTag()
{
    return git_reference_is_tag(m_current_ref) == 1;
}

bool ReferenceIterator::IsRemote()
{
    return git_reference_is_remote(m_current_ref) == 1;
}

bool ReferenceIterator::IsNote()
{
    return git_reference_is_note(m_current_ref) == 1;
}

bool ReferenceIterator::IsValidName()
{
    return git_reference_is_valid_name(git_reference_name(m_current_ref)) == 1;
}