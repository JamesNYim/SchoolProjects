#pragma once

#include <iostream>
#include <functional>

namespace cse 
{
    template<typename Iter, typename Cmp = std::less<>>
    void sort(Iter beg, Iter end, Cmp cmp = {}) 
    {
        // TODO
	for (auto first = beg; first != end; ++first)
	{
		for (auto second = first; second != end; ++second)
		{
			if (!cmp(*first, *second))	
			{			
				auto temp = *second;
				*second = *first;
				*first = temp;
			}
		}
	}
	return;
    }
}
