cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)


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