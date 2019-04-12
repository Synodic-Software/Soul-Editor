cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)

#Set CMake tools location
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Tools/CMake)


##############################################
#Project 

project(SoulEditor
	VERSION 0.0.1
	DESCRIPTION "Soul Engine editor and project interface."
	LANGUAGES CXX
)


##############################################
#Dependencies

#TODO: Pull Engine from Conan remote and use that as a dependancy if an editable package is not found
#Conan via CMake
include(${CMAKE_SOURCE_DIR}/Tools/Conan/conan.cmake)

conan_cmake_run(CONANFILE Tools/Conan/conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

#TODO: replace with Conan workspaces
#Engine path
add_subdirectory(${CONAN_USER_SOULENGINE_ENGINE_PATH} ${CONAN_USER_SOULENGINE_ENGINE_PATH}/Build)


##############################################
#Targets

add_executable(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX
        CXX_EXTENSIONS OFF  
        CXX_STANDARD 17
        USE_FOLDERS ON
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
		CONAN_PKG::SoulEngine
)

##############################################
#Sources

target_sources(${PROJECT_NAME}
    PRIVATE
        Source/Editor.cpp
        Source/Editor.h
)

#Provides Visual Studio filter support
get_target_property(PROJECT_SOURCES ${PROJECT_NAME} SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})


##############################################
#Installation

#TODO: Proper resource handling via Conan probably. No need to pass around all these janky files
add_custom_command( TARGET ${PROJECT_NAME} 
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory 
                    ${CONAN_USER_SOULENGINE_ENGINE_PATH}/Resources
                    ${CMAKE_BINARY_DIR}/Resources)