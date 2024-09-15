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

    # add the program
    add_executable(
        ${CORE_LIB_NAME}
        ${CORE_LIB_SRC_FILES}
        ${CORE_LIB_INCLUDES_FILES}
        ${CORE_LIP_TOP_SRC}
        ${CORE_LIP_TOP_HEADER}
    )

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

    target_include_directories(
        ${CORE_LIB_NAME}
        PUBLIC
        ${CORE_LIB_INCLUDES_FDR}
        PUBLIC
        ${CORE_LIB_SUBDIR}/include/
    )

    IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${CORE_LIB_NAME} PRIVATE -Wall ${DisableWarnings})
        target_compile_options(${CORE_LIB_NAME}_lib PRIVATE -Wall ${DisableWarnings})
    elseif(MSVC)
        target_compile_options(${CORE_LIB_NAME} PRIVATE /W3 /WX-)
        target_compile_options(${CORE_LIB_NAME}_lib PRIVATE /W3 /WX-)
    endif()

    target_link_libraries(
        ${CORE_LIB_NAME}

        PRIVATE ${CORE_LIB_NAME}_lib
        ${ALL_LIBS}
    )

    target_link_libraries(
        ${CORE_LIB_NAME}_lib
        ${ALL_LIBS}
    )

    set_property(TARGET ${CORE_LIB_NAME}_lib PROPERTY CXX_STANDARD 20)
    set_property(TARGET ${CORE_LIB_NAME} PROPERTY CXX_STANDARD 20)

    # append to the list of all libraries
    list(APPEND ALL_LIBS ${CORE_LIB_NAME}_lib)
endforeach()