include(FetchContent)
set(DEP_DIR "${CMAKE_BINARY_DIR}/lib/")

# Macro to import tinyobjloader
macro(import_tinyobjloader)
    if(NOT TARGET tinyobjloader) # Guard to prevent multiple inclusion
        FetchContent_Declare(
            tinyobjloader
            GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
            GIT_TAG release
            SOURCE_DIR ${DEP_DIR}/tinyobjloader
        )
        FetchContent_MakeAvailable(tinyobjloader)

        # include_directories(${tinyobjloader_SOURCE_DIR})
    endif()
endmacro()

macro(import_lodepng)
    if(NOT TARGET lodepng)
        FetchContent_Declare(
            lodepng
            GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/lodepng
        )
        FetchContent_MakeAvailable(lodepng)
        include_directories(${lodepng_SOURCE_DIR})
    endif()
endmacro()

macro(import_glm)
    if(NOT TARGET glm)
        FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/glm
        )
        FetchContent_MakeAvailable(glm)
        include_directories(${glm_SOURCE_DIR})
    endif()
endmacro()

macro(import_glew)
    if(NOT TARGET glew_s)
        FetchContent_Declare(
            glew_s
            GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/glew
        )
        FetchContent_MakeAvailable(glew_s)
        include_directories(${glew_s_SOURCE_DIR}/include)
    endif()
endmacro()

macro(import_glfw)
    if(NOT TARGET glfw)
        FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/glfw
        )

        FetchContent_MakeAvailable(glfw)
        include_directories(${glfw_SOURCE_DIR}/include)
    endif()
endmacro()

macro(import_fmod)
    if(NOT TARGET fmod)
        FetchContent_Declare(
            fmod
            GIT_REPOSITORY https://github.com/rosshoyt/FMOD-Audio-Engine
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/fmod
        )
        FetchContent_MakeAvailable(fmod)
        include_directories(${fmod_SOURCE_DIR}/Include)
    endif()
endmacro()

macro(import_soil)
    if(NOT TARGET soil)
        FetchContent_Declare(
            soil
            GIT_REPOSITORY https://github.com/paralin/soil
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/soil
        )
        FetchContent_MakeAvailable(soil)
        include_directories(${soil_SOURCE_DIR}/inc/SOIL)
    endif()
endmacro()

macro(import_stb)
    if(NOT TARGET stb)
        FetchContent_Declare(
            stb
            GIT_REPOSITORY https://github.com/nothings/stb.git
            GIT_TAG master 
        )
        FetchContent_MakeAvailable(stb)
        add_library(stb INTERFACE)
        target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
        add_deps_all_targets(PUBLIC stb)
    endif()
endmacro()

macro(import_backward_stacktrace)
    if(NOT TARGET backward)
        FetchContent_Declare(
            backward
            GIT_REPOSITORY https://github.com/bombela/backward-cpp
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/backward
        )
        FetchContent_MakeAvailable(backward)
        include_directories(${backward_SOURCE_DIR})
    endif()

    if(TARGET backward)
        add_deps_all_targets(PUBLIC Backward::Backward)
    endif()
endmacro()

macro(import_json)
    if(NOT TARGET json)
        FetchContent_Declare(
            json
            GIT_REPOSITORY https://github.com/nlohmann/json
            GIT_TAG b36f4c477c40356a0ae1204b567cca3c2a57d201
            SOURCE_DIR ${DEP_DIR}/json
        )
        FetchContent_MakeAvailable(json)
        include_directories(${json_SOURCE_DIR})
    endif()
endmacro()

