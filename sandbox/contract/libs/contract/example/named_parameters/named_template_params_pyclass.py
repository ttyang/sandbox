
# Copyright (C) 2008-2013 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

import sys

print 'Importing module:', sys.argv[1]
pyclass = __import__(sys.argv[1]) # Import checks contracts (preconditions,etc).

# Check that objects are constructed successfully.
pyclass.x()
pyclass.y()

