include(FetchContent)
set(DEP_DIR "${CMAKE_BINARY_DIR}/lib/")
# Macro to import tinyobjloader
macro(import_tinyobjloader)
    if(NOT TARGET tinyobjloader)  # Guard to prevent multiple inclusion
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
    if (NOT TARGET lodepng)
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
    if (NOT TARGET glm)
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
    if (NOT TARGET glew_s)
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
    if (NOT TARGET glfw)
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
    if (NOT TARGET fmod)
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
    if (NOT TARGET soil)
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
    if (NOT TARGET stb)
        FetchContent_Declare(
            stb
            GIT_REPOSITORY https://github.com/gracicot/stb-cmake
            GIT_TAG master
            SOURCE_DIR ${DEP_DIR}/stb
        )
        FetchContent_MakeAvailable(stb)
        include_directories(${stb_SOURCE_DIR}/stb)
    endif()
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
endmacro()