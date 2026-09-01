cmake_minimum_required(VERSION 3.16)

project(UsageTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appUsageTracker
    main.cpp
)

qt_add_qml_module(appUsageTracker
    URI UsageTracker
    QML_FILES
        Main.qml
        SOURCES window.h window.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appUsageTracker PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appUsageTracker
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    CXX_STANDARD 20
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
if(WIN32)
  set(CMAKE_PREFIX_PATH $ENV{CMAKE_PREF})
  set(SQLite3_LIBRARY $ENV{SQLITE_LIB})
endif()
find_package(SQLite3)

target_link_libraries(appUsageTracker
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
    PRIVATE SQLite::SQLite3
)

install(TARGETS appUsageTracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
