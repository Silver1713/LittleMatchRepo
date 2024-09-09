# Unit Test Generator - run after all build targets are executed
option(IS_UNIT_TEST_ENABLED "Generate Unit Test" ON)

if (IS_UNIT_TEST_ENABLED)
message(STATUS "Unit Test is enabled")
include(FetchContent)

# Import dependencies
macro(import_gtestframework)
    if (NOT TARGET gtest)
        FetchContent_Declare(
            gtest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG main
            SOURCE_DIR ${DEP_DIR}/googletest
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(gtest)
        include_directories(${gtest_SOURCE_DIR}/googletest/include)
    endif()
endmacro()

    macro(setup_SageInput_unit)
       

        file(GLOB_RECURSE SageInput_unit_sources_files 
        ${CMAKE_SOURCE_DIR}/SageInputUnit/src/*.[ch]pp
        ${CMAKE_SOURCE_DIR}/SageInputUnit/include/*.[ch]pp
        ${CMAKE_SOURCE_DIR}/SageInputUnit/include/*.h
        )

        # Create the executable
        add_executable(SageInput_unit
           ${SageInput_unit_sources_files}
        )
        # Link the executable with the necessary libraries
        target_link_libraries(SageInput_unit
            gtest
            gtest_main
            SageInput_lib
        )
        set_property(TARGET SageInput_unit PROPERTY CXX_STANDARD 20)
        IF (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(SageInput_unit PRIVATE -Wall ${DisableWarnings})
            
        elseif (MSVC)
            target_compile_options(SageInput_unit PRIVATE /W3 /WX-)
        endif()

        
        target_include_directories(SageInput_unit PRIVATE 
            ${CMAKE_SOURCE_DIR}/SageInputUnit/include
        )
        target_include_directories(SageInput_unit PRIVATE 
            ${CMAKE_SOURCE_DIR}/SageInput/include
            ${CMAKE_SOURCE_DIR}/SageInput/include/internal
        )
        
        # Let test project know about the lib (include)
        
        add_test(NAME SageInput_UnitTest COMMAND SageInput_unit)
        
    endmacro()
    import_gtestframework()
    setup_SageInput_unit()
endif()