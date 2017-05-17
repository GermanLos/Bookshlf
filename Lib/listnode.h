
#ifndef _LIB_LIST_NODE_
#define _LIB_LIST_NODE_

namespace Lib
{
	template <typename T>
	struct ListNode
	{
		T value;
		ListNode<T>* next;
		ListNode<T>* prew;

		ListNode() : value(), next(nullptr), prew(nullptr)
		{ }
	};
}

#endif // !_LIB_LIST_NODE_

