# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

#--------------------------------------------------------------------
# Project and version.
#--------------------------------------------------------------------

project('myxml',
	['c', 'cpp'],
	version : '0.1.0',
	license : 'MIT',
	default_options : [
		'buildtype=release',
		'default_library=static',
		],
  	subproject_dir: 'tests/vendor'
)

compiler = meson.get_compiler('cpp')
message('target cpu_family: @0@'.format(host_machine.cpu_family()))
message('target cpu: @0@'.format(host_machine.cpu()))
message('target system: @0@'.format(host_machine.system()))
message('target endian: @0@'.format(host_machine.endian()))

#--------------------------------------------------------------------
# Configure Project Variables.   
#--------------------------------------------------------------------

license = files('LICENSE')

myxml_is_subproject = meson.is_subproject()
myxml_include_dirs = include_directories('include')
myxml_build_tests = get_option('myxml_build_tests') and not myxml_is_subproject
myxml_build_examples = get_option('myxml_build_examples') and not myxml_is_subproject
myxml_install = get_option('myxml_install') and not myxml_is_subproject
myxml_build_c_api = get_option('myxml_build_c_api')

src_files = []

#--------------------------------------------------------------------
# Build Project Libraries.
#--------------------------------------------------------------------

#===========================
# Build C++ Library        #
#===========================

myxml_lib = library(
	'myxml',
	'src/myxml.cpp',
	include_directories : myxml_include_dirs,
	install : myxml_install,
)

#===========================
# Build C Library          #
#===========================

myxml_dep = declare_dependency(
	link_with : myxml_lib,
	include_directories : myxml_include_dirs,
)

myxmlc_dep = myxml_dep

if myxml_build_c_api
	myxmlc_lib = library(
		'myxmlc', 
		'src/myxmlc.cpp',
		include_directories : myxml_include_dirs,
		link_with : myxml_lib,
		install : myxml_install,
	)

	myxmlc_dep = declare_dependency(
		link_with : myxmlc_lib,
		include_directories : myxml_include_dirs,
	)
endif

#--------------------------------------------------------------------
# Add Project subdirectories.
#--------------------------------------------------------------------

if myxml_build_tests
	subdir('tests')
endif

if myxml_build_examples
	subdir('examples')
endif

#--------------------------------------------------------------------
# Install Project Packages.
#--------------------------------------------------------------------

if not meson.is_subproject()

	if myxml_install
		install_headers('include/myxml/myxml.h', subdir : 'myxml')
		install_headers('include/myxml/myxml.hpp', subdir : 'myxml')
	endif

	pkgc = import('pkgconfig')
	pkg_libraries = [myxml_lib]
	if myxml_build_c_api
		pkg_libraries += [myxmlc_lib]
	endif
	pkgc.generate(
		name : meson.project_name(),
		version: meson.project_version(),
		description: 'XML for Modern C/C++',
		url: 'https://github.com/djoezeke/myxml',
		libraries: pkg_libraries,
		subdirs : 'myxml',
	)

endif

# ===================================================================
