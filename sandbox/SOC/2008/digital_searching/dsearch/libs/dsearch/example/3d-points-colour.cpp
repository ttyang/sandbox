// Copyright 2008 Chintan Rao H.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include<boost/dsearch/patricia.hpp>
#include<iostream>
#include<vector>

using boost::dsearch::patricia;
using boost::dsearch::pat_vector_traits;

class colour {
	public:
	int R,B,G;
	colour() : R(0), B(0) ,G(0) 
	{
	}
};

int main(int argc, char** argv)
{
	typedef patricia<std::vector<int>, colour, pat_vector_traits<int> > pat_type;
	std::vector<int> coord(3);
	pat_type colour_cube;
	colour col;
	
	for(int i=0;i<256;i++)
	{
		coord[0]=col.R = i;
		for(int j=0;j<256;j++)
		{
			coord[1]=col.B = j;
			for(int k=0;k<256;k++)
			{
				coord[2]=col.G = k;
				colour_cube[coord]=col;
			}
		}
	}
	return 0;
}