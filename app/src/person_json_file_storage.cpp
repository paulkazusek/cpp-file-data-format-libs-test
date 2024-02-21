#include "person_json_file_storage.hpp"

#include <json.hpp>

#include <fstream>

using nlohmann::json;

void PersonJSONFileStorage::save( const std::list<std::shared_ptr<Person>>& people )
{
    json data;
	data["people"]["person"] = json::array();

	for( const auto& person : people )
	{
		json jsonPerson;
		jsonPerson["id"] = person->getId();
		jsonPerson["forename"] = person->getForename();
		jsonPerson["surname"] = person->getSurname();

		data["people"]["person"].push_back( jsonPerson );
	}

	std::ofstream file;
	file.open( "people.json", std::ios::trunc | std::ios::out );
	file << data.dump( 2 );
	file.close();
}

std::list<std::shared_ptr<Person>> PersonJSONFileStorage::load()
{
    std::ifstream file;
	file.open( "people.json", std::ios::in );
	json data = json::parse( file );
	file.close();

	std::list<std::shared_ptr<Person>> people;

	const auto& root = data["people"];
	for( const auto& jsonPerson : root["person"] )
	{
		const auto id = jsonPerson.at( "id" ).get<std::size_t>();
		const auto forename = jsonPerson.at( "forename" ).get<std::string>();
		const auto surname = jsonPerson.at( "surname" ).get<std::string>();

		people.emplace_back( makePersonShared( id, forename, surname ) );
	}

	return people;
}