macro(import_fmod)
    # import LOCAL version of fmod in FMOD/ folder
    set(FMOD_IMPORT_SUCCESS TRUE)
    set(FMOD_API_INSTALL_DIR "${CMAKE_SOURCE_DIR}/FMOD")
    set(FMOD_INCL_DIR "${FMOD_API_INSTALL_DIR}/api/core/inc")
    set(FMOD_LIB_DIR "${FMOD_API_INSTALL_DIR}/api/core/lib/x64")
    set(FMOD_DLL)

    if(NOT EXISTS "${FMOD_API_INSTALL_DIR}")
        message(STATUS "FMOD API not found in FMOD/ folder")
        set(FMOD_IMPORT_SUCCESS FALSE)
    endif()

    if(NOT EXISTS "${FMOD_INCL_DIR}")
        message(STATUS "FMOD API include directory not found in FMOD/ folder but FMOD API found check FMOD/api/core/inc")
        set(FMOD_IMPORT_SUCCESS FALSE)
    endif()

    IF(${FMOD_IMPORT_SUCCESS})
        find_library(FMOD_LIBRARY_DEBUG fmodL_vc PATHS ${FMOD_LIB_DIR})
        find_library(FMOD_LIBRARY_RELEASE fmod_vc PATHS ${FMOD_LIB_DIR})

        if(NOT FMOD_LIBRARY_DEBUG OR NOT FMOD_LIBRARY_RELEASE)
            message(STATUS "FMOD API library not found in FMOD/ folder")
            set(FMOD_IMPORT_SUCCESS FALSE)
        endif()

        add_library(fmod SHARED IMPORTED)
        set_target_properties(fmod PROPERTIES

            # Debug configuration
            IMPORTED_LOCATION_DEBUG ${FMOD_LIB_DIR}/fmodL.dll
            IMPORTED_IMPLIB_DEBUG ${FMOD_LIBRARY_DEBUG}

            # Release configuration
            IMPORTED_LOCATION_RELEASE ${FMOD_LIB_DIR}/fmod.dll
            IMPORTED_IMPLIB_RELEASE ${FMOD_LIBRARY_RELEASE}

            # MinSizeRel configuration
            IMPORTED_LOCATION_MINSIZEREL ${FMOD_LIB_DIR}/fmod.dll
            IMPORTED_IMPLIB_MINSIZEREL ${FMOD_LIBRARY_RELEASE}

            # RelWithDebInfo configuration
            IMPORTED_LOCATION_RELWITHDEBINFO ${FMOD_LIB_DIR}/fmod.dll
            IMPORTED_IMPLIB_RELWITHDEBINFO ${FMOD_LIBRARY_RELEASE}

            INTERFACE_INCLUDE_DIRECTORIES ${FMOD_INCL_DIR}
        )

        add_deps_all_targets(PUBLIC fmod)

    ELSE()
        message(STATUS "FMOD Import Failed.")
    ENDIF()
endmacro()

macro(import_freetype)

if (NOT TARGET freetype)
    FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype/
        GIT_TAG master
        SOURCE_DIR ${DEP_DIR}/freetype
    )
    FetchContent_MakeAvailable(freetype)
    include_directories(${freetype_SOURCE_DIR}/include)
    add_deps_all_targets(PUBLIC freetype)
endif()
endmacro()

macro (import_imgui)
    if (NOT TARGET imgui)
        FetchContent_Declare(
            imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/imgui
        )
        FetchContent_MakeAvailable(imgui)
        add_library(
            imgui
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            
        )
        add_library(
            imgui_backends
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        )
        include_directories(${imgui_SOURCE_DIR})
        include_directories(${imgui_SOURCE_DIR}/backends)
        add_deps_all_targets(PUBLIC imgui imgui_backends)
    endif()
endmacro()

macro(add_deps_all_targets ...)
    list(APPEND ALL_LIBS ${ARGN})
endmacro()

# Macro to import all dependencies
macro(importDependencies)
    # import_tinyobjloader()
    import_glew()
    import_glfw()
    import_glm()
    import_lodepng()
    import_soil()
    import_stb()
    import_backward_stacktrace()
    import_fmod()
    import_freetype()
    import_json()
    import_imgui()
endmacro()