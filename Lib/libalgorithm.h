
#ifndef _LIB_ALGORITHM_
#define _LIB_ALGORITHM_

#include "list.h"


namespace Lib 
{
	template <typename StructureIterator>
	StructureIterator at(StructureIterator first, StructureIterator last, 
						 size_t index)
	{
		size_t counter = 0;

		for (first; first != last; ++first)
		{
			if (counter == index)
			{
				break;
			}
			++counter;
		}

		return first;
	}



	template <typename StructureItrator, typename Structure>
	void removeAt(StructureItrator first, StructureItrator last,
				  Structure& structure, size_t index)
	{
		size_t counter = 0;

		for (first; first != last; ++first)
		{
			if (counter == index)
			{
				structure.remove(first);
				break;
			}
			++counter;
		}
	}
}


#endif // !_LIB_ALGORITHM_

