#ifndef PERSON_XML_FILE_STORAGE
#define PERSON_XML_FILE_STORAGE

#include "person_file_storage.hpp"

// abtract class
struct PersonXMLFileStorage final : public PersonFileStorage
{
    // pure virtual methode 
    void save( const std::list<std::shared_ptr<Person>>& people ) override;
    std::list<std::shared_ptr<Person>> load() override;
};

#endif
