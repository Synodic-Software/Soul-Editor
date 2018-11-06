cmake_minimum_required(VERSION 3.11.1 FATAL_ERROR)


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
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

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


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Soul\ Engine ${CMAKE_CURRENT_SOURCE_DIR}/../../Soul\ Engine/Build)


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
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC

    PRIVATE
        synodic::SoulEngine
)