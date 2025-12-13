SUMMARY = "A Telegram client for SailfishOS"
LICENSE = "GPL-3.0-or-later"
LIC_FILES_CHKSUM = "file://LICENSE;md5=1ebbd3e34237af26da5dc08a4e440464"

SRC_URI = "git://github.com/roundedrectangle/harbour-fernschreiber2.git;protocol=https;branch=main"
SRCREV = "${AUTOREV}"
PR = "r1"
PV = "0.1+git${SRCREV}"

S = "${WORKDIR}/git"

inherit cmake_qt5 pkgconfig

# qttools: Qt5LinquistTools
DEPENDS += "ccache qml-asteroid qttools qttools-native qtdeclarative-native nemo-qml-plugin-notifications zlib qtmultimedia qtlocation"
RDEPENDS:${PN} += "qtlocation qtlocation-plugins"

FILES:${PN} += "/usr/share/asteroid-fernschreiber2/ /usr/share/icons/asteroid/asteroid-fernschreiber2.svg"

# Additional CMake options
EXTRA_OECMAKE = "-DEDITION=asteroid"