cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)


##############################################
#Project 

project(SoulEditor
	VERSION 0.0.1
	DESCRIPTION "Soul Engine editor and project interface."
	LANGUAGES CXX
)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  )


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

#Conan via CMake
include(${CMAKE_SOURCE_DIR}/Tools/Conan/conan.cmake)

conan_cmake_run(CONANFILE ${CMAKE_SOURCE_DIR}/Tools/Conan/conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

add_subdirectory(${CONAN_USER_SOULENGINE_ENGINE_PATH})

##############################################
#Targets

add_executable(SoulEditor ${PROJECT_FILES})

set_target_properties(SoulEditor 
    PROPERTIES 
        LINKER_LANGUAGE CXX
        CXX_EXTENSIONS OFF  
        CXX_STANDARD 17
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Build"
)

target_link_libraries(SoulEditor
    PUBLIC
		CONAN_PKG::SoulEngine
)