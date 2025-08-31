set(TARGET_NAME mainapp)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(${TARGET_NAME} ${TARGET_SOURCES})


target_link_libraries(${TARGET_NAME} 
    PRIVATE 
	project_options
	project_warnings
    PUBLIC
        liblwp
	libmycuda
)

