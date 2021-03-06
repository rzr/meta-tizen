DESCRIPTION = "Library for accessing the Secret Service API"
HOMEPAGE = "http://www.gnome.org/"
SECTION = "System/Libraries"
LICENSE = "LGPL-2.1+"
PV = "0.15"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by typelib-Secret
PROVIDES += "typelib-Secret"


#PROVIDES by libsecret-dev
PROVIDES += "libsecret-dev"


#PROVIDES by libsecret


#PROVIDES by libsecret-tools
PROVIDES += "libsecret-tools"


#PROVIDES by typelib-SecretUnstable
PROVIDES += "typelib-SecretUnstable"


RDEPENDS = ""
#RDEPENDS of libsecret-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "typelib-Secret"
RDEPENDS_${PN}-dev += "libsecret"
RDEPENDS_${PN}-dev += "typelib-SecretUnstable"


DEPENDS = ""
#DEPENDS of libsecret
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS_append_class-native = " intltool-native"
DEPENDS_append_class-target = " intltool-native"
DEPENDS += "vala"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "docbook-xsl-stylesheets"
DEPENDS += "gtk-doc-stub"
DEPENDS += "libxslt"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "libgcrypt"
DEPENDS += "gtk-doc"
DEPENDS += "libxslt"


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
  
  
   
  autotools_do_configure
  make V=1
  
  
  
}
EXTRA_OECONF += " --disable-static"

do_install() {
 export RPM_BUILD_ROOT=${D}
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
 #find_lang libsecret
 rm -rf ${D}${prefix}/share/locales/*
 #fdupes ${D}
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libsecret-tools "
PACKAGES += " libsecret "
PACKAGES += " libsecret-dev "
PACKAGES += " typelib-Secret "
PACKAGES += " typelib-SecretUnstable "

libsecret-tools_files = ""
libsecret-tools_files += "${prefix}/bin/secret-tool"

libsecret_files = ""
libsecret_files += "${prefix}/lib/libsecret-1.so.*"

libsecret-dev_files = ""
libsecret-dev_files += "AUTHORS ChangeLog NEWS README"
libsecret-dev_files += "${prefix}/lib/libsecret-1.so"
libsecret-dev_files += "${prefix}/lib/pkgconfig/libsecret-1.pc"
libsecret-dev_files += "${prefix}/lib/pkgconfig/libsecret-unstable.pc"
libsecret-dev_files += "${prefix}/include/libsecret-1/"
libsecret-dev_files += "${prefix}/share/gir-1.0/Secret-1.gir"
libsecret-dev_files += "${prefix}/share/gir-1.0/SecretUnstable-0.gir"
libsecret-dev_files += "${prefix}/share/vala/vapi"
libsecret-dev_files += "${prefix}/share/vala/vapi/libsecret-1.deps"
libsecret-dev_files += "${prefix}/share/vala/vapi/libsecret-1.vapi"
libsecret-dev_files += "${prefix}/share/vala/vapi/libsecret-unstable.deps"
libsecret-dev_files += "${prefix}/share/vala/vapi/libsecret-unstable.vapi"
libsecret-dev_files += "${prefix}/share/vala/vapi/mock-service-0.vapi"
DIRFILES_${PN}-dev = ""
DIRFILES_${PN}-dev += "${prefix}/share/vala/vapi"

typelib-Secret_files = ""
typelib-Secret_files += "${prefix}/lib/girepository-1.0/Secret-1.typelib"

typelib-SecretUnstable_files = ""
typelib-SecretUnstable_files += "${prefix}/lib/girepository-1.0/SecretUnstable-0.typelib"

FILES_${PN}-tools = "${libsecret-tools_files}"
FILES_${PN} = "${libsecret_files}"
FILES_${PN}-dev = "${libsecret-dev_files}"
FILES_typelib-Secret = "${typelib-Secret_files}"
FILES_typelib-SecretUnstable = "${typelib-SecretUnstable_files}"

PKG_libsecret-tools= "libsecret-tools"
PKG_libsecret= "libsecret"
PKG_libsecret-dev= "libsecret-dev"
PKG_typelib-Secret= "typelib-Secret"
PKG_typelib-SecretUnstable= "typelib-SecretUnstable"

require libsecret-extraconf.inc

