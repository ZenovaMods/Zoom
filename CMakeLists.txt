cmake_minimum_required(VERSION 3.12)

set(ModName Zoom)
set(SourceDir source)
set(IncludeDir include)
set(generated_directory "${CMAKE_CURRENT_SOURCE_DIR}/${SourceDir}/generated")
set(maps_directory "${CMAKE_CURRENT_SOURCE_DIR}/maps")

set(CMAKE_ASM_NASM_OBJECT_FORMAT win64)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(${ModName} CXX ASM_NASM)

# temporary till configs are figured out
option(USE_ZOOM_ANIMATION "Use animation with zoom" OFF)
option(USE_JAVA_SMOOTH "Use Java\'s smoothing" OFF)
if (NOT ZOOM_USE_ANIMATION)
    add_compile_definitions(USE_OPTIFINE)
endif()
if (NOT USE_JAVA_SMOOTH)
    add_compile_definitions(PE_ALPHA_SMOOTH)
endif()

if(MSVC)
    set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "$ENV{ZENOVA_DATA}/mods/${ModName}")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "$ENV{ZENOVA_DATA}/mods/${ModName}")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "$ENV{ZENOVA_DATA}/mods/${ModName}")
    endforeach(OUTPUTCONFIG)
endif()

if(NOT EXISTS ${generated_directory})
    file(MAKE_DIRECTORY ${generated_directory})
    file(TOUCH "${generated_directory}/initasm.asm")
    file(TOUCH "${generated_directory}/initcpp.cpp")
    file(TOUCH "${generated_directory}/initcpp.h")
endif()

include_directories(
    "$ENV{ZENOVA_DATA}/dev/inc"
    "${IncludeDir}"
    "${SourceDir}"
)

file(GLOB_RECURSE INCLUDE_LIST
    "${IncludeDir}/*.hpp"
    "${IncludeDir}/*.h"
)

file(GLOB_RECURSE SRC_INCLUDE_LIST
    "${SourceDir}/*.hpp"
    "${SourceDir}/*.h"
)

file(GLOB_RECURSE SOURCE_LIST
    "${SourceDir}/*.cpp"
    "${SourceDir}/*.cxx"
    "${SourceDir}/*.cc"
    "${SourceDir}/*.asm"
)

add_library(${ModName} SHARED
    ${SRC_INCLUDE_LIST}
    ${INCLUDE_LIST}
    ${SOURCE_LIST}
)

target_link_libraries(${ModName} 
    $ENV{ZENOVA_DATA}/dev/lib/ZenovaAPI.lib
)

add_custom_command(
    OUTPUT "${generated_directory}/initcpp.cpp" "${generated_directory}/initasm.asm" "${generated_directory}/initcpp.h"
    COMMAND py -3 $ENV{ZENOVA_DATA}/dev/tools/process_symbol_map.py -e -a x64 -p windows -d ${generated_directory} ${maps_directory}/*.json
    DEPENDS $ENV{ZENOVA_DATA}/dev/tools/process_symbol_map.py ${maps_directory}/*.json
)

add_custom_command(TARGET ${ModName}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $ENV{ZENOVA_DATA}/mods/${ModName}
    COMMENT "Resources copied to $ENV{ZENOVA_DATA}/mods/${ModName}"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${IncludeDir} PREFIX "Header Files//" FILES ${INCLUDE_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${SourceDir} PREFIX "Header Files//" FILES ${SRC_INCLUDE_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${SourceDir} PREFIX "Source Files//" FILES ${SOURCE_LIST})