cmake_minimum_required(VERSION 3.12.1 FATAL_ERROR)


##############################################
#Project 

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
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SoulEditor)

set(ENGINE_REPOSITORY_PATH "" CACHE STRING "If set, the editor will not pull the default engine. This should be set if you are developing an engine at the same time." )


##############################################
#Sources

file(GLOB_RECURSE PROJECT_HEADERS *.h)
file(GLOB_RECURSE PROJECT_SOURCES *.cpp)
set (PROJECT_FILES 
    ${PROJECT_HEADERS} 
    ${PROJECT_SOURCES} 
)


##############################################
#Dependencies

if (ENGINE_REPOSITORY_PATH STREQUAL "")

    #TODO Pull Conan package for default Engine
    message( SEND_ERROR "`ENGINE_REPOSITORY_PATH` is not set. Default engine package is not implemented yet. See issue #_" )
    include(${CMAKE_CURRENT_SOURCE_DIR}/Build/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)

else()

    add_subdirectory(${ENGINE_REPOSITORY_PATH} ${ENGINE_REPOSITORY_PATH}/Build)

    endif()

##############################################
#Targets

add_executable(SoulEditor ${PROJECT_FILES})

set_target_properties(SoulEditor 
    PROPERTIES 
        LINKER_LANGUAGE CXX
        CXX_EXTENSIONS OFF  
        CXX_STANDARD 17
)

target_include_directories(SoulEditor
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
)

target_link_libraries(SoulEditor
    PUBLIC

    PRIVATE
        SoulEngine
)