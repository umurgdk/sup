cmake_minimum_required(VERSION 3.5)
project(sup)

include(FindPkgConfig)

set(Boost_USE_STATIC_LIBS ON)

pkg_check_modules(libgit2 REQUIRED libgit2>=0.2.34)
include_directories(${libgit2_INCLUDE_DIRS})

FIND_PACKAGE(Boost COMPONENTS program_options filesystem REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES git/Repository.cpp git/Repository.h git/Tag.cpp git/Tag.h git/Signature.cpp git/Signature.h git/RevWalker.cpp git/RevWalker.h git/ReferenceIterator.cpp git/ReferenceIterator.h git/Commit.cpp git/Commit.h ChangeLogEntry.cpp ChangeLogEntry.h parsers/EntryTypeParser.cpp parsers/EntryTypeParser.h parsers/EntryMessageParser.cpp parsers/EntryMessageParser.h parsers/IssueIdParser.cpp parsers/IssueIdParser.h ConfigParser.cpp ConfigParser.h)
add_executable(sup main.cpp ${SOURCE_FILES})
target_link_libraries(sup git2 ${Boost_LIBRARIES} ${libgit2_LIBRARIES})