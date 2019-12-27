cmake_minimum_required(VERSION 3.00)

project(buckey-service-library
	VERSION 0.1
	LANGUAGES CXX)

#Pretty sure that dbus-cxx-1.0 requires C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INSTALL_PREFIX /usr)
include(GNUInstallDirs)

add_library(buckey-service SHARED Service.cpp ServiceAdapter.cpp ServiceProxy.cpp)

set_target_properties(buckey-service PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER Service.h ServiceProxy.h ServiceAdapter.h)

configure_file(config.h.in config.h)
configure_file(buckey-service.pc.in buckey-service.pc @ONLY)

target_include_directories(buckey-service PUBLIC "${PROJECT_BINARY_DIR}")

#We're gonna use pkg-config to include all of our libraries
include(FindPkgConfig)
pkg_check_modules(DBUSCXX REQUIRED dbus-cxx-1.0)
target_include_directories(buckey-service PUBLIC "${DBUSCXX_INCLUDE_DIRS}")
target_link_libraries(buckey-service PUBLIC "${DBUSCXX_LDFLAGS}")

install(TARGETS buckey-service
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/buckey
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/buckey)

install(FILES ${CMAKE_BINARY_DIR}/buckey-service.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
