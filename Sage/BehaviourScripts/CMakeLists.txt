enable_language(CSharp)


message(STATUS "SAGE_LOGIC_SCRIPTS = ${SAGE_LOGIC_SCRIPTS}")

source_group("..\\BehaviourScripts\\scripts" FILES ${SAGE_LOGIC_SCRIPTS})

set(CMAKE_CSharp_FLAGS "/langversion:latest")
set(CMAKE_CSharp_FLAGS "/platform:anycpu")
add_library(SageCSContainer 
    SHARED
    ${SAGE_LOGIC_SCRIPTS}
)

