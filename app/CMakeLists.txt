project(app)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

add_executable(${PROJECT_NAME}
	src/file_storage_format.hpp
	src/main.cpp
	src/person_file_storage.hpp
	src/person_json_file_storage.cpp
	src/person_json_file_storage.hpp
	src/person_xml_file_storage.cpp
	src/person_xml_file_storage.hpp
	src/person.cpp
	src/person.hpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		RapidXML
		pugixml
		json
)
