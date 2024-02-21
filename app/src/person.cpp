#include "person.hpp"

Person::Person( const std::uint64_t id, std::string forename, std::string surname )
    : id_{ id }
    , forename_{ std::move( forename )}
    , surname_{ std::move( surname ) }
{
}

Person::~Person() = default;

std::size_t Person::getId() const
{
    return id_;
}

std::string Person::getSurname() const
{
    return forename_;
}

std::string Person::getForename() const
{
    return surname_;
}



