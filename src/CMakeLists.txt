AUTO_FILES("." "src" "\\.(cpp|h)$")
include_directories(${COMMON_INCLUDE_DIR})
link_directories(${COMMON_LIBRARY_DIR})
if(WIN32)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
endif()
ADD_EXE(3dstool "${src}")
if(WIN32)
  target_link_libraries(3dstool libeay32)
else()
  target_link_libraries(3dstool crypto)
  if(APPLE OR CYGWIN)
    target_link_libraries(3dstool iconv)
  endif()
endif()
install(TARGETS 3dstool DESTINATION bin)
