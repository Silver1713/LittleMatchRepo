# Generate core library targets that is going to be linked to all libraries

# find folders in CoreComponents
file(GLOB CORE_LIB_DIR ${CMAKE_SOURCE_DIR}/CoreComponents/Sage*/)

# Loop through all the folders in CoreComponents
foreach(CORE_LIB_SUBDIR ${CORE_LIB_DIR})
    # get the name of the folder
    file(GLOB_RECURSE CORE_LIP_TOP_SRC 
    ${CORE_LIB_SUBDIR}/src/*.[ch]pp
    ${CORE_LIB_SUBDIR}/src/*.h
    ${CORE_LIB_SUBDIR}/src/*.hpp
    )

    file(GLOB_RECURSE CORE_LIP_TOP_HEADER 
    ${CORE_LIB_SUBDIR}/include/*.[h]pp
    ${CORE_LIB_SUBDIR}/include/*.h)
    get_filename_component(CORE_LIB_NAME ${CORE_LIB_SUBDIR} NAME)

    # foreach folders in include
    file(GLOB CORE_LIB_INCLUDES_FDR ${CORE_LIB_SUBDIR}/include/*/)

    foreach(CORE_LIB_INCLUDES ${CORE_LIB_INCLUDES_FDR})
        get_filename_component(CORE_LIB_INCLUDES_NAME ${CORE_LIB_INCLUDES} NAME)
        file(GLOB CORE_LIB_INCLUDES_FILES ${CORE_LIB_INCLUDES}/*.[h]pp)
        source_group("Header Files/${CORE_LIB_INCLUDES_NAME}" FILES ${CORE_LIB_INCLUDES_FILES})
    endforeach()

    # foreach folders in src
    file(GLOB CORE_LIB_SRC_FDR ${CORE_LIB_SUBDIR}/src/*/)

    foreach(CORE_LIB_SRC ${CORE_LIB_SRC_FDR})
        get_filename_component(CORE_LIB_SRC_NAME ${CORE_LIB_SRC} NAME)
        file(GLOB CORE_LIB_SRC_FILES 
        ${CORE_LIB_SRC}/*.[ch]pp
        ${CORE_LIB_SRC}/*.h
        
        )


        source_group("Source Files/${CORE_LIB_SRC_NAME}" FILES ${CORE_LIB_SRC_FILES})
    endforeach()

   
    if(CORE_LIB_NAME STREQUAL "SageLogic")
    message(STATUS "Behaviour Directory: ${BEHAVIOUR_DIR}")

    set(SAGE_LOGIC_SCRIPTS)

    if(EXISTS "${BEHAVIOUR_DIR}")
        message(STATUS "Behaviour Directory Exists")
        file(GLOB_RECURSE SAGE_LOGIC_SCRIPTS
            ${BEHAVIOUR_DIR}/scripts/*.cs
        )
        source_group("C# Scripts" FILES ${SAGE_LOGIC_SCRIPTS})

        add_subdirectory(${BEHAVIOUR_DIR})
    endif()
endif()
    # add the program
    IF (NOT IS_LIBS_ONLY)
    add_executable(
        ${CORE_LIB_NAME}
        ${CORE_LIB_SRC_FILES}
        ${CORE_LIB_INCLUDES_FILES}
        ${CORE_LIP_TOP_SRC}
        ${CORE_LIP_TOP_HEADER}
        ${SAGE_LOGIC_SCRIPTS}
    )
    ENDIF()

    # remove the main.cpp file
    list(REMOVE_ITEM CORE_LIB_SRC_FILES ${CORE_LIB_SRC}/main.cpp)

    add_library(
        ${CORE_LIB_NAME}_lib
        STATIC
        ${CORE_LIB_SRC_FILES}
        ${CORE_LIB_INCLUDES_FILES}
        ${CORE_LIP_TOP_SRC}
        ${CORE_LIP_TOP_HEADER}
        
    )

    # include directories
    target_include_directories(
        ${CORE_LIB_NAME}_lib
        PUBLIC
        ${CORE_LIB_INCLUDES_FDR}
        PUBLIC
        ${CORE_LIB_SUBDIR}/include/
    )
    IF (NOT IS_LIBS_ONLY)
    target_include_directories(
        ${CORE_LIB_NAME}
        PUBLIC
        ${CORE_LIB_INCLUDES_FDR}
        PUBLIC
        ${CORE_LIB_SUBDIR}/include/
    )
    ENDIF()

    # clear  logics
    set(SAGE_LOGIC_SCRIPTS)

    

    IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
       IF (NOT IS_LIBS_ONLY)
        target_compile_options(${CORE_LIB_NAME} PRIVATE -Wall ${DisableWarnings})
        ENDIF()
        target_compile_options(${CORE_LIB_NAME}_lib PRIVATE -Wall ${DisableWarnings})
    elseif(MSVC)
    IF (NOT IS_LIBS_ONLY)
        target_compile_options(${CORE_LIB_NAME} PRIVATE /W4 /WX-)
    ENDIF()
        target_compile_options(${CORE_LIB_NAME}_lib PRIVATE /W4 /WX-)
    endif()
    IF (NOT IS_LIBS_ONLY)
    target_link_libraries(
        ${CORE_LIB_NAME}

        PRIVATE ${CORE_LIB_NAME}_lib
        ${ALL_LIBS}
    )
    ENDIF()

    target_link_libraries(
        ${CORE_LIB_NAME}_lib
        ${ALL_LIBS}
    )

    if(WIN32 AND MONO_IMPORT_SUCCESS)
    add_custom_command(TARGET ${CORE_LIB_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "$<$<CONFIG:Debug>:${MONO_DLL_PATH}>$<$<NOT:$<CONFIG:Debug>>:${MONO_DLL_PATH}>" 
            "$<TARGET_FILE_DIR:${CORE_LIB_NAME}>"
    )
    add_custom_command(TARGET ${CORE_LIB_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "${MONO_DLL_POSIX}" 
            "$<TARGET_FILE_DIR:${CORE_LIB_NAME}>"
    )
endif()

    set_property(TARGET ${CORE_LIB_NAME}_lib PROPERTY CXX_STANDARD 20)
    IF (NOT IS_LIBS_ONLY)
    set_property(TARGET ${CORE_LIB_NAME} PROPERTY CXX_STANDARD 20)
    ENDIF()
    # append to the list of all libraries
    list(APPEND ALL_LIBS ${CORE_LIB_NAME}_lib)
endforeach()