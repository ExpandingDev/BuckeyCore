cmake_minimum_required(VERSION 3.00)

project(buckey-core
	VERSION 0.1
	LANGUAGES CXX)

#Pretty sure that dbus-cxx-1.0 requires C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INSTALL_PREFIX /usr)

include(GNUInstallDirs)

add_library(buckey-uio SHARED uio/UIO.cpp)
add_library(buckey-service SHARED service/Service.cpp service/ServiceAdapter.cpp service/ServiceProxy.cpp)
add_library(buckey-tts SHARED tts/TTSServiceAdapter.cpp tts/TTSServiceProxy.cpp)
add_library(buckey-asr SHARED asr/ASRServiceAdapter.cpp asr/ASRServiceProxy.cpp)

set(UIO_VERSION 0.1)
set(SERVICE_VERSION 0.1)
set(TTS_VERSION 0.1)
set(ASR_VERSION 0.1)

set_target_properties(buckey-uio PROPERTIES
    VERSION ${UIO_VERSION}
    SOVERSION 1)

set_target_properties(buckey-service PROPERTIES
    VERSION ${SERVICE_VERSION}
    SOVERSION 1)

set_target_properties(buckey-tts PROPERTIES
    VERSION ${TTS_VERSION}
    SOVERSION 1)

set_target_properties(buckey-asr PROPERTIES
    VERSION ${ASR_VERSION}
    SOVERSION 1)

configure_file(uio/buckey-uio.pc.in buckey-uio.pc @ONLY)
configure_file(service/buckey-service.pc.in buckey-service.pc @ONLY)
configure_file(tts/buckey-tts.pc.in buckey-tts.pc @ONLY)
configure_file(asr/buckey-asr.pc.in buckey-asr.pc @ONLY)

target_include_directories(buckey-uio PUBLIC "${PROJECT_BINARY_DIR}")

#We're gonna use pkg-config to include all of our libraries
include(FindPkgConfig)
pkg_check_modules(DBUSCXX REQUIRED dbus-cxx-1.0)

target_include_directories(buckey-uio PUBLIC "${DBUSCXX_INCLUDE_DIRS}")
target_link_libraries(buckey-uio PUBLIC "${DBUSCXX_LDFLAGS}")

target_include_directories(buckey-service PUBLIC "${DBUSCXX_INCLUDE_DIRS}")
target_link_libraries(buckey-service PUBLIC "${DBUSCXX_LDFLAGS}")

target_include_directories(buckey-tts PUBLIC "${DBUSCXX_INCLUDE_DIRS}" "service/")
target_link_libraries(buckey-tts PUBLIC "${DBUSCXX_LDFLAGS}" buckey-service)

target_include_directories(buckey-asr PUBLIC "${DBUSCXX_INCLUDE_DIRS}"  "service/")
target_link_libraries(buckey-asr PUBLIC "${DBUSCXX_LDFLAGS}" buckey-service)

install(TARGETS buckey-uio buckey-service buckey-tts buckey-asr
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES uio/UIO.h tts/TTSService.h tts/TTSServiceAdapter.h tts/TTSServiceProxy.h asr/ASRService.h asr/ASRServiceAdapter.h asr/ASRServiceProxy.h service/Service.h service/ServiceAdapter.h service/ServiceProxy.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/buckey)

install(FILES buckey-uio.pc buckey-service.pc buckey-tts.pc buckey-asr.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
