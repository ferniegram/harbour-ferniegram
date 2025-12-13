SUMMARY = "Telegram Database Library"
HOMEPAGE = "https://github.com/tdlib/td"
LICENSE = "BSL-1.0"
LIC_FILES_CHKSUM = "file://LICENSE_1_0.txt;md5=e4224ccaecb14d942c71d31bef20d78c \
                    file://example/uwp/LICENSE_1_0.txt;md5=e4224ccaecb14d942c71d31bef20d78c \
                    file://sqlite/sqlite/LICENSE;md5=77e11f02ab3482b8bd58b68a1c4b63d2 \
                    file://td/generate/tl-parser/LICENSE;md5=b234ee4d69f5fce4486a80fdaf4a4263"

SRC_URI = "git://github.com/tdlib/td;protocol=https;branch=master"
PV = "1.0"

S = "${WORKDIR}/git"

inherit cmake

DEPENDS = "ccache zlib openssl"

# Additional CMake options
EXTRA_OECMAKE = "-DCMAKE_BUILD_TYPE=Release -DTD_ENABLE_LTO=ON"