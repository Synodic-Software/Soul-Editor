cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(Soul_Editor 
	VERSION 0.0.1
	DESCRIPTION "An editor for building Soul Engine applications."
	LANGUAGES CXX
)


##############################################
#Global Variables

set(EDITOR_SOURCE ${PROJECT_SOURCE_DIR}/Source)
set(EDITOR_BUILD ${PROJECT_SOURCE_DIR}/Build)

#set(CMAKE_SUPPRESS_REGENERATION true) #zero check is not needed/clutter
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


##############################################
# Create target and set properties


##############################################
#Main target properties

file(GLOB_RECURSE SourceFiles 
	LIST_DIRECTORIES false 
    ${EDITOR_SOURCE}/*.cpp)

file(GLOB_RECURSE IncludeFiles 
	LIST_DIRECTORIES false 
    ${EDITOR_SOURCE}/*.h)

file(GLOB EDITOR_All_SOURCES ${SourceFiles} ${IncludeFiles})

add_executable(SoulEditor ${EDITOR_All_SOURCES})
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SoulEditor)


#Visual filters for all source files
foreach(_source IN ITEMS ${EDITOR_All_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

#Visual filters for all frontend files
foreach(_source IN ITEMS ${EDITOR_INCLUDE})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()


set_property(TARGET SoulEditor PROPERTY CXX_STANDARD 17)
set_property(TARGET SoulEditor PROPERTY CXX_STANDARD_REQUIRED ON)

set_target_properties(SoulEditor 
	PROPERTIES 
		CXX_EXTENSIONS OFF	
		CUDA_SEPARABLE_COMPILATION ON
)

#Main target linking and stuff
target_include_directories(SoulEditor
    PUBLIC 
        
    PRIVATE
        ${EDITOR_SOURCE}
)

target_link_libraries(SoulEditor
    PUBLIC
    
    PRIVATE		
		
)


##############################################
# Unit Tests



##############################################
# Installation

#install(TARGETS SoulEngine
#    EXPORT SoulEngine-targets
#    LIBRARY DESTINATION ${SOUL_BUILD}
#    ARCHIVE DESTINATION ${SOUL_BUILD}
#)

#set_target_properties(SoulEngine PROPERTIES EXPORT_NAME SoulEngine)

#bring from 
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#install(EXPORT SoulEngine-targets
#	FILE
#		SoulEngineTargets.cmake
#	NAMESPACE
#		SoulEngine::
#	DESTINATION
#		${SOUL_BUILD}
#)


##############################################
# Exporting for others

#export(
#	EXPORT 
#		SoulEngine-targets 
#	FILE 
#		${SOUL_BUILD}/SoulEngineTargets.cmake 
#	NAMESPACE 
#		SoulEngine::
#)

#export(PACKAGE SoulEngine)