#include "person_xml_file_storage.hpp"

#include <pugixml.hpp>

using pugi::xml_document;
using pugi::xml_parse_result;
using pugi::xml_node;
using pugi::xml_attribute;

using std::to_string;
//using std::list;

using namespace std::string_literals;

void PersonXMLFileStorage::save( const std::list<std::shared_ptr<Person>>& people )
{
	xml_document document;
	
	xml_node declaration = document.prepend_child( pugi::node_declaration );
	declaration.append_attribute( "version" ) = "1.0";
	declaration.append_attribute( "encoding" ) = "UTF-8";
	declaration.append_attribute( "standalone" ) = "no";

	xml_node nodePeople = document.append_child( "people" );

	for( const auto& person : people )
	{
		xml_node nodePerson = nodePeople.append_child( "person" );

		nodePerson.append_attribute( "id" ) = to_string( person->getId() ).c_str();

		xml_node nodeForename = nodePerson.append_child( "forename" );
		nodeForename.append_child( pugi::node_pcdata ).set_value( person->getForename().c_str() );

		xml_node nodeSurname = nodePerson.append_child( "surname" );
		nodeSurname.append_child( pugi::node_pcdata ).set_value( person->getSurname().c_str() );
	}

	declaration.append_copy( nodePeople );
	document.save_file( "people.xml" );
}

std::list<std::shared_ptr<Person>> PersonXMLFileStorage::load()
{
	xml_document document;
	const xml_parse_result result = document.load_file( "people.xml" );
	if( !result )
		throw std::exception( result.description() );

	const xml_node nodePeople = document.child( "people" );
	if( nodePeople.empty() )
		throw std::exception( "empty file" );

	std::list<std::shared_ptr<Person>> people;

	for( const auto& nodePerson : nodePeople )
	{
		if( nodePerson.empty() )
			continue;

		const auto idAttribute = nodePerson.attribute( "id" );
		const auto id = idAttribute ? idAttribute.as_int() : 0;

		const auto forenameChild = nodePerson.child( "forename" );
		const auto forename = forenameChild ? forenameChild.text().as_string() : ""s;

		const auto surnameChild = nodePerson.child( "surname" );
		const auto surname = surnameChild ? surnameChild.text().as_string() : ""s;

		people.emplace_back( makePersonShared( id, forename, surname ) );
	}

    return people;
}
