cmake_minimum_required(VERSION 3.00)

project(buckey-tts-library
	VERSION 0.1
	LANGUAGES CXX)

#Pretty sure that dbus-cxx-1.0 requires C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INSTALL_PREFIX /usr)
include(GNUInstallDirs)

add_library(buckey-tts SHARED Service.cpp ServiceAdapter.cpp ServiceProxy.cpp)

set_target_properties(buckey-tts PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1)

configure_file(config.h.in config.h)
configure_file(buckey-tts.pc.in buckey-tts.pc @ONLY)

target_include_directories(buckey-tts PUBLIC "${PROJECT_BINARY_DIR}")

#We're gonna use pkg-config to include all of our libraries
include(FindPkgConfig)
pkg_check_modules(DBUSCXX REQUIRED dbus-cxx-1.0)
target_include_directories(buckey-tts PUBLIC "${DBUSCXX_INCLUDE_DIRS}")
target_link_libraries(buckey-tts PUBLIC "${DBUSCXX_LDFLAGS}")

install(TARGETS buckey-tts
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES Service.h ServiceAdapter.h ServiceProxy.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/buckey)

install(FILES ${CMAKE_BINARY_DIR}/buckey-tts.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
