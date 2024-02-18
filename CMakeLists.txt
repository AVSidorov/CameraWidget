cmake_minimum_required(VERSION 3.16)
project(cameratest LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickWidgets)

qt_add_executable(${PROJECT_NAME}
        main.cpp
        CamerViewImageProvider.h
        CamerViewImageProvider.cpp
        ViewPort.h
        ViewPort.cpp
        camera.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickWidgets
)

set(INSTALL_EXAMPLEDIR ${PROJECT_SOURCE_DIR}/install/)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
