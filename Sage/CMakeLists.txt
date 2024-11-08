cmake_minimum_required(VERSION 2.8...3.13)

project(Sage)
set(IS_LIBS_ONLY OFF)
add_definitions(-DGLEW_STATIC)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(ImportDependencies)

# All libraries - GLFW, glew , include libraries here for ALL
set(ALL_LIBS
    PRIVATE glfw
    PRIVATE libglew_static
    PRIVATE soil
)

importDependencies()
include(GenerateCoreComponents)
 # message(STATUS "All Libraries: ${ALL_LIBS}")
option(GENERATE_ENGINE_CORE "Generate Engine Core" ON)
option(COMPILE_USING_OBJECT "Compile using object" ON)

file(GLOB PROJECT_DIRECTORIES ${CMAKE_SOURCE_DIR}/Sage*/)
message(STATUS "Project Directories: ${PROJECT_DIRECTORIES}")
set(LIB_LIST)
set(INCLUDES_LIST)
set(OBJECT_LIST)

foreach(dir ${PROJECT_DIRECTORIES})
    set(ADDITION_INCLUDE)
    string(REGEX REPLACE "/$" "" dir ${dir})
    get_filename_component(DIR_NAME ${dir} NAME)
    set(INERNAL_H_FILE_NAME "Internal Header Files")

    if(IS_DIRECTORY ${dir} AND NOT DIR_NAME STREQUAL "SageEngine" AND NOT DIR_NAME STREQUAL "Sage" AND NOT DIR_NAME STREQUAL "SageInputUnit" AND NOT IS_LIBS_ONLY)
        set(SAGE_SHADER_FILES)

        if(DIR_NAME STREQUAL "SageGraphics")
            file(GLOB_RECURSE SAGE_SHADER_FILES
                ${dir}/shaders/*.glsl
            )
            source_group("Shader Files" FILES ${SAGE_SHADER_FILES})
        endif()

        if(DIR_NAME STREQUAL "SageLogic")
            set(SAGE_LOGIC_SCRIPTS)
            file(GLOB_RECURSE SAGE_LOGIC_SCRIPTS
                ${dir}/scripts/*.cs
            )
            source_group("C# Scripts" FILES ${SAGE_LOGIC_SCRIPTS})
        endif()

        file(GLOB_RECURSE SAGE_SOURCE_FILE
            ${dir}/src/*.[ch]pp
            ${dir}/src/*/*.[ch]pp
            ${dir}/include/*.[h]pp
            ${dir}/include/*.h
        )
        file(GLOB_RECURSE SAGE_INTERNALS_H_FILES
            ${dir}/include/internal/*.h
            ${dir}/include/internal/*.hpp
        )

        source_group("Internal Header Files" FILES ${SAGE_INTERNALS_H_FILES})
        file(GLOB PROJECT_SUBDIRECTORIES_SRC ${dir}/src/*/)

        foreach(subdirsrc ${PROJECT_SUBDIRECTORIES_SRC})
            set(SUB_NAMESRC)

            if(IS_DIRECTORY ${subdirsrc})
                get_filename_component(SUB_NAMESRC ${subdirsrc} NAME)
                FILE(GLOB_RECURSE DIR_SRC_FILE
                    ${subdirsrc}/*.[ch]pp
                    ${subdirsrc}/*.h
                    ${subdirsrc}/*.hpp
                )

                source_group("Source Files/${SUB_NAMESRC}" FILES ${DIR_SRC_FILE})
                message(STATUS "Sourced Source Files/${SUB_NAME_LIB}")
            endif()
        endforeach()

        file(GLOB PROJECT_SUBDIRECTORIES_HEADER ${dir}/include/*/)

        foreach(subdirh ${PROJECT_SUBDIRECTORIES_HEADER})
            set(SUB_NAME)
            get_filename_component(SUB_NAME ${subdirh} NAME)

            if(IS_DIRECTORY ${subdirh} AND NOT SUB_NAME STREQUAL "internal")
                FILE(GLOB_RECURSE DIR_H_FILE
                    ${subdirh}/*.h
                    ${subdirh}/*.hpp
                )
                source_group("Header Files/${SUB_NAME}" FILES ${DIR_H_FILE})
                message(STATUS"Header Files/${SUB_NAME}")
                list(APPEND ADDITION_INCLUDE ${subdirh})
            endif()
        endforeach()

        add_executable(
            ${DIR_NAME}
            ${SAGE_SOURCE_FILE}
            ${SAGE_INTERNALS_H_FILES}
            ${SAGE_SHADER_FILES}
            ${SAGE_LOGIC_SCRIPTS})
        set(SAGE_SHADER_FILES "")
        set(SAGE_LOGIC_SCRIPTS "")
        target_link_libraries(${DIR_NAME} ${ALL_LIBS})
        set_property(TARGET ${DIR_NAME} PROPERTY CXX_STANDARD 20)

        if(WIN32 AND FMOD_IMPORT_SUCCESS)
        add_custom_command(TARGET ${DIR_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                "$<$<CONFIG:Debug>:${FMOD_LIB_DIR}/fmodL.dll>$<$<NOT:$<CONFIG:Debug>>:${FMOD_LIB_DIR}/fmod.dll>" 
                "$<TARGET_FILE_DIR:${DIR_NAME}>"
        )
    endif()
    

    if(WIN32 AND MONO_IMPORT_SUCCESS)
    add_custom_command(TARGET ${DIR_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "$<$<CONFIG:Debug>:${MONO_DLL_PATH}>$<$<NOT:$<CONFIG:Debug>>:${MONO_DLL_PATH}>" 
            "$<TARGET_FILE_DIR:${DIR_NAME}>"
    )
    add_custom_command(TARGET ${DIR_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "${MONO_DLL_POSIX}" 
            "$<TARGET_FILE_DIR:${DIR_NAME}>"
    )
endif()



        IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${DIR_NAME} PRIVATE -Wall ${DisableWarnings})
        elseif(MSVC)
            target_compile_options(${DIR_NAME} PRIVATE /W4 /WX-)
        endif()

        target_include_directories(${DIR_NAME} PRIVATE
            ${dir}/include
            ${dir}/include/internal
            ${ADDITION_INCLUDE})
        list(APPEND INCLUDES_LIST ${dir}/include ${ADDITION_INCLUDE})
    endif()

    if(IS_DIRECTORY ${dir} AND NOT DIR_NAME STREQUAL "SageEngine" AND NOT DIR_NAME STREQUAL "Sage" AND NOT DIR_NAME STREQUAL "SageInputUnit")
        file(GLOB_RECURSE SAGE_SOURCE_FILE
            ${dir}/src/*.[ch]pp
            ${dir}/src/*/*.[ch]pp
            ${dir}/include/*.[h]pp
            ${dir}/include/*.h
        )
        file(GLOB_RECURSE SAGE_INTERNALS_H_FILES
            ${dir}/include/internal/*.h
            ${dir}/include/internal/*.hpp
        )

        list(REMOVE_ITEM SAGE_SOURCE_FILE ${dir}/src/main.cpp)

        source_group("Internal Header Files" FILES ${SAGE_INTERNALS_H_FILES})

        IF(COMPILE_USING_OBJECT)
            add_library(${DIR_NAME}_lib OBJECT
                ${SAGE_SOURCE_FILE}
                ${SAGE_INTERNALS_H_FILES}
            )
        ELSE()
            message(STATUS "Adding Library : ${DIR_NAME}_lib")
            add_library(${DIR_NAME}_lib
                STATIC
                ${SAGE_SOURCE_FILE}
                ${SAGE_INTERNALS_H_FILES}
            )
        ENDIF()

        target_link_libraries(${DIR_NAME}_lib ${ALL_LIBS})
        set_property(TARGET ${DIR_NAME}_lib PROPERTY CXX_STANDARD 20)

        IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${DIR_NAME}_lib PRIVATE -Wall ${DisableWarnings})
        elseif(MSVC)
            target_compile_options(${DIR_NAME}_lib PRIVATE /W4 /WX-)
        endif()

        file(GLOB PROJECT_LIB_SUBDIRECTORIES_HEADER ${dir}/include/*/)

        FOREACH(SUB_DIR_LIB ${PROJECT_LIB_SUBDIRECTORIES_HEADER})
            set(SUB_NAME_LIB)
            get_filename_component(SUB_NAME_LIB ${SUB_DIR_LIB} NAME)

            IF(IS_DIRECTORY ${SUB_DIR_LIB} AND NOT SUB_NAME_LIB STREQUAL "internal")
                FILE(GLOB_RECURSE DIR_H_FILE_LIB
                    ${SUB_DIR_LIB}/*.h
                    ${SUB_DIR_LIB}/*.hpp
                )
                source_group("Header Files/${SUB_NAME_LIB}" FILES ${DIR_H_FILE_LIB})
                message(STATUS "Sourced Header Files/${SUB_NAME_LIB}")
                target_include_directories(${DIR_NAME}_lib PUBLIC
                    ${SUB_DIR_LIB}
                )
                IF (IS_LIBS_ONLY)
                    list(APPEND ADDITION_INCLUDE ${SUB_DIR_LIB})
                ENDIF()
            ENDIF()
        ENDFOREACH()

        target_include_directories(${DIR_NAME}_lib PUBLIC
            ${dir}/include
        )
        target_include_directories(${DIR_NAME}_lib
            PRIVATE ${dir}/include/internal
        )
        
        IF (IS_LIBS_ONLY)
        list(APPEND INCLUDES_LIST ${dir}/include ${ADDITION_INCLUDE})
        ENDIF()
        list(APPEND LIB_LIST "${DIR_NAME}_lib")
        list(APPEND OBJECT_LIST "$<TARGET_OBJECTS:${DIR_NAME}_lib>")
    endif()
endforeach()

#  message("List of Libraries: ${LIB_LIST}")

# Generate Core Libraries and Engine
IF(GENERATE_ENGINE_CORE)
    include(GenerateCore)
ENDIF()

include(UnitTest)

if(${IS_UNIT_TEST_ENABLED})
    enable_testing()
endif()
