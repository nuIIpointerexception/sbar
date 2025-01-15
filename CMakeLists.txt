cmake_minimum_required(VERSION 3.15)
project(sbar C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

find_program(MOLD_LINKER mold)
if(MOLD_LINKER)
    add_link_options("-fuse-ld=mold")
endif()

set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -flto -fdata-sections -ffunction-sections")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,--gc-sections")

find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND REQUIRED wayland-client)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PANGO REQUIRED pangocairo)

pkg_get_variable(WAYLAND_PROTOCOLS_DIR wayland-protocols pkgdatadir)
set(PROTOCOL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protocols)
file(MAKE_DIRECTORY ${PROTOCOL_DIR}/generated)

add_custom_command(
    OUTPUT ${PROTOCOL_DIR}/generated/xdg-shell-protocol.c ${PROTOCOL_DIR}/generated/xdg-shell-client-protocol.h
    COMMAND wayland-scanner client-header ${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml ${PROTOCOL_DIR}/generated/xdg-shell-client-protocol.h
    COMMAND wayland-scanner private-code ${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml ${PROTOCOL_DIR}/generated/xdg-shell-protocol.c
    DEPENDS ${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml)

add_custom_command(
    OUTPUT ${PROTOCOL_DIR}/generated/wlr-layer-shell-unstable-v1-protocol.c ${PROTOCOL_DIR}/generated/wlr-layer-shell-unstable-v1-client-protocol.h
    COMMAND wayland-scanner client-header ${PROTOCOL_DIR}/wlr-layer-shell-unstable-v1.xml ${PROTOCOL_DIR}/generated/wlr-layer-shell-unstable-v1-client-protocol.h
    COMMAND wayland-scanner private-code ${PROTOCOL_DIR}/wlr-layer-shell-unstable-v1.xml ${PROTOCOL_DIR}/generated/wlr-layer-shell-unstable-v1-protocol.c
    DEPENDS ${PROTOCOL_DIR}/wlr-layer-shell-unstable-v1.xml)

set(SOURCES src/main.c src/shm.c src/wayland.c src/state.c src/render.c ${PROTOCOL_DIR}/generated/xdg-shell-protocol.c ${PROTOCOL_DIR}/generated/wlr-layer-shell-unstable-v1-protocol.c)

add_executable(sbar ${SOURCES})
target_include_directories(sbar PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${PROTOCOL_DIR}/generated ${WAYLAND_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS})
target_link_libraries(sbar PRIVATE ${WAYLAND_LIBRARIES} ${CAIRO_LIBRARIES} ${PANGO_LIBRARIES} rt)
target_compile_options(sbar PRIVATE -Wall -Wextra -Wno-unused-parameter -O3 -march=native -flto -fno-plt -fstack-protector-strong)

include(GNUInstallDirs)
install(TARGETS sbar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}) 