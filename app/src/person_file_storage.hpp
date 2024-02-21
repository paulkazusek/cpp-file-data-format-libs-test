#ifndef PERSON_FILE_STORAGE
#define PERSON_FILE_STORAGE

#include "person.hpp"

#include <list>
#include <memory>

// abtract class
struct PersonFileStorage
{
    // pure virtual methode 
    virtual void save( const std::list<std::shared_ptr<Person>>& people ) = 0;

    //virtual void save( const std::list<std::shared_ptr<Person>>& people, 
    //                   const std::string& path = "", 
    //                   const std::string& filename = "" ) = 0;

    virtual std::list<std::shared_ptr<Person>> load() = 0;
};

#endif
