CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

PROJECT(ENUM_MODE)


if (MSVC)
    MESSAGE(STATUS "StartBuildEnumMode")
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        #CMAKE_C_FLAGS
        #CMAKE_C_FLAGS_DEBUG
        #CMAKE_C_FLAGS_RELEASE
        )
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif(MSVC)

#ADD_SUBDIRECTORY(privilege)

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
SET(SOURCE_LIST
    ${CMAKE_SOURCE_DIR}/privilege/SeDebugPrivilege.cpp
    main.cpp
    )

ADD_EXECUTABLE( ${PROJECT_NAME} ${SOURCE_LIST})
