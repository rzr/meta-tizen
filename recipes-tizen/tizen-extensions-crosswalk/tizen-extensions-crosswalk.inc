DESCRIPTION = "Tizen Web APIs implemented using Crosswalk"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Development/Libraries"
LICENSE = "BSD-3-Clause and Apache-2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by tizen-extensions-crosswalk-bluetooth-demo


#PROVIDES by tizen-extensions-crosswalk


#PROVIDES by tizen-extensions-crosswalk-examples


#PROVIDES by tizen-extensions-crosswalk-system-info-demo


RDEPENDS = ""
#RDEPENDS of tizen-extensions-crosswalk-bluetooth-demo (${PN}-bluetooth-demo)
RDEPENDS_${PN}-bluetooth-demo += "tizen-extensions-crosswalk"

#RDEPENDS of tizen-extensions-crosswalk (${PN})
RDEPENDS_${PN} += "crosswalk"
RDEPENDS_${PN} += "media-thumbnail-server"

#RDEPENDS of tizen-extensions-crosswalk-examples (${PN}-examples)
RDEPENDS_${PN}-examples += "tizen-extensions-crosswalk"

#RDEPENDS of tizen-extensions-crosswalk-system-info-demo (${PN}-system-info-demo)
RDEPENDS_${PN}-system-info-demo += "tizen-extensions-crosswalk"


DEPENDS = ""
#DEPENDS of tizen-extensions-crosswalk
DEPENDS += "pkgconfig(evas)"
DEPENDS += "udev"
DEPENDS += "app-core"
DEPENDS += "pkgconfig(pkgmgr)"
DEPENDS += "bluez"
DEPENDS += "pkgconfig(capi-system-device)"
DEPENDS += "wayland"
DEPENDS += "notification"
DEPENDS += "pkgconfig(capi-web-url-download)"
DEPENDS += "glib-2.0"
DEPENDS += "application"
DEPENDS += "system-info"
DEPENDS += "pkgconfig(capi-web-favorites)"
DEPENDS += "pkgconfig(capi-system-system-settings)"
DEPENDS += "pkgconfig(capi-network-bluetooth)"
inherit pythonnative
DEPENDS += "tizen-platform-config"
DEPENDS += "pkgmgr-info"
DEPENDS += "libslp-pm"
DEPENDS_append_class-native = " ninja-native"
DEPENDS_append_class-target = " ninja-native"
DEPENDS += "pkgconfig(capi-system-power)"
DEPENDS += "vconf"
DEPENDS += "pkgconfig(capi-network-connection)"
DEPENDS += "pkgconfig(capi-appfw-app-manager)"
DEPENDS += "dbus"
DEPENDS += "pkgconfig(capi-system-sensor)"
DEPENDS += "pkgconfig(capi-content-media-content)"
DEPENDS += "pkgconfig(capi-system-runtime-info)"
DEPENDS += "pkgconfig(message-port)"
DEPENDS += "libtapi-legacy"
DEPENDS += "pkgconfig(capi-appfw-package-manager)"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 cp ${S}/packaging/tizen-extensions-crosswalk.manifest .
 cp ${S}/packaging/tizen-extensions-crosswalk.in .
 cp ${S}/packaging/tizen-extensions-crosswalk.png .
 cp ${S}/packaging/tizen-extensions-crosswalk-bluetooth-demo .
 cp ${S}/packaging/tizen-extensions-crosswalk-examples .
 cp ${S}/packaging/tizen-extensions-crosswalk-system-info-demo .
 
 sed "s|@LIB_INSTALL_DIR@|${prefix}/lib|g" tizen-extensions-crosswalk.in > tizen-extensions-crosswalk
 
 
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
 CFLAGS="-O2 -g -m64 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables" ; export CFLAGS ;
 CXXFLAGS="${CXXFLAGS:--O2 -g -m64 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables}" ; export CXXFLAGS ;
 FFLAGS="${FFLAGS:--O2 -g -m64 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables -I%_fmoddir}" ; export FFLAGS ;
 LD_AS_NEEDED=1; export LD_AS_NEEDED ;
 
 
 export GYP_GENERATORS='ninja'
 GYP_OPTIONS="--depth=. -Dtizen=1 -Dextension_build_type=Debug -Dextension_host_os=pc"
 
 GYP_OPTIONS="$GYP_OPTIONS -Ddisplay_type=wayland"
 
 ./tools/gyp/gyp $GYP_OPTIONS tizen-wrt.gyp
 
 ninja -C out/Default -j16
 
 
 
}

