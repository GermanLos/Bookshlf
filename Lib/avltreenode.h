
#ifndef LIB_TREE_NODE
#define LIB_TREE_NODE

namespace Lib
{
	template <typename K, typename V>
	struct TreeNode
	{
		TreeNode<K, V>* parent;
		TreeNode<K, V>* left;
		TreeNode<K, V>* right;
		K key;
		V value;
		unsigned char level;
	};

}

#endif // !LIB_TREE_NODE
