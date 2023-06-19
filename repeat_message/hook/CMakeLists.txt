PROJECT(hooks)

IsCompile("false")

SET(src hook_helper.cpp)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${src})

BinaryAttribute(${PROJECT_NAME} ${PROJECT_NAME} "none" "none")




