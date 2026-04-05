# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================


if myxml_build_examples

    #===========================
    # C++ Library API Examples #
    #===========================

	myxml_examples = []

    foreach example : myxml_examples

		exe = executable(
                        example,
                        'apis/' + example,
                        include_directories: myxml_include_dirs,
                        dependencies: [myxml_dep],
            install: false
        )
        
	endforeach

    #===========================
    # C Library API Examples   #
    #===========================

	myxmlc_examples = []

    foreach example : myxmlc_examples

		exe = executable(
                        example + 'c',
            'apis/' + example,
                        include_directories: myxml_include_dirs,
                        dependencies: [myxmlc_dep],
            install: false
        )

	endforeach

endif

# ===================================================================
