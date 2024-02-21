#ifndef PERSON
#define PERSON

#include <string>
#include <memory>
#include <utility>

class Person
{
public:
	Person( const std::size_t id, std::string forename, std::string surname );
	virtual ~Person();

    std::uint64_t getId() const;

	std::string getSurname() const;
	
	std::string getForename() const;

private:
    std::uint64_t id_;
	std::string forename_;
	std::string surname_;
};

template<typename... Args>
auto makePersonShared( Args&&... args )
{
	return std::make_shared<Person>( std::forward<Args>(args)... );
}

template<typename... Args>
auto makePersonUnique( Args&&... args )
{
    return std::make_unique<Person>( std::forward<Args>(args)... );
}

#endif
