cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# delete cmake cache folder before changing this option
set(BUILD_SDL1 OFF CACHE BOOL "Build with SDL1 support (software, osmesa) support")
set(BUILD_SDL1_GL OFF CACHE BOOL "Build with SDL1 support (hardware rendering, fast, needs BUILD_SDL1=ON)")
set(BUILD_SDL2 OFF CACHE BOOL "Build with SDL2 (software) support")
set(BUILD_SDL2_GL OFF CACHE BOOL "Build with SDL2 support (hardware rendering, fast, needs BUILD_SDL2=ON)")
set(BUILD_PSP2 OFF CACHE BOOL "Build with PSP2 support")
set(BUILD_PS3 OFF CACHE BOOL "Build with PS3 support")
set(BUILD_3DS OFF CACHE BOOL "Build with 3DS support")
set(BUILD_NX ON CACHE BOOL "Build with NX (SWITCH) support")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_DEBUG true CACHE BOOL "Debug build")
endif ()

# setup toolchain
include(libcross2d/Toolchain.cmake)
enable_language(ASM)

execute_process(COMMAND "date" "+%Y.%m.%d" OUTPUT_VARIABLE BUILD_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)

# add cross2d library. If you want to port pfba to another platform,
# you should (may) only need to port this library.
add_subdirectory(libcross2d)

project(nxfiler)

set(NXFILER_DIRS src)
file(GLOB NXFILER_SRC src/*.cpp)

# source files
set(SRC ${NXFILER_SRC})

# includes
set(INC ${NXFILER_DIRS})

# flags
set(FLAGS)

if (BUILD_PSP2)
elseif (BUILD_PS3)
elseif (BUILD_3DS)
elseif (BUILD_NX)
    list(APPEND FLAGS -D__SWITCH__)
elseif (BUILD_SDL2)
elseif (BUILD_SDL1)
elseif (BUILD_SFML)
endif (BUILD_PSP2)

##########################
# main target
##########################
add_executable(${PROJECT_NAME}.elf ${SRC})
target_compile_options(${PROJECT_NAME}.elf PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME}.elf PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++11 -fpermissive>)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${INC})
target_link_libraries(${PROJECT_NAME}.elf cross2d ${LDFLAGS})

#####################
# PSP2 (vita) vpk
#####################
if (BUILD_PSP2)
endif (BUILD_PSP2)

#####################
# PS3
#####################
if (BUILD_PS3)
endif (BUILD_PS3)

#####################
# CTR (3DS) target
#####################
if (BUILD_3DS)
endif (BUILD_3DS)

#####################
# NX (SWITCH) target
#####################
if (BUILD_NX)
    set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_FLAGS "-specs=${DEVKITPRO}/libnx/switch.specs")
    add_custom_target(${PROJECT_NAME}.nro
            DEPENDS ${PROJECT_NAME}.elf
            COMMAND nacptool --create "nxFiler" "Cpasjuste" "1.0" nxFiler.nacp
            COMMAND elf2nro ${PROJECT_NAME}.elf ${PROJECT_NAME}.nro --nacp=nxFiler.nacp
            #--icon=${CMAKE_SOURCE_DIR}/pfba/data/nx/icon.jpg
            )
endif (BUILD_NX)
