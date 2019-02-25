cmake_minimum_required(VERSION 2.8)

set(USE_QT5 1)
if(USE_QT5)
    if(POLICY CMP0020)
        cmake_policy(SET CMP0020 NEW) # remove if CMake >= 2.8.11 required
    endif()
    if(POLICY CMP0043) # compatibility with CMake 3.0.1
        cmake_policy(SET CMP0043 OLD)
    endif()
    if(POLICY CMP0071) # compatibility with CMake 3.10.0
        cmake_policy(SET CMP0071 OLD)
    endif()
endif()
set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(libs)


if (USE_QT5)
    add_definitions(-D QT5)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    find_package(Qt5Core REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Network REQUIRED)
    set(QT_LIBRARIES "")
    macro(qt4_wrap_cpp VARNAME)
        set(${VARNAME} "")
    endmacro()
    # wrap functions
    macro(qt4_wrap_ui)
        qt5_wrap_ui(${ARGN})
    endmacro()
    macro(qt4_add_resources)
        qt5_add_resources(${ARGN})
    endmacro()
else()
    set(QT_USE_QTNETWORK true)
    find_package(Qt4 REQUIRED)
    include(${QT_USE_FILE})
endif()
list(APPEND libs ${QT_LIBRARIES})

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
list(APPEND libs ${PROTOBUF_LIBRARIES})

protobuf_generate_cpp(PROTO_CPP PROTO_H
    ../../src/proto/grSim_Replacement.proto
    ../../src/proto/grSim_Commands.proto
    ../../src/proto/grSim_Packet.proto
)

set(app client)

add_executable(${app} MACOSX_BUNDLE
    ${PROTO_CPP}
    ${PROTO_H}
    main.cpp
    mainwindow.cpp
    mainwindow.h
)
if(USE_QT5)
    target_link_libraries(${app} ${libs} Qt5::Core Qt5::Widgets Qt5::Network)
else()
    target_link_libraries(${app} ${libs} )
endif()

