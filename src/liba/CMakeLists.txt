set(TARGET_NAME liba)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/liba.cpp)


if(BUILD_SHARED_LIBS)
  add_library(${TARGET_NAME} SHARED ${TARGET_SOURCES})
else()
  add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES})
endif()

find_package(fmt REQUIRED)

target_link_libraries(${TARGET_NAME} PRIVATE project_options project_warnings fmt::fmt)

if(BUILD_TESTING)
  list(APPEND TEST_CASES
    hellolib_test
  )
  foreach(TEST_CASE ${TEST_CASES})
    add_executable(${TEST_CASE} ${CMAKE_CURRENT_SOURCE_DIR}/test/${TEST_CASE}.cpp)
    target_link_libraries(${TEST_CASE} PRIVATE ${TARGET_NAME} doctest::doctest)
    target_compile_options(${TEST_CASE} PRIVATE ${compiler_options})
    target_compile_definitions(${TEST_CASE} PRIVATE ${compiler_definitions} $<$<BOOL:${OPENSSL_FOUND}>:WITH_OPENSSL>)
    target_link_options(${TEST_CASE} PRIVATE ${linker_flags})

    target_include_directories(${TEST_CASE}
      PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
      PRIVATE 
        ${TARGET_INCLUDE_FOLDER}
        # Any other extra include required
    )

    add_test(NAME ${TEST_CASE} COMMAND ${TEST_CASE})
  endforeach(TEST_CASE ${TEST_CASES})
endif()
