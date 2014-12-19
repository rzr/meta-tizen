# Inherit this class to package shared libraries separately.
#
# By default, all libraries will be in a lib${PN} package.
#
# To override that, set PKG_LIBS to a space-separated list of
# library base names (like "libfoo libbar"). This will create one
# package per lib, with that lib inside.
#
# The additional packages are automatically marked as containing
# libraries via SRPM_IS_LIB and put into the "libs" section.
#
# Summary and description are inherited from the main package. This
# can be changed by setting SUMMARY_<lib> and DESCRIPTION_<lib> for
# them. The FILES_<lib> variable can be set, in which case this class
# will not modify it at all.

# What generate_libs creates is similar to these variable assignments,
# except that is potentially done for multiple different libs:
#
# Split out all libs.
# PACKAGES =+ "lib${PN}"
#
# We extend the -dev runtime dependency instead of replacing
# it, because we do not know whether the other dependencies (usually
# the one on the main package) still matter. Besides, doing it
# via _remove would not work anyway, because that can only
# remove single words and not complex expressions like
# "${PN} = ${EXTENDEDPKGV}".
# RDEPENDS_${PN}-dev_append = " lib${PN} (= ${EXTENDPKGV})"
#
# FILES_lib{$PN} ?= "\
# ${libdir}/*.so.* \
# "
# SECTION_lib{$PN} ?= "libs"
#
# SRPM_IS_LIB += "lib${PN}"
def generate_libs(d):
    def add_lib(lib, files, d):
        d.prependVar('PACKAGES', '%s ' % lib)
        var = 'FILES_%s' % lib
        if d.getVar(var, True) is None:
            d.setVar(var, files)
        var = 'SECTION_%s' % lib
        if d.getVar(var, True) is None:
            d.setVar(var, 'libs')
        d.appendVar('RDEPENDS_%s-dev' % pn, (' %s (= $' + '{EXTENDPKGV})') % lib)
        d.appendVar('SRPM_IS_LIB', ' ' + lib)

    libs = d.getVar('PKG_LIBS', True)
    pn = d.getVar('PN', True)
    if libs:
        for lib in libs.split():
            add_lib(lib, ('$' + '{libdir}/%s.so.*') % lib, d)
    else:
        add_lib('lib' + pn, '$' + '{libdir}/*.so.*', d)

# Trigger code above after other code set up default packaging.
# When converting, the order does not really matter because populate_packages
# is empty.
python populate_packages_append () {
    generate_libs(d)
}