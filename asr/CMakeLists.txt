cmake_minimum_required(VERSION 3.00)

project(buckey-asr-library
	VERSION 0.1
	LANGUAGES CXX)

#Pretty sure that dbus-cxx-1.0 requires C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INSTALL_PREFIX /usr)
include(GNUInstallDirs)

add_library(buckey-asr SHARED ASRServiceAdapter.cpp ASRServiceProxy.cpp)

set_target_properties(buckey-asr PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1)

configure_file(config.h.in config.h)
configure_file(buckey-asr.pc.in buckey-asr.pc @ONLY)

target_include_directories(buckey-asr PUBLIC "${PROJECT_BINARY_DIR}")

#We're gonna use pkg-config to include all of our libraries
include(FindPkgConfig)

pkg_check_modules(DBUSCXX REQUIRED dbus-cxx-1.0)
target_include_directories(buckey-asr PUBLIC "${DBUSCXX_INCLUDE_DIRS}")
target_link_libraries(buckey-asr PUBLIC "${DBUSCXX_LDFLAGS}")

pkg_check_modules(BS REQUIRED buckey-service)
target_include_directories(buckey-asr PUBLIC "${BS_INCLUDE_DIRS}")
target_link_libraries(buckey-asr PUBLIC "${BS_LDFLAGS}")

install(TARGETS buckey-asr
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES ASRService.h ASRServiceAdapter.h ASRServiceProxy.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/buckey)

install(FILES ${CMAKE_BINARY_DIR}/buckey-asr.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
