project(krecipes2)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake 
                      ${CMAKE_MODULE_PATH}
                      /home/stefanie/Programmieren/KDE/KF5/inst/share/ECM-0.0.8/find-modules #FIXME
                      )
set(CMAKE_INSTALL_PREFIX ../inst)

set(krecipes2_SRCS src/krecipes2.cpp src/main.cpp src/backends/recipedb.cpp src/backends/literecipedb.cpp)
set(CMAKE_AUTOMOC ON)

add_executable(krecipes2 ${krecipes2_SRCS})
find_package(KF5 REQUIRED)
find_package(Qt5Widgets)
qt5_use_modules(krecipes2 Widgets Sql)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(KF5_INCLUDE_DIRS /home/stefanie/Programmieren/KDE/KF5/inst/include)
include_directories(${KF5_INCLUDE_DIRS} ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
set(KF5_LIB /home/stefanie/Programmieren/KDE/KF5/inst/lib/x86_64-linux-gnu)
set(KF5_LIBRARIES ${KF5_LIB}/libki18n.so
                  ${KF5_LIB}/libkdecore.so
                  ${KF5_LIB}/libKCoreAddons.so
                  ${KF5_LIB}/libkdeui.so
                  ${KF5_LIB}/libXmlGui.so
                  ${KF5_LIB}/libkwidgets.so
                  #${KF5_LIB}/libkguiaddons.so
                  #${KF5_LIB}/libKIconThemes.so
                  )
target_link_libraries(krecipes2 ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
                                ${KF5_LIBRARIES}
                                )

install(TARGETS krecipes2 RUNTIME DESTINATION bin )
install(FILES src/krecipes2ui.rc DESTINATION  $ENV{XDG_DATA_HOME})
