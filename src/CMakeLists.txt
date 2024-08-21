set(TUI_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

find_package(PkgConfig REQUIRED)
pkg_search_module(NCURSES REQUIRED ncurses menu)
pkg_search_module(BLEPP REQUIRED libblepp)

add_library(tui-lib STATIC
text_format.cc
system.cc)
target_include_directories(tui-lib PUBLIC ${TUI_INCLUDE_DIR} ${NCURSES_INCLUDE_DIRS})
target_link_libraries(tui-lib ${NCURSES_LIBRARIES})