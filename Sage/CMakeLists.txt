cmake_minimum_required(VERSION 2.8...3.13)

project(Sage)

add_definitions(-DGLEW_STATIC)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(ImportDependencies)

importDependencies()

# All libraries - GLFW, glew , include libraries here for ALL
set(ALL_LIBS
    PRIVATE glfw
    PRIVATE libglew_static
    PRIVATE soil
)

option(GENERATE_ENGINE_CORE "Generate Engine Core" ON)
option(COMPILE_USING_OBJECT "Compile using object" ON)

file(GLOB PROJECT_DIRECTORIES ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Sage*/)
set(LIB_LIST)
set(INCLUDES_LIST)
set(OBJECT_LIST)

foreach(dir ${PROJECT_DIRECTORIES})
    string(REGEX REPLACE "/$" "" dir ${dir})
    get_filename_component(DIR_NAME ${dir} NAME)
   
    

    if(IS_DIRECTORY ${dir} AND NOT DIR_NAME STREQUAL "SageEngine" AND NOT DIR_NAME STREQUAL "Sage" AND NOT DIR_NAME STREQUAL "SageInputUnit")
        SET(SAGE_SHADER_FILES)
        if (${DIR_NAME} STREQUAL "SageGraphics")

        file(GLOB_RECURSE SAGE_SHADER_FILES
            ${dir}/shaders/*.glsl
        )

        source_group("Shaders File" FILES ${SAGE_SHADER_FILES})
        endif()
        file(GLOB_RECURSE SAGE_SOURCE_FILE
            ${dir}/src/*.[ch]pp
            ${dir}/include/*.[h]pp
            ${dir}/include/*.h
        )
        file(GLOB_RECURSE SAGE_INTERNALS_H_FILES
            ${dir}/include/internal/*.h
            ${dir}/include/internal/*.hpp
        )

        source_group("Internal Header Files" FILES ${SAGE_INTERNALS_H_FILES})
        add_executable(
            ${DIR_NAME}
            ${SAGE_SOURCE_FILE}
            ${SAGE_INTERNALS_H_FILES})

        target_link_libraries(${DIR_NAME} ${ALL_LIBS})
        set_property(TARGET ${DIR_NAME} PROPERTY CXX_STANDARD 20)

        IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${DIR_NAME} PRIVATE -Wall ${DisableWarnings})
        elseif(MSVC)
            target_compile_options(${DIR_NAME} PRIVATE /W3 /WX-)
        endif()

        target_include_directories(${DIR_NAME} PRIVATE
            ${dir}/include
            ${dir}/include/internal)
        list(APPEND INCLUDES_LIST ${dir}/include)
    endif()

    if(IS_DIRECTORY ${dir} AND NOT DIR_NAME STREQUAL "SageEngine" AND NOT DIR_NAME STREQUAL "Sage" AND NOT DIR_NAME STREQUAL "SageInputUnit")
        
        file(GLOB_RECURSE SAGE_SOURCE_FILE
            ${dir}/src/*.[ch]pp
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
            target_compile_options(${DIR_NAME}_lib PRIVATE /W3 /WX-)
        endif()
        
        target_include_directories(${DIR_NAME}_lib PUBLIC
            ${dir}/include
        )
        target_include_directories(${DIR_NAME}_lib PRIVATE
            ${dir}/include/internal)
        list(APPEND LIB_LIST "${DIR_NAME}_lib")
        list(APPEND OBJECT_LIST "$<TARGET_OBJECTS:${DIR_NAME}_lib>")
    endif()

    
endforeach()

message("List of Libraries: ${LIB_LIST}")
# Generate Core Libraries and Engine
IF(GENERATE_ENGINE_CORE)
    include(GenerateCore)
ENDIF()

include(UnitTest)

# Gather source files for the single executable
file(GLOB_RECURSE SageLite_source_files
    ${CMAKE_SOURCE_DIR}/SageGraphics/src/*.[c]pp
    ${CMAKE_SOURCE_DIR}/SageGraphics/include/*.h
    ${CMAKE_SOURCE_DIR}/SageGraphics/include/*.hpp
)

file(GLOB_RECURSE SageInput_source_files
    ${CMAKE_SOURCE_DIR}/SageInput/src/*.[ch]pp
    ${CMAKE_SOURCE_DIR}/SageInput/include/*.[h]
    ${CMAKE_SOURCE_DIR}/SageInput/include/*.[h]pp
)
file(GLOB_RECURSE INternal_SAGELITE_H_FILES
    ${CMAKE_SOURCE_DIR}/SageGraphics/include/internal/*.h
    ${CMAKE_SOURCE_DIR}/SageGraphics/include/internal/*.hpp
)

file(GLOB_RECURSE INternal_SAGEINPUT_H_FILES
    ${CMAKE_SOURCE_DIR}/SageInput/include/internal/*.h
    ${CMAKE_SOURCE_DIR}/SageInput/include/internal/*.hpp
)

# # Gather shader files
# file(GLOB_RECURSE SageLite_shaders_files
# ${CMAKE_SOURCE_DIR}/SageLite/shaders/*.glsl
# )

# source_group("Shaders File" FILES ${SageLite_shaders_files})
# source_group("Internal Header Files" FILES ${INternal_SAGELITE_H_FILES})

# source_group("Internal Header Files" FILES ${INternal_SAGEINPUT_H_FILES})

# # Create the executable
# add_executable(SageGraphicFramework
# ${SageLite_source_files}
# ${SageLite_shaders_files}
# ${INternal_SAGELITE_H_FILES}
# )

# add_executable(SageInput
# ${SageInput_source_files}
# ${INternal_SAGEINPUT_H_FILES}
# )

# # Link the executable with the necessary libraries
# target_link_libraries(SageGraphicFramework
# ${ALL_LIBS}
# )

# # same lib for input
# target_link_libraries(SageInput
# ${ALL_LIBS}
# )

# # Set the C++ standard
# set_property(TARGET SageGraphicFramework PROPERTY CXX_STANDARD 20)
# set_property(TARGET SageInput PROPERTY CXX_STANDARD 20)

# # Add compiler options based on the compiler
# IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
# target_compile_options(SageGraphicFramework PRIVATE -Wall ${DisableWarnings})
# target_compile_options(SageInput PRIVATE -Wall ${DisableWarnings})
# elseif(MSVC)
# target_compile_options(SageGraphicFramework PRIVATE /W3 /WX-)
# target_compile_options(SageInput PRIVATE /W3 /WX-)
# endif()

# # Include directories for the executable
# target_include_directories(SageGraphicFramework PRIVATE
# ${CMAKE_CURRENT_LIST_DIR}/SageLite/include
# ${CMAKE_CURRENT_LIST_DIR}/SageLite/include/internal)

# target_include_directories(SageInput PRIVATE
# ${CMAKE_CURRENT_LIST_DIR}/SageInput/include
# ${CMAKE_CURRENT_LIST_DIR}/SageInput/include/internal)
if(${IS_UNIT_TEST_ENABLED})
    enable_testing()
endif()
