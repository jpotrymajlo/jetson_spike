set(TARGET_NAME libmycuda)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/libmycuda.cu)

if(BUILD_SHARED_LIBS)
  add_library(${TARGET_NAME} SHARED ${TARGET_SOURCES})
else()
  add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES})
endif()

#target_link_libraries(${TARGET_NAME} PRIVATE project_options project_warnings)
#target_link_libraries(${TARGET_NAME} PUBLIC OpenSSL::SSL OpenSSL::Crypto)
set_target_properties(${TARGET_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

