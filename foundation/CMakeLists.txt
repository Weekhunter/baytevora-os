cmake_minimum_required(VERSION 3.16)

project(Baytevora_Foundation
    VERSION 0.1.0
    DESCRIPTION "Baytevora Linux Distribution Foundation (BLDF) - Milestone H2"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

set(SOURCES
    src/main.cpp
    src/DebianBaseBuilder.cpp
    src/FilesystemConfigurator.cpp
    src/ComponentInstaller.cpp
    src/DisplayManagerConfigurator.cpp
    src/ApplicationRegistrar.cpp
    src/ServiceConfigurator.cpp
)

set(HEADERS
    include/bldf/DebianBaseBuilder.h
    include/bldf/FilesystemConfigurator.h
    include/bldf/ComponentInstaller.h
    include/bldf/DisplayManagerConfigurator.h
    include/bldf/ApplicationRegistrar.h
    include/bldf/ServiceConfigurator.h
)

qt_add_executable(Baytevora_Foundation
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(Baytevora_Foundation PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Baytevora_Foundation PRIVATE
    Qt6::Core
)
