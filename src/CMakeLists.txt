set(TUI_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncursesw)

add_library(tui-lib STATIC
  text_format.cc
  system.cc)
target_include_directories(tui-lib PUBLIC ${TUI_INCLUDE_DIR} ${NCURSES_INCLUDE_DIRS})
target_link_libraries(tui-lib ${NCURSES_LIBRARIES})