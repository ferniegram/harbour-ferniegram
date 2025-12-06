cmake_minimum_required(VERSION 3.5)
project(SortFilterProxyModel CXX)

find_package(Qt5 COMPONENTS Core Qml REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(SortFilterProxyModel STATIC)

if(Qt5_VERSION VERSION_LESS 5.9)
    target_compile_definitions(SortFilterProxyModel PRIVATE qmlWarning=qmlInfo)
endif()

target_include_directories(SortFilterProxyModel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(SortFilterProxyModel
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/qqmlsortfilterproxymodel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/filter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/filtercontainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/rolefilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/valuefilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/indexfilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/regexpfilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/rangefilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/expressionfilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/filtercontainerfilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/anyoffilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/alloffilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/filtersqmltypes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/sorter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/sortercontainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/rolesorter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/stringsorter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/expressionsorter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/sortersqmltypes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/proxyrole.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/proxyrolecontainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/joinrole.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/switchrole.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/expressionrole.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/proxyrolesqmltypes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/singlerole.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/regexprole.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/filtersorter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/filterrole.cpp
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/qqmlsortfilterproxymodel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/filter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/filtercontainer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/rolefilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/valuefilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/indexfilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/regexpfilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/rangefilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/expressionfilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/filtercontainerfilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/anyoffilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/alloffilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/sorter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/sortercontainer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/rolesorter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/stringsorter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/expressionsorter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/proxyrole.h
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/proxyrolecontainer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/joinrole.h
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/switchrole.h
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/expressionrole.h
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/singlerole.h
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/regexprole.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sorters/filtersorter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/proxyroles/filterrole.h
)

target_link_libraries(SortFilterProxyModel 
    Qt5::Core
    Qt5::Qml
)