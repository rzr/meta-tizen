require libmm-fileinfo.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/platform/core/multimedia/libmm-fileinfo;tag=0fa1c04c6047e41a8e221c603e65d12858fde559;nobranch=1"

BBCLASSEXTEND += " native "

