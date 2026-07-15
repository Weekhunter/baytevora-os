cmake_minimum_required(VERSION 3.16)

project(Baytevora_ISO_Generator
    VERSION 0.1.0
    DESCRIPTION "Baytevora OS ISO Generation (BIG) - Milestone H"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

set(SOURCES
    src/main.cpp
    src/ISOBuilder.cpp
    src/ImageManifest.cpp
    src/BuildConfiguration.cpp
    src/ISOConfiguration.cpp
    src/BuildLogger.cpp
)

set(HEADERS
    include/big/ISOBuilder.h
    include/big/ImageManifest.h
    include/big/BuildConfiguration.h
    include/big/ISOConfiguration.h
    include/big/BuildLogger.h
)

qt_add_executable(Baytevora_ISO_Generator
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(Baytevora_ISO_Generator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Baytevora_ISO_Generator PRIVATE
    Qt6::Core
)
