PROJECT("test")

ADD_COMPILE_OPTIONS(-g)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE -pthread)
