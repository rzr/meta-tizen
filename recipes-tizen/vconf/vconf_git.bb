require vconf.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/platform/core/appfw/vconf;tag=bb4b1ca3dd523ca1b0ab9add555a01179de8b069;nobranch=1"

BBCLASSEXTEND += " native "

