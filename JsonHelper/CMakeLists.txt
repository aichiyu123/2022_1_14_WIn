PROJECT(test)

SET(rapidjson_path $ENV{RAPID_JSON})

MESSAGE(STATUS "RapidJsonPath: ${rapidjson_path}")

INCLUDE_DIRECTORIES(${rapidjson_path})

SET(src json.cpp main.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${src})
