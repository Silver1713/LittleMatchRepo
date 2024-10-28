enable_language(CSharp)
set(SCRIPT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SAGE_LOGIC_SCRIPTS)

file(GLOB SAGE_LOGIC_SCRIPTS "${SCRIPT_DIR}/scripts/*.cs")
message(STATUS "SAGE_LOGIC_SCRIPTS = ${SAGE_LOGIC_SCRIPTS}")

# source_group("scripts" FILES ${SAGE_LOGIC_SCRIPTS})
set(CMAKE_CSharp_FLAGS "/langversion:latest")
set(CMAKE_CSharp_FLAGS "/platform:anycpu")

foreach(script ${SAGE_LOGIC_SCRIPTS})
    # Make each file appear in the "Scripts" folder within Visual Studio
    get_filename_component(script_name ${script} NAME)
    source_group("Scripts" FILES ${script})
    set_source_files_properties(${script} PROPERTIES
        VS_LINK_FLAGS "/link:${SCRIPTS_DIR}/${script_name}"
    )
endforeach()

add_library(SageCSContainer
    SHARED
    ${SAGE_LOGIC_SCRIPTS}
)
set_target_properties(SageCSContainer PROPERTIES
    CSharp_PROJECT_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}" # Custom path for .csproj and intermediate files
)

# Allow the C# project to add script through visual studio
