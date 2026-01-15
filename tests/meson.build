# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

if myxml_build_tests

    #===========================
    # C++ Library Tests        #
    #===========================

	myxml_test_sources = [
		'cxx/Version.test.cpp'
	]

	myxml_test_exe = executable(
		myxml_test, 
		myxml_test_sources,
		include_directories: myxml_include_dirs,
		link_with: [myxml_lib], 
		install: false
	)

	test(myxml_test, myxml_test_exe)

    #===========================
    # C Library Tests          #
    #===========================

	myxmlc_test_sources = [
		'c/Version.test.cpp'
	]

	myxmlc_test_exe = executable(
		myxmlc_test, 
		myxmlc_test_sources,
		include_directories: myxml_include_dirs,
		link_with: [myxmlc_lib], 
		install: false
	)

	test(myxmlc_test, myxmlc_test_exe)

endif

# ===================================================================
