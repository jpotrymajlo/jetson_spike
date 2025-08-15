if(BUILD_TESTING)
  enable_testing()
endif()

add_subdirectory(liba)
add_subdirectory(libmycuda)
add_subdirectory(main)

