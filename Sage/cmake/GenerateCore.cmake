# Generate a core project that run on libs
option(IS_LIB_COMPILED_CORE_GEN "Compile Library and generate a core build target." ON)

if(IS_LIB_COMPILED_CORE_GEN)
    message(STATUS "Library Core Generation is enabled")

    IF(COMPILE_USING_OBJECT)
        add_library(SageEngine_Core STATIC
            ${OBJECT_LIST}
        )
        target_link_libraries(SageEngine_Core
            ${ALL_LIBS}
        )
        target_include_directories(SageEngine_Core INTERFACE
            ${INCLUDES_LIST}
        )

        set_property(TARGET SageEngine_Core PROPERTY CXX_STANDARD 20)

        IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(SageEngine_Core PRIVATE -Wall ${DisableWarnings})
        elseif(MSVC)
            target_compile_options(SageEngine_Core PRIVATE /W3 /WX-)
        endif()

        add_dependencies(SageEngine_Core
            ${LIB_LIST}
        )
    ELSE()
        add_library(SageEngine_Core INTERFACE)
        target_link_libraries(SageEngine_Core INTERFACE
            ${LIB_LIST}
        )
        target_include_directories(SageEngine_Core INTERFACE
            ${INCLUDES_LIST}
        )
    ENDIF()
endif()

# Link the executable with the necessary libraries
# file(GLOB_RECURSE SAGEINPUT_LIBSRC
# ${CMAKE_SOURCE_DIR}/SageInput/src/*.[ch]pp
# ${CMAKE_SOURCE_DIR}/SageInput/include/*.[h]pp
# ${CMAKE_SOURCE_DIR}/SageInput/include/*.h
# )
# list(REMOVE_ITEM SAGEINPUT_LIBSRC ${CMAKE_SOURCE_DIR}/SageInput/src/main.cpp)

# file(GLOB_RECURSE SAGE_LITE_H_LIB
# ${CMAKE_SOURCE_DIR}/SageLite/include/*.[h]pp
# ${CMAKE_SOURCE_DIR}/SageLite/include/*.h
# )
# list(REMOVE_ITEM SAGE_LITE_H_LIB ${CMAKE_SOURCE_DIR}/SageEngine/include/Main.h)

# file(GLOB_RECURSE SAGE_INPUT_H_LIB

# ${CMAKE_SOURCE_DIR}/SageInput/include/*.[h]pp
# ${CMAKE_SOURCE_DIR}/SageInput/include/*.h
# )

# list(REMOVE_ITEM SAGE_INPUT_H_LIB ${CMAKE_SOURCE_DIR}/SageInput/include/Main.h)

# file(GLOB_RECURSE SAGEINPUT_LIBSRC
# ${CMAKE_SOURCE_DIR}/SageLite/src/*.[ch]pp
# ${CMAKE_SOURCE_DIR}/SageLite/include/*.[h]pp
# ${CMAKE_SOURCE_DIR}/SageLite/include/*.h
# )
# list(REMOVE_ITEM SAGELITE_SRCLIB ${CMAKE_SOURCE_DIR}/SageLite/src/main.cpp)

# add_library(SageEngine_Core STATIC
# ${SAGELITE_SRCLIB}
# ${SAGEINPUT_LIBSRC}
# )

# target_include_directories(SageEngine_Core PUBLIC
# ${CMAKE_SOURCE_DIR}/SageLite/include
# ${CMAKE_SOURCE_DIR}/SageInput/include
# )

# target_include_directories(SageEngine_Core PRIVATE
# ${CMAKE_SOURCE_DIR}/SageEngine/include
# ${CMAKE_SOURCE_DIR}/SageEngine/include/internal
# ${CMAKE_SOURCE_DIR}/SageLite/include/internal
# ${CMAKE_SOURCE_DIR}/SageInput/include/internal
# )

# target_link_libraries(SageEngine_Core
# ${ALL_LIBS}
# )

# Set the C++ standard to 20

# Generate a core project that run on libs
file(GLOB_RECURSE SageEngine_source_files
    ${CMAKE_SOURCE_DIR}/SageEngine/src/*.[ch]pp
    ${CMAKE_SOURCE_DIR}/SageEngine/include/*.[h]pp
    ${CMAKE_SOURCE_DIR}/SageEngine/include/*.h
)

file(GLOB SAGEENGINE_INC_SUBDIR
    ${CMAKE_SOURCE_DIR}/SageEngine/include/*/
)

file(GLOB SAGEENGINE_SRC_SUBDIR
    ${CMAKE_SOURCE_DIR}/SageEngine/src/*/
)
set(ENGINE_SUB_INC_FILES)
foreach(SAGEENGINE_INC_SUBDIRS ${SAGEENGINE_INC_SUBDIR})
    get_filename_component(SAGEENGINE_INC_SUBDIR_NAME ${SAGEENGINE_INC_SUBDIRS} NAME)
    file(GLOB SAGEENGINE_INC_SUBDIR_FILES
        ${SAGEENGINE_INC_SUBDIRS}/*.[h]pp
    )
    source_group("Header Files/${SAGEENGINE_INC_SUBDIR_NAME}" FILES ${SAGEENGINE_INC_SUBDIR_FILES})

    list(APPEND ENGINE_SUB_INC_FILES ${SAGEENGINE_INC_SUBDIR_FILES})
endforeach()
set(ENGINE_SUB_SRC_FILES)
foreach(SAGEENGINE_SRC_SUBDIRS ${SAGEENGINE_SRC_SUBDIR})
    get_filename_component(SAGEENGINE_SRC_SUBDIR_NAME ${SAGEENGINE_SRC_SUBDIRS} NAME)
    file(GLOB SAGEENGINE_SRC_SUBDIR_FILES
        ${SAGEENGINE_SRC_SUBDIRS}/*.[ch]pp
        ${SAGEENGINE_SRC_SUBDIRS}/*.h
    )
    source_group("Source Files/${SAGEENGINE_SRC_SUBDIR_NAME}" FILES ${SAGEENGINE_SRC_SUBDIR_FILES})
    list(APPEND ENGINE_SUB_SRC_FILES ${SAGEENGINE_SRC_SUBDIR_FILES})
endforeach()


add_executable(SageEngine
    ${SageEngine_source_files}
    ${ENGINE_SUB_SRC_FILES}
)

# Link the executable with the necessary libraries
target_link_libraries(SageEngine
    ${ALL_LIBS}
    SageEngine_Core
)

set_property(TARGET SageEngine PROPERTY CXX_STANDARD 20)

IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(SageEngine PRIVATE -Wall ${DisableWarnings})
elseif(MSVC)
    target_compile_options(SageEngine PRIVATE /W3 /WX-)
endif()

if(WIN32 AND FMOD_IMPORT_SUCCESS)
            add_custom_command(TARGET SageEngine POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<$<CONFIG:Debug>:${FMOD_LIB_DIR}/fmodL.dll>$<$<NOT:$<CONFIG:Debug>>:${FMOD_LIB_DIR}/fmod.dll>"
                $<TARGET_FILE_DIR:SageEngine>)
        endif()

target_include_directories(SageEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/SageEngine/include
    ${CMAKE_SOURCE_DIR}/SageEngine/include/internal
    ${ENGINE_SUB_INC_FILES}
    ${INCLUDES_LIST}
)
