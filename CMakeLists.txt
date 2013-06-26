project(krecipes2)
cmake_minimum_required(VERSION 2.6)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(krecipes2_SRCS src/krecipes2.cpp src/main.cpp src/backends/recipedb.cpp src/backends/literecipedb.cpp)
set(CMAKE_AUTOMOC ON)

add_executable(krecipes2 ${krecipes2_SRCS})
# Find the QtWidgets library
find_package(Qt5Widgets)
qt5_use_modules(krecipes2 Widgets Sql)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries(krecipes2 ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
#install(TARGETS krecipes2 RUNTIME DESTINATION bin)

install(TARGETS krecipes2 RUNTIME DESTINATION bin)
install(FILES src/krecipes2ui.rc DESTINATION  share)
