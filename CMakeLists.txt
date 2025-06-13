# !!!! FIXME: Right now to build you need to open projects panel in Qt Creator (or do it directly in CMakeLists.txt.user) and replace `-GNinja` with `-GUnix Makefiles` in every build configuration and then select "Re-configure with initial parameters"

cmake_minimum_required(VERSION 3.5)
project(harbour-fernschreiber2 CXX)

find_package (Qt5 COMPONENTS Core Network Qml Gui Quick DBus Sql Multimedia Positioning REQUIRED)
find_package(ZLIB REQUIRED)

find_package(PkgConfig)
pkg_search_module(SAILFISH REQUIRED sailfishapp)

pkg_check_modules(NEMO_NOTIFICATIONS REQUIRED nemonotifications-qt5)
include_directories(${NEMO_NOTIFICATIONS_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_definitions(-DQT_STATICPLUGIN)

set(SOURCES
    src/${CMAKE_PROJECT_NAME}.cpp
    src/appsettings.cpp
    src/boolfiltermodel.cpp
    src/chatpermissionfiltermodel.cpp
    src/chatlistmodel.cpp
    src/chatmodel.cpp
    src/contactsmodel.cpp
    src/dbusadaptor.cpp
    src/dbusinterface.cpp
    src/emojisearchworker.cpp
    src/fernschreiberutils.cpp
    src/knownusersmodel.cpp
    src/mceinterface.cpp
    src/namedaction.cpp
    src/notificationmanager.cpp
    src/processlauncher.cpp
    src/stickermanager.cpp
    src/tdlibfile.cpp
    src/tdlibreceiver.cpp
    src/tdlibwrapper.cpp
    src/textfiltermodel.cpp
    src/tgsplugin.cpp

    src/debuglog.h
    src/debuglogjs.h
    src/tdlibsecrets.h
)

# https://github.com/Samsung/rlottie.git
set(RLOTTIE_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/rlottie/src/vector/config.h)
# file(TOUCH RLOTTIE_CONFIG) # Empty config is fine
# add_dependencies(${CMAKE_PROJECT_NAME} ${RLOTTIE_CONFIG})

add_custom_target(rlottie_config ALL
    COMMAND ${CMAKE_COMMAND} -E touch ${RLOTTIE_CONFIG}
)

add_definitions(-DLOTTIE_THREAD_SUPPORT)

include_directories(
    rlottie/inc
    rlottie/src/vector
    rlottie/src/vector/freetype
)

set(RLOTTIE_SOURCES
    rlottie/src/lottie/lottieanimation.cpp
    rlottie/src/lottie/lottieitem.cpp
    rlottie/src/lottie/lottieitem_capi.cpp
    rlottie/src/lottie/lottiekeypath.cpp
    rlottie/src/lottie/lottieloader.cpp
    rlottie/src/lottie/lottiemodel.cpp
    rlottie/src/lottie/lottieparser.cpp

    rlottie/src/vector/freetype/v_ft_math.cpp
    rlottie/src/vector/freetype/v_ft_raster.cpp
    rlottie/src/vector/freetype/v_ft_stroker.cpp
    rlottie/src/vector/stb/stb_image.cpp
    rlottie/src/vector/varenaalloc.cpp
    rlottie/src/vector/vbezier.cpp
    rlottie/src/vector/vbitmap.cpp
    rlottie/src/vector/vbrush.cpp
    rlottie/src/vector/vdasher.cpp
    rlottie/src/vector/vdrawable.cpp
    rlottie/src/vector/vdrawhelper.cpp
    rlottie/src/vector/vdrawhelper_common.cpp
    rlottie/src/vector/vdrawhelper_neon.cpp
    rlottie/src/vector/vdrawhelper_sse2.cpp
    rlottie/src/vector/vmatrix.cpp
    rlottie/src/vector/vimageloader.cpp
    rlottie/src/vector/vinterpolator.cpp
    rlottie/src/vector/vpainter.cpp
    rlottie/src/vector/vpath.cpp
    rlottie/src/vector/vpathmesure.cpp
    rlottie/src/vector/vraster.cpp
    rlottie/src/vector/vrle.cpp
)

execute_process(COMMAND g++ -dM -E -x c++ - < /dev/null OUTPUT_VARIABLE CXX_FLAGS_OUTPUT)
if(CXX_FLAGS_OUTPUT MATCHES "__ARM_NEON__")
    message("Using NEON render functions")
    list(APPEND RLOTTIE_SOURCES rlottie/src/vector/pixman/pixman-arm-neon-asm.S)
elseif(CXX_FLAGS_OUTPUT MATCHES "__SSE2__")
    message("Using SSE2 render functions")
    list(APPEND RLOTTIE_SOURCES rlottie/src/vector/vdrawhelper_sse2.cpp)
else()
    message("Using default render functions")
endif()
# end rlottie

list(APPEND CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/lib")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${RLOTTIE_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:
    ${SAILFISH_INCLUDE_DIRS}
>)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    Qt5::Quick
    Qt5::DBus
    Qt5::Sql
    Qt5::Multimedia
    Qt5::Positioning
    ZLIB::ZLIB
    ${NEMO_NOTIFICATIONS_LIBRARIES}
    ${SAILFISH_LDFLAGS}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tdlib/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/tdlib/${CMAKE_SYSTEM_PROCESSOR}/lib)
find_library(TDJSON tdjson HINTS ${CMAKE_CURRENT_SOURCE_DIR}/tdlib/${CMAKE_SYSTEM_PROCESSOR}/lib)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${TDJSON})

