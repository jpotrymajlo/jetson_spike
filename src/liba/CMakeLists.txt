set(TARGET_NAME liba)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/liba.cpp)


add_library(${TARGET_NAME} SHARED ${TARGET_SOURCES})

find_package(fmt REQUIRED)

target_link_libraries(${TARGET_NAME} 
	PRIVATE 
	    project_options
	    project_warnings
)

