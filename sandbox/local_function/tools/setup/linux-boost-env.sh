
# Copyright (C) 2009-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://www.boost.org/libs/local_function

export BOOST_ROOT="$HOME/sandbox/boost-trunk.linux"
export BOOST_BUILD_PATH="$BOOST_ROOT/tools/build/v2"
export PATH="$BOOST_BUILD_PATH/engine/bin.linuxx86:$PATH"

echo "HOME=$HOME"
echo "BOOST_ROOT=$BOOST_ROOT"
echo "BOOST_BUILD_PATH=$BOOST_BUILD_PATH"
echo
echo "Make sure your \"$HOME/user-config.jam\" exists and it is correct."

