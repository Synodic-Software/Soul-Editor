cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)

#Set CMake tools location
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Tools/CMake)

#set prior to target definition
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


##############################################
#Project 

project(SoulEditor
	VERSION 0.0.1
	DESCRIPTION "Soul Engine editor and project interface."
	LANGUAGES CXX
)


##############################################
#Sources

#TODO: Get rid of the globs. More elegant solution needed.
file(GLOB_RECURSE PROJECT_HEADERS Source/*.h)
file(GLOB_RECURSE PROJECT_SOURCES Source/*.cpp)
set (PROJECT_FILES 
    ${PROJECT_HEADERS} 
    ${PROJECT_SOURCES} 
)

#Provides Visual Studio filter support
include(source_groups)
source_groups(${PROJECT_FILES})

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

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX
        CXX_EXTENSIONS OFF  
        CXX_STANDARD 17
		VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
		CONAN_PKG::SoulEngine
)

#TODO: Proper resource handling via Conan probably. No need to pass around all these janky files
add_custom_command( TARGET ${PROJECT_NAME} 
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory 
                    ${CONAN_USER_SOULENGINE_ENGINE_PATH}/Resources
                    ${CMAKE_BINARY_DIR}/Resources)