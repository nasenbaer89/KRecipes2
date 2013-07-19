project(krecipes2)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(ECM 0.0.8 REQUIRED NO_MODULE) #TODO remove later
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH}) #TODO remove later
 
find_package(kdeqt5staging REQUIRED NO_MODULE) #TODO remove later

find_package(LibAttica NO_MODULE) #TODO remove later

find_package(KF5 5.0.0 REQUIRED MODULE COMPONENTS KCoreAddons KI18n 
                             KConfig KGuiAddons KWidgetsAddons #TODO remove later
                             KAuth KWindowSystem KService KCodecs #TODO remove later
                             KWidgets
                             ItemViews #TODO remove later
                             KIconThemes
                             Sonnet KNotifications KCompletion KTextWidgets #TODO remove later
                             XmlGui
                             )
find_package(Qt5Widgets)
find_package(Qt5 5.2.0 REQUIRED NO_MODULE COMPONENTS Svg DBus X11Extras Xml Network PrintSupport) #TODO remove later

qt5_wrap_ui(krecipes2view_ui src/krecipes2view.ui)

set(krecipes2_SRCS src/categoryitem.cpp
                   src/krecipes2.cpp
                   src/main.cpp
                   src/backends/recipedb.cpp
                   src/backends/literecipedb.cpp
                   src/recipelistmodel.cpp
                   src/krecipes2view.cpp
                   )

add_executable(krecipes2 ${krecipes2_SRCS} ${krecipes2view_ui})
qt5_use_modules(krecipes2 Widgets Sql)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(KF5_INCLUDE_DIRS /home/stefanie/Programmieren/KDE/KF5/inst/include) #FIXME
include_directories(${KF5_INCLUDE_DIRS} ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

#                                 message(STATUS "test" ${KCoreAddons_LIBRARIES})
target_link_libraries(krecipes2 #${Qt5Widgets_LIBRARIES}
                                ${KI18n_LIBRARIES}
                                ${KWidgets_LIBRARIES}
                                ${KCoreAddons_LIBRARIES}
                                ${XmlGui_LIBRARIES}
                                ${KIconThemes_LIBRARIES}
                                )

# install(TARGETS krecipes2 RUNTIME DESTINATION bin )
install(FILES src/krecipes2ui.rc DESTINATION  $ENV{XDG_DATA_HOME})
