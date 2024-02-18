# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(cameratest LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

# Resources:
set(${PROJECT_NAME}_resource_files
    "camera.qml"
    "images/pr.png"
)

qt_add_resources(${PROJECT_NAME} "camera"
        PREFIX
            "/camera"
        FILES
        ${${PROJECT_NAME}_resource_files}
)

set(INSTALL_EXAMPLEDIR ${PROJECT_SOURCE_DIR}/install/)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
