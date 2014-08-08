DESCRIPTION = "Feedback library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libfeedback-dev
PROVIDES += "libfeedback-dev"


#PROVIDES by libsvi


#PROVIDES by libsvi-dev
PROVIDES += "libsvi-dev"


#PROVIDES by svi-data
PROVIDES += "svi-data"


#PROVIDES by libfeedback
PROVIDES += "libfeedback"


RDEPENDS = ""
#RDEPENDS of libfeedback-dev (libfeedback-dev)
RDEPENDS_libfeedback-dev += "libfeedback"

#RDEPENDS of libsvi (${PN})
RDEPENDS_${PN} += "libfeedback"

#RDEPENDS of libfeedback (libfeedback)
RDEPENDS_libfeedback += "eglibc"

#RDEPENDS of libsvi-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libsvi"


DEPENDS = ""
#DEPENDS of libfeedback
DEPENDS += "libhaptic"
DEPENDS += "libmm-sound"
DEPENDS_append_class-native = " cmake-native"
DEPENDS_append_class-target = " cmake-native"
DEPENDS += "libxml2"
DEPENDS += "tizen-platform-config"
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "common"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q 
 
 
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
 
 cp ${S}/packaging/libsvi.manifest .
 cp ${S}/packaging/libfeedback.manifest .
 cp ${S}/packaging/svi-data.manifest .
 
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
         ${EXTRA_OECMAKE} .
 oe_runmake
 
 
 
}

do_install() {
 echo export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 mkdir -p ${D}${prefix}/share/license
 cp LICENSE.APLv2 ${D}${prefix}/share/license/libfeedback
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
}

pkg_postinst_libsvi() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
}

pkg_postrm_svi-data() {
    #!/bin/sh -e

    rm -rf $D${prefix}/share/feedback/

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
}

pkg_postrm_libsvi() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libfeedback-dev "
PACKAGES += " svi-data "
PACKAGES += " libfeedback "
PACKAGES += " libsvi-dev "
PACKAGES += " libsvi "

libfeedback-dev_files = ""
libfeedback-dev_files += "${prefix}/include/feedback/*.h"
libfeedback-dev_files += "${prefix}/lib/libfeedback.so"
libfeedback-dev_files += "${prefix}/lib/pkgconfig/feedback.pc"
MANIFESTFILES_libfeedback-dev = "libfeedback.manifest"

svi-data_files = ""
svi-data_files += "${prefix}/share/feedback/*"
MANIFESTFILES_svi-data = "libfeedback.manifest"

libfeedback_files = ""
libfeedback_files += "${prefix}/lib/libfeedback.so.*"
libfeedback_files += "${prefix}/share/license/libfeedback"
MANIFESTFILES_libfeedback = "libfeedback.manifest"

libsvi-dev_files = ""
libsvi-dev_files += "${prefix}/include/svi/*.h"
libsvi-dev_files += "${prefix}/lib/libsvi.so"
libsvi-dev_files += "${prefix}/lib/pkgconfig/svi.pc"
MANIFESTFILES_${PN}-dev = "libfeedback.manifest"

libsvi_files = ""
libsvi_files += "${prefix}/lib/libsvi.so.*"
MANIFESTFILES_${PN} = "libfeedback.manifest"

FILES_libfeedback-dev = "${libfeedback-dev_files}"
FILES_svi-data = "${svi-data_files}"
FILES_libfeedback = "${libfeedback_files}"
FILES_${PN}-dev = "${libsvi-dev_files}"
FILES_${PN} = "${libsvi_files}"

PKG_libfeedback-dev= "libfeedback-dev"
PKG_svi-data= "svi-data"
PKG_libfeedback= "libfeedback"
PKG_libsvi-dev= "libsvi-dev"
PKG_libsvi= "libsvi"

require libsvi-extraconf.inc
