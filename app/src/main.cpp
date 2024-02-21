#include "file_storage_format.hpp"
#include "person_json_file_storage.hpp"
#include "person_xml_file_storage.hpp"

#include <iostream>
#include <format>

using SharedPersonList = std::list<std::shared_ptr<Person>>;

void generateTestData( std::unique_ptr<PersonFileStorage> storage )
{
    std::list<std::shared_ptr<Person>> people;
    people.push_back( makePersonShared( 10001, "Joe", "Doe" ) );
    people.push_back( makePersonShared( 10002, "Jane", "Doe" ) );

    storage->save( people );
}

void printAllPeople( const std::list<std::shared_ptr<Person>>& people )
{
    const std::uint8_t idLength{ 12 }, forenameLength{ 13 }, surnameLength{ 15 };
    //const std::string separator = std::format("+{:-<10}+", "") + std::format("{:-<17}+", "") + std::format("{:-<17}+", "") + "\n";
    const std::string separator = std::format( "+{0:-<{1}}", "", idLength + 2 ) 
                                + std::format( "+{0:-<{1}}", "", forenameLength + 2 ) 
                                + std::format( "+{0:-<{1}}", "", surnameLength + 2 ) 
                                + "+\n";
    
    std::cout << separator;
    //std::cout << std::format( "| {:<} | {:<15} | {:<15} |\n", "Id", "Forename", "Surname" );
    std::cout << std::format( "| {0:<{1}} | {2:<{3}} | {4:<{5}} |\n", "Id", idLength, "Forename", forenameLength, "Surname", surnameLength );
    std::cout << separator;

    for ( const auto& person : people )
    {
        //std::cout << std::format("| {0:<{1}} | {2:<{3}} | {4:<{5}} |\n", person->getId(), idLength, person->getForename(), forenameLength, person->getSurname(), surnameLength );
        std::cout << std::format( "| {0:<{1}} ", person->getId(), idLength )
                  << std::format( "| {0:<{1}} ", person->getForename(), forenameLength )
                  << std::format( "| {0:<{1}} ", person->getSurname(), surnameLength )
                  << std::format( "|\n", "");
    }

    std::cout << separator;
}

void printMainMenu()
{
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Print all people" << std::endl;
    std::cout << "2. Programm terminate" << std::endl;
}

int main( int argc, char *argv[] )
{
    FileStorageFormat format = FileStorageFormat::JSON;
    std::unique_ptr<PersonFileStorage> storage;

    if ( format == FileStorageFormat::XML )
    {
        storage = std::make_unique<PersonXMLFileStorage>();
    }
    else if( format == FileStorageFormat::JSON )
    {
        storage = std::make_unique<PersonJSONFileStorage>();
    }
    else
    {
        std::cerr << "failure" << std::endl;
        std::exit( EXIT_FAILURE );
    }

    int choice{ 0 };

    do
    {
        printMainMenu();
        std::cout << "Choose an option" << std::endl;
        std::cin >> choice;

        switch( choice )
        {
            case 1:
            {
                const auto people = storage->load();
                printAllPeople( people );
                break;
            }
            default:
                std::cout << "Invalid entry. Please select again." << std::endl;
        }

    } while ( choice != 2 );

    return EXIT_SUCCESS;
}
