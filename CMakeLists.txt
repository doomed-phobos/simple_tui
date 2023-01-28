cmake_minimum_required(VERSION 3.2)

project(tui)

set(TUI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(TUI_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(tui-lib STATIC
   ${TUI_SRC_DIR}/menu.cc
   ${TUI_SRC_DIR}/system.cc)
target_include_directories(tui-lib PUBLIC ${TUI_INCLUDE_DIR})
target_link_libraries(tui-lib ncurses)
set_target_properties(
   tui-lib
   PROPERTIES
      CXX_STANDARD_REQUIRED ON
      CXX_STANDARD 17)