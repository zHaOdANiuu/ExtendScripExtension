cmake_minimum_required(VERSION 3.20.0)
project(ExtendScripExtension)

# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)
set(AE_SDK_PATH "E:/C_C++/After-Effects-Plug-ins/include")
set(DIST_DIR ${PROJECT_SOURCE_DIR}/bin)

set(LIBRARY_OUTPUT_PATH ${DIST_DIR}/${CMAKE_BUILD_TYPE})

file(
    GLOB_RECURSE
    SOURCE_FILES
    ${AE_SDK_PATH}/Util/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/func/*.cpp
    ${PROJECT_SOURCE_DIR}/src/export/*.cpp
)
add_library(
    ${PROJECT_NAME}
    MODULE
    ${SOURCE_FILES}
)
target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    UNICODE
    _UNICODE
    WIN32
    WINDOWS
    _WINDOWS
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${AE_SDK_PATH}/External
    ${AE_SDK_PATH}/Headers
    ${AE_SDK_PATH}/Headers/SP
    ${AE_SDK_PATH}/Resources
    ${AE_SDK_PATH}/Util
    ${PROJECT_SOURCE_DIR}/inc/func
    ${PROJECT_SOURCE_DIR}/inc
)
# to aex plugin
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/res)
set(RC_R ${RESOURCE_DIR}/${PROJECT_NAME}.r)
set(RC_RR ${RESOURCE_DIR}/${PROJECT_NAME}.rr)
set(RC_RRC ${RESOURCE_DIR}/${PROJECT_NAME}.rrc)
set(RC_RC ${RESOURCE_DIR}/${PROJECT_NAME}.rc)
add_custom_command(
    OUTPUT ${RC_RR}
    COMMAND cl /I "${AE_SDK_PATH}/Headers" /EP \"${RC_R}\" > ${RC_RR}
)
add_custom_command(
    DEPENDS ${RC_RR}
    OUTPUT ${RC_RRC}
    COMMAND "${AE_SDK_PATH}/Resources/PiPLtool.exe" "${RC_RR}" "${RC_RRC}"
)
add_custom_command(
    DEPENDS ${RC_RRC}
    OUTPUT ${RC_RC}
    COMMAND cl /EP ${RC_RRC} > ${RC_RC}
)
target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${RC_RC}
)
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".aex")
# # 开启LTO
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -ffunction-sections -fdata-sections")
# set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -flto -Wl,--gc-sections -Wl,--strip-all")
