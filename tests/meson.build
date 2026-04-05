# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

if myxml_build_tests
	catch2_include_dirs = include_directories('vendor/Catch2/src')

	catch2_dep = dependency(
		'catch2-with-main',
        fallback: ['Catch2', 'catch2_with_main_dep'],
		required: true
	)

    #===========================
    # C++ Library Tests        #
    #===========================

	myxml_test_sources = [
		'cxx/Main.test.cpp',
	]

	myxml_test_exe = executable(
		'myxml_cpp_tests', 
		myxml_test_sources,
		include_directories: [myxml_include_dirs, catch2_include_dirs],
		dependencies: [myxml_dep, catch2_dep], 
		install: false
	)

	test('myxml_cpp_tests', myxml_test_exe)

    #===========================
    # C Library Tests          #
    #===========================

	myxmlc_test_sources = [
		'c/Main.test.cpp'
	]

	myxmlc_test_exe = executable(
		'myxml_c_tests', 
		myxmlc_test_sources,
		include_directories: [myxml_include_dirs, catch2_include_dirs],
		dependencies: [myxmlc_dep, catch2_dep], 
		install: false
	)

	test('myxml_c_tests', myxmlc_test_exe)

endif

# ===================================================================