do_install() {
 echo export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 
 # Binary wrapper.
 install -m 755 -D tizen-extensions-crosswalk ${D}${prefix}/bin/tizen-extensions-crosswalk
 install -m 755 -D ${S}/packaging/tizen-extensions-crosswalk-bluetooth-demo ${D}${prefix}/bin/tizen-extensions-crosswalk-bluetooth-demo
 install -m 755 -D ${S}/packaging/tizen-extensions-crosswalk-examples ${D}${prefix}/bin/tizen-extensions-crosswalk-examples
 install -m 755 -D ${S}/packaging/tizen-extensions-crosswalk-system-info-demo ${D}${prefix}/bin/tizen-extensions-crosswalk-system-info-demo
 
 # Extensions.
 mkdir -p ${D}${prefix}/lib/tizen-extensions-crosswalk
 install -p -m 644 out/Default/libtizen*.so ${D}${prefix}/lib/tizen-extensions-crosswalk
 
 # Examples.
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/examples
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/examples/js
 install -p -m 644 examples/*.html ${D}${prefix}/share/tizen-extensions-crosswalk/examples
 install -p -m 644 examples/js/*.js ${D}${prefix}/share/tizen-extensions-crosswalk/examples/js
 
 # Demos
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/css
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/js
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/images
 
 install -p -m 644 demos/tizen/*.html ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen
 install -p -m 644 demos/tizen/css/*.css ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/css
 install -p -m 644 demos/tizen/js/*.js ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/js
 install -p -m 644 demos/tizen/images/*.png ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/images
 
 # Demos - System Info
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/css
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/js
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/images
 
 install -p -m 644 demos/system_info/*.html ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info
 install -p -m 644 demos/system_info/css/*.css ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/css
 install -p -m 644 demos/system_info/js/*.js ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/js
 install -p -m 644 demos/system_info/images/*.png ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/images
 
 # register to the package manager
 install -m 644 -D tizen-extensions-crosswalk-examples.xml ${D}${prefix}/share/packages/tizen-extensions-crosswalk-examples.xml
 install -m 644 -D tizen-extensions-crosswalk-bluetooth-demo.xml ${D}${prefix}/share/packages/tizen-extensions-crosswalk-bluetooth-demo.xml
 install -m 644 -D tizen-extensions-crosswalk-system-info-demo.xml ${D}${prefix}/share/packages/tizen-extensions-crosswalk-system-info-demo.xml
 install -p -D tizen-extensions-crosswalk.png ${D}${prefix}/share/icons/default/small/tizen-extensions-crosswalk-examples.png
 install -p -D tizen-extensions-crosswalk.png ${D}${prefix}/share/icons/default/small/tizen-extensions-crosswalk-bluetooth-demo.png
 install -p -D tizen-extensions-crosswalk.png ${D}${prefix}/share/icons/default/small/tizen-extensions-crosswalk-system-info-demo.png
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " tizen-extensions-crosswalk-bluetooth-demo "
PACKAGES += " tizen-extensions-crosswalk "
PACKAGES += " tizen-extensions-crosswalk-examples "
PACKAGES += " tizen-extensions-crosswalk-system-info-demo "

tizen-extensions-crosswalk-bluetooth-demo_files = ""
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/bin/tizen-extensions-crosswalk-bluetooth-demo"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/packages/tizen-extensions-crosswalk-bluetooth-demo.xml"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/icons/default/small/tizen-extensions-crosswalk-bluetooth-demo.png"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/tizen/*.html"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/tizen/css/*.css"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/tizen/js/*.js"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/tizen/images/*.png"

tizen-extensions-crosswalk_files = ""
tizen-extensions-crosswalk_files += "${prefix}/bin/tizen-extensions-crosswalk"
tizen-extensions-crosswalk_files += "${prefix}/lib/tizen-extensions-crosswalk/libtizen*.so"

tizen-extensions-crosswalk-examples_files = ""
tizen-extensions-crosswalk-examples_files += "${prefix}/bin/tizen-extensions-crosswalk-examples"
tizen-extensions-crosswalk-examples_files += "${prefix}/share/packages/tizen-extensions-crosswalk-examples.xml"
tizen-extensions-crosswalk-examples_files += "${prefix}/share/icons/default/small/tizen-extensions-crosswalk-examples.png"
tizen-extensions-crosswalk-examples_files += "${prefix}/share/tizen-extensions-crosswalk/examples/*.html"
tizen-extensions-crosswalk-examples_files += "${prefix}/share/tizen-extensions-crosswalk/examples/js/*.js"

tizen-extensions-crosswalk-system-info-demo_files = ""
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/bin/tizen-extensions-crosswalk-system-info-demo"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/packages/tizen-extensions-crosswalk-system-info-demo.xml"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/icons/default/small/tizen-extensions-crosswalk-system-info-demo.png"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/system_info/*.html"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/system_info/css/*.css"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/system_info/js/*.js"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/system_info/images/*.png"

FILES_${PN}-bluetooth-demo = "${tizen-extensions-crosswalk-bluetooth-demo_files}"
FILES_${PN} = "${tizen-extensions-crosswalk_files}"
FILES_${PN}-examples = "${tizen-extensions-crosswalk-examples_files}"
FILES_${PN}-system-info-demo = "${tizen-extensions-crosswalk-system-info-demo_files}"

PKG_tizen-extensions-crosswalk-bluetooth-demo= "tizen-extensions-crosswalk-bluetooth-demo"
PKG_tizen-extensions-crosswalk= "tizen-extensions-crosswalk"
PKG_tizen-extensions-crosswalk-examples= "tizen-extensions-crosswalk-examples"
PKG_tizen-extensions-crosswalk-system-info-demo= "tizen-extensions-crosswalk-system-info-demo"

require tizen-extensions-crosswalk-extraconf.inc
