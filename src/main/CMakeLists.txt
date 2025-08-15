# MIT License 
# Copyright (c) 2018-Today Michele Adduci <adduci@tutanota.com>
#
# helloapp target instructions

#####################################
# Define Target Information
#####################################
set(TARGET_NAME mainapp)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(${TARGET_NAME} ${TARGET_SOURCES})


target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(${TARGET_NAME} PRIVATE project_options project_warnings)
target_link_libraries(${TARGET_NAME} PUBLIC liba libmycuda)