install(TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION bin
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tdlib/${CMAKE_SYSTEM_PROCESSOR}/lib
    DESTINATION share/${CMAKE_PROJECT_NAME}
)
install(DIRECTORY qml
    DESTINATION share/${CMAKE_PROJECT_NAME}
)
install(DIRECTORY images
    DESTINATION share/${CMAKE_PROJECT_NAME}
)
install(DIRECTORY db
    DESTINATION share/${CMAKE_PROJECT_NAME}
)
install(DIRECTORY translations
    DESTINATION share/${CMAKE_PROJECT_NAME}
    FILES_MATCHING PATTERN "*.qm"
)
install(FILES ${CMAKE_PROJECT_NAME}.desktop
    DESTINATION share/applications
)

set(ICONPATH share/icons/hicolor)
install(FILES icons/86x86/${CMAKE_PROJECT_NAME}.png
    DESTINATION ${ICONPATH}/86x86/apps
)
install(FILES icons/108x108/${CMAKE_PROJECT_NAME}.png
    DESTINATION ${ICONPATH}/108x108/apps
)
install(FILES icons/128x128/${CMAKE_PROJECT_NAME}.png
    DESTINATION ${ICONPATH}/128x128/apps
)
install(FILES icons/172x172/${CMAKE_PROJECT_NAME}.png
    DESTINATION ${ICONPATH}/172x172/apps
)
install(FILES icons/256x256/${CMAKE_PROJECT_NAME}.png
    DESTINATION ${ICONPATH}/256x256/apps
)

# Tell Qt Creator where the application executable(s) would be located on the
# device.
#
# It is not necessary to list other deployables than executables (runtime
# targets) here. The deployment process of Sailfish OS projects is opaque to
# Qt Creator and the information contained in QtCreatorDeployment.txt is only
# used to locate the executable associated with the active run configuration
# on the device in order to run it.
#
# Search the Qt Creator Manual to learn about the QtCreatorDeployment.txt file
# format.
file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
    "${CMAKE_INSTALL_PREFIX}\n${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}:bin\n")


# https://github.com/Samsung/rlottie.git
# TODO: make rlottie an actual library

# add_library(rlottie ${RLOTTIE_SOURCES})
# add_dependencies(${CMAKE_PROJECT_NAME} rlottie_config)

# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE rlottie)

# add_subdirectory(rlottie)
# target_link_libraries(${CMAKE_PROJECT_NAME} rlottie)

# target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
#     rlottie/inc
#     rlottie/src/vector
#     rlottie/src/vector/freetype
# )