set(TARGET_NAME liblwp)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/HubClient.cpp)


add_library(${TARGET_NAME} ${TARGET_SOURCES})

find_package(simplebluez REQUIRED)
find_package(DBus1 REQUIRED)
find_package(fmt REQUIRED)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(${TARGET_NAME}
	PRIVATE 
	    project_options
	    project_warnings
	PUBLIC
	    simplebluez::simplebluez
            dbus-1
	    fmt::fmt
)

