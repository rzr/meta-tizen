DESCRIPTION = "NFC framework manager"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Network & Connectivity/NFC"
LICENSE = "Flora"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by nfc-common-neard-dev
PROVIDES += "nfc-common-neard-dev"


#PROVIDES by nfc-client-lib-neard
PROVIDES += "nfc-client-lib-neard"


#PROVIDES by nfc-manager-neard


#PROVIDES by nfc-client-lib-neard-dev
PROVIDES += "nfc-client-lib-neard-dev"


RDEPENDS = ""
#RDEPENDS of nfc-client-lib-neard-dev (nfc-client-lib-neard-dev)
RDEPENDS_nfc-client-lib-neard-dev += "nfc-client-lib-neard"

#RDEPENDS of nfc-manager-neard (${PN})
RDEPENDS_${PN} += "neardal"
RDEPENDS_${PN} += "neard"
RDEPENDS_${PN} += "eglibc"
RDEPENDS_${PN} += "nfc-client-lib-neard"
RDEPENDS_${PN} += "vconf"


DEPENDS = ""
#DEPENDS of nfc-manager-neard
DEPENDS += "security-server"
DEPENDS += "libtapi-legacy"
DEPENDS += "curl"
DEPENDS_append_class-native = " cmake-native"
DEPENDS_append_class-target = " cmake-native"
DEPENDS += "slp-pkgmgr"
DEPENDS += "app-svc"
DEPENDS += "aul"
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "bluetooth-frwk"
inherit pythonnative
DEPENDS += "libsvi"
DEPENDS += "tizen-platform-config"
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "pkgmgr-info"
DEPENDS += "python-xml"
DEPENDS += "ecore"
DEPENDS += "vconf"
DEPENDS += "libmm-sound"
DEPENDS += "wav-player"
DEPENDS += "wifi"
DEPENDS += "openssl"
DEPENDS += "neardal"
DEPENDS += "libslp-pm"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/nfc-manager-neard.manifest .
 
 
 
}
do_patch_append() {
    bb.build.exec_func('do_prep', d)
}

do_configure() {
}

do_compile() {
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 LD_AS_NEEDED=1; export LD_AS_NEEDED ;
 
 MAJORVER=`echo 0.1.6 | awk 'BEGIN {FS="."}{print $1}'`
 
   cmake \
         -DCMAKE_VERBOSE_MAKEFILE=ON \
         -DCMAKE_INSTALL_PREFIX:PATH=${prefix} \
         -DCMAKE_INSTALL_LIBDIR:PATH=${prefix}/lib \
         -DINCLUDE_INSTALL_DIR:PATH=${prefix}/include \
         -DLIB_INSTALL_DIR:PATH=${prefix}/lib \
         -DSYSCONF_INSTALL_DIR:PATH=${sysconfdir} \
         -DSHARE_INSTALL_PREFIX:PATH=${prefix}/share \
         -DCMAKE_SKIP_RPATH:BOOL=ON \
         -DBUILD_SHARED_LIBS:BOOL=ON \
         ${EXTRA_OECMAKE} . -DMAJORVER=${MAJORVER} -DFULLVER=0.1.6  \
 -DWAYLAND_SUPPORT=On \
 -DX11_SUPPORT=Off
 
 
 
 
}

do_install() {
 echo export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 mkdir -p ${D}${prefix}/lib/systemd/system/multi-user.target.wants
 cp -af ${S}/packaging/nfc-manager-neard.service ${D}${prefix}/lib/systemd/system/
 ln -s ../nfc-manager-neard.service ${D}${prefix}/lib/systemd/system/multi-user.target.wants/nfc-manager-neard.service
 
 
}

pkg_postinst_nfc-client-lib-neard() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
    USER_GROUP_ID=$(getent group users | cut -d: -f3)
    vconftool set -t bool db/nfc/feature 0 -g $USER_GROUP_ID -f
    vconftool set -t bool db/nfc/predefined_item_state 0 -g $USER_GROUP_ID -f
    vconftool set -t string db/nfc/predefined_item "None" -g $USER_GROUP_ID -f
    vconftool set -t bool db/nfc/enable 0 -g $USER_GROUP_ID -f
    vconftool set -t int db/nfc/se_type 0 -g $USER_GROUP_ID -f

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
    [ "x\$D" == "x" ] && systemctl daemon-reload
    if [ $1 == 1 ]; then
        systemctl restart nfc-manager-neard.service
    fi

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
    if [ $1 == 0 ]; then
        systemctl stop nfc-manager-neard.service
    fi
    [ "x\$D" == "x" ] && systemctl daemon-reload

}

pkg_postrm_nfc-client-lib-neard() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " nfc-client-lib-neard "
PACKAGES += " nfc-client-lib-neard-dev "
PACKAGES += " nfc-manager-neard "
PACKAGES += " nfc-common-neard-dev "

nfc-client-lib-neard_files = ""
nfc-client-lib-neard_files += "${prefix}/lib/libnfc.so.*"
MANIFESTFILES_nfc-client-lib-neard = "nfc-manager-neard.manifest"

nfc-client-lib-neard-dev_files = ""
nfc-client-lib-neard-dev_files += "${prefix}/lib/libnfc.so"
nfc-client-lib-neard-dev_files += "${prefix}/lib/pkgconfig/nfc.pc"
nfc-client-lib-neard-dev_files += "${prefix}/include/nfc/*.h"

nfc-manager-neard_files = ""
nfc-manager-neard_files += "${prefix}/bin/nfc-manager-daemon"
nfc-manager-neard_files += "${prefix}/lib/systemd/system/nfc-manager-neard.service"
nfc-manager-neard_files += "${prefix}/lib/systemd/system/multi-user.target.wants/nfc-manager-neard.service"
nfc-manager-neard_files += "${prefix}/share/dbus-1/system-services/org.tizen.NetNfcService.service"
nfc-manager-neard_files += "${prefix}/share/packages/nfc-manager.xml"
nfc-manager-neard_files += "${prefix}/share/nfc-manager-daemon/sounds/*"
MANIFESTFILES_${PN} = "nfc-manager-neard.manifest"

nfc-common-neard-dev_files = ""
nfc-common-neard-dev_files += "${prefix}/lib/pkgconfig/nfc-common.pc"
nfc-common-neard-dev_files += "${prefix}/include/nfc-common/*.h"

FILES_nfc-client-lib-neard = "${nfc-client-lib-neard_files}"
FILES_nfc-client-lib-neard-dev = "${nfc-client-lib-neard-dev_files}"
FILES_${PN} = "${nfc-manager-neard_files}"
FILES_nfc-common-neard-dev = "${nfc-common-neard-dev_files}"

PKG_nfc-client-lib-neard= "nfc-client-lib-neard"
PKG_nfc-client-lib-neard-dev= "nfc-client-lib-neard-dev"
PKG_nfc-manager-neard= "nfc-manager-neard"
PKG_nfc-common-neard-dev= "nfc-common-neard-dev"

require nfc-manager-neard-extraconf.inc
