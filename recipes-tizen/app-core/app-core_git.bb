require app-core.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/platform/core/appfw/app-core;tag=5f1787bb00aeec0926b50780d7aeae081895c7cb;nobranch=1"

BBCLASSEXTEND += " native "

