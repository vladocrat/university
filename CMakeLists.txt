cmake_minimum_required(VERSION 3.14)

project(db_idz VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LOG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/log.txt)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)
find_package(Qt5Sql REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        database.h database.cpp
        dbsettings.h
        user.h user.cpp
        student.h student.cpp
        group.h group.cpp
        passport.h passport.cpp
        databasecontroller.h databasecontroller.cpp
        filecontroller.h filecontroller.cpp
        logger.h
        userdata.h
        filelogger.h filelogger.cpp
        logincontroller.h logincontroller.cpp
        menucontroller.h menucontroller.cpp
        userrepository.h userrepository.cpp
        DB_config.h
        usersmodel.h usersmodel.cpp
        baserepository.h
        accessrightsrepository.h accessrightsrepository.cpp
        accessrightsmodel.h accessrightsmodel.cpp
        grouprepository.h grouprepository.cpp
        groupmodel.h groupmodel.cpp
        contracttype.h contracttype.cpp
        contracttyperepository.h contracttyperepository.cpp
        contracttypemodel.h contracttypemodel.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(db_idz
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET db_idz APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(db_idz SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(db_idz
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(db_idz
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(db_idz
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(db_idz PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(db_idz)
    qt_finalize_executable(db_idz)
endif()
