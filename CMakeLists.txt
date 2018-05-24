cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)


##############################################
#Options


option(BUILD_TESTS "Build tests." OFF)
set(SOUL_ROOT "N:/Projects/Soul Engine" CACHE STRING "The directory location of Soul Engine")
set(SOUL_BUILD "N:/Projects/Soul Engine/Build" CACHE STRING "The build location of Soul Engine")


##############################################
#Project 

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/Hunter/HunterGate.cmake)

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.21.6.tar.gz"
    SHA1 "19e74186aa97d8c3ebe799083cd5e97d87701552"
    FILEPATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Hunter/config.cmake
)

project(SoulEditor
	VERSION 0.0.1
	DESCRIPTION "Soul Engine editor and project interface."
	LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})


##############################################
#Sources


file(GLOB_RECURSE PROJECT_HEADERS Source/*.h Include/*.h)
file(GLOB_RECURSE PROJECT_SOURCES Source/*.cpp)
set (PROJECT_FILES 
    ${PROJECT_HEADERS} 
    ${PROJECT_SOURCES} 
)


include(source_groups)
source_groups(${PROJECT_FILES})


##############################################
#Dependencies


#find_package(SoulEngine REQUIRED)
add_subdirectory(${SOUL_ROOT} ${SOUL_BUILD})

##############################################
#Targets


add_executable(${PROJECT_NAME} ${PROJECT_FILES})

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX
        CXX_EXTENSIONS OFF  
        CXX_STANDARD 17
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
        Source
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC

    PRIVATE		
        Soul::SoulEngine
)


##############################################
#Tests


if(BUILD_TESTS)
 

endif()