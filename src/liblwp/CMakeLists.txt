set(TARGET_NAME liblwp)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/HubClient.cpp)


add_library(${TARGET_NAME} ${TARGET_SOURCES})

find_package(simpleble REQUIRED)
find_package(PkgConfig REQUIRED) 
pkg_check_modules(DBUS REQUIRED dbus-1) 

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(${TARGET_NAME}
	PRIVATE 
	    project_options
	    project_warnings
)

target_link_libraries(${TARGET_NAME}
	PUBLIC
	    simpleble::simpleble
	    ${DBUS_LIBRARIES}
)

