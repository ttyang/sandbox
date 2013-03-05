
# Copyright (C) 2008-2013 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

import os

boost_dir = "../../../../boost"
scripts = [
    ("contract/detail/preprocessor/array", "first_n-generate.py"),
    ("contract/detail/preprocessor/array", "rest_n-generate.py"),
    ("contract/detail/preprocessor/facilities", "is_digit-generate.py"),
    ("contract/detail/preprocessor/traits/aux_", "apply-generate.py"),
    ("contract/detail/preprocessor/traits/aux_", "list-generate.py"),
    ("contract/detail/preprocessor/traits/aux_",
            "select_assertion_-generate.py"),
    ("contract/detail/preprocessor/traits/func", "catches-generate.py"),
    ("contract/detail/preprocessor/traits/func", "postconditions-generate.py"),
    ("contract/detail/preprocessor/tuple", "split-generate.py"),
    ("contract/detail/preprocessor/keyword", "generate.py"),
]

this_dir = os.getcwd()
for s in scripts:
    py_dir = s[0]
    py_name = s[1]
    header_dir = os.path.join(boost_dir, py_dir)
    for i in range(0, py_dir.count("/") + 1):
        header_dir = os.path.join("..", header_dir) 
    cmd = "python " + py_name + " " + header_dir
    print
    print "[" + py_dir + "]$ " + cmd
    os.chdir(py_dir)
    os.system(cmd)
    os.chdir(this_dir)

print
print "Done. (Add any missing generation Python script to this script.)",

