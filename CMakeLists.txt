cmake_minimum_required(VERSION 3.14)

project(db_idz VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(REPOSITORIES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/repositories)
set(MODELS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/models)
set(CONTROLLERS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/controllers)
set(ENTITIES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/entities)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)
find_package(Qt5Sql REQUIRED)

include_directories(${REPOSITORIES_PATH})
include_directories(${MODELS_PATH})
include_directories(${CONTROLLERS_PATH})
include_directories(${ENTITIES_PATH})

set(PROJECT_SOURCES
        main.cpp
        database.h database.cpp
        dbsettings.h
        user.h user.cpp
        logger.h
        filelogger.h filelogger.cpp
        DB_config.h
        baserepository.h

        ${ENTITIES_PATH}/contracttype.h ${ENTITIES_PATH}/contracttype.cpp
        ${ENTITIES_PATH}/GapYear.h
        ${ENTITIES_PATH}/document.h
        ${ENTITIES_PATH}/Dormitory.h
        ${ENTITIES_PATH}/userdata.h
        ${ENTITIES_PATH}/group.h ${ENTITIES_PATH}/group.cpp
        ${ENTITIES_PATH}/passport.h ${ENTITIES_PATH}/passport.cpp
        ${ENTITIES_PATH}/student.h ${ENTITIES_PATH}/student.cpp

        ${CONTROLLERS_PATH}/databasecontroller.h ${CONTROLLERS_PATH}/databasecontroller.cpp
        ${CONTROLLERS_PATH}/filecontroller.h ${CONTROLLERS_PATH}/filecontroller.cpp
        ${CONTROLLERS_PATH}/logincontroller.h ${CONTROLLERS_PATH}/logincontroller.cpp
        ${CONTROLLERS_PATH}/menucontroller.h ${CONTROLLERS_PATH}/menucontroller.cpp

        ${MODELS_PATH}/usersmodel.h ${MODELS_PATH}/usersmodel.cpp
        ${MODELS_PATH}/accessrightsmodel.h ${MODELS_PATH}/accessrightsmodel.cpp
        ${MODELS_PATH}/groupmodel.h ${MODELS_PATH}/groupmodel.cpp
        ${MODELS_PATH}/contracttypemodel.h ${MODELS_PATH}/contracttypemodel.cpp
        ${MODELS_PATH}/documentmodel.h ${MODELS_PATH}/documentmodel.cpp
        ${MODELS_PATH}/gapyearmodel.h ${MODELS_PATH}/gapyearmodel.cpp
        ${MODELS_PATH}/passporttypemodel.h ${MODELS_PATH}/passporttypemodel.cpp
        ${MODELS_PATH}/studentmodel.h ${MODELS_PATH}/studentmodel.cpp
        ${MODELS_PATH}/dormitorymodel.h ${MODELS_PATH}/dormitorymodel.cpp

        ${REPOSITORIES_PATH}/documentrepository.h ${REPOSITORIES_PATH}/documentrepository.cpp
        ${REPOSITORIES_PATH}/userrepository.h ${REPOSITORIES_PATH}/userrepository.cpp
        ${REPOSITORIES_PATH}/grouprepository.h ${REPOSITORIES_PATH}/grouprepository.cpp
        ${REPOSITORIES_PATH}/gapyearrepository.h ${REPOSITORIES_PATH}/gapyearrepository.cpp
        ${REPOSITORIES_PATH}/passporttyperepository.h ${REPOSITORIES_PATH}/passporttyperepository.cpp
        ${REPOSITORIES_PATH}/dormitoryrepository.h ${REPOSITORIES_PATH}/dormitoryrepository.cpp
        ${REPOSITORIES_PATH}/contracttyperepository.h ${REPOSITORIES_PATH}/contracttyperepository.cpp
        ${REPOSITORIES_PATH}/accessrightsrepository.h ${REPOSITORIES_PATH}/accessrightsrepository.cpp
        ${REPOSITORIES_PATH}/studentrepository.h ${REPOSITORIES_PATH}/studentrepository.cpp

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
