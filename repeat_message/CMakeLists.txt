PROJECT(test)

INCLUDE(${PROJECT_SOURCE_DIR}/CCommon.cmake)

SetSetting(${PROJECT_SOURCE_DIR}/bin)

#IsBit()

ADD_SUBDIRECTORY(hook)

ADD_SUBDIRECTORY(repeat_message)