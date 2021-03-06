#! /usr/bin/env python
# -*- coding: utf-8 -*-
# ===========================================================================
#  Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.
# 
#  Use, modification and distribution is subject to the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt)9
# ============================================================================

import os, sys

cmd = "doxygen_xml2qbk"
cmd = cmd + " --xml xml/%s.xml"
cmd = cmd + " --start_include boost/"
cmd = cmd + " --output_style alt"
cmd = cmd + " > generated/%s.qbk"

os.system("doxygen Doxyfile")

os.system(cmd % ("classboost_1_1container_1_1varray", "varray"))
os.system(cmd % ("group__varray__non__member", "varray_non_member"))

os.system("b2") 
