
#ifndef LIB_AVL_TREE
#define LIB_AVL_TREE

#include "avltreeiterator.h"
#include "reverseavltreeiterator.h"

namespace Lib
{
	enum TREE_EXCEPTIONS
	{
		NOT_FOUND,
		SMTH_ELSE	// TODO?
	};



	template <typename K, typename V>
	class AvlTree
	{
	public:
		typedef AvlTreeIterator<K, V> iterator;
        typedef ReverseAvlTreeIterator<K, V> reverse_iterator;

		AvlTree() : m_root(nullptr), treeSize(0) 
		{ }

		AvlTree(AvlTree& other)
		{
			for (auto iter = other.begin(); iter != other.end(); ++iter)
			{
				this->insert(iter.m_node->key, iter.m_node->value);
			}
		}

		~AvlTree()
		{ clear(); }

		void insert(const K& key, const V& value);

		void remove(const K& key);
		void remove(AvlTreeIterator<K, V>& iter);
		void clear();

		V& find(const K& key);

		// Methods for work with iterators.
		AvlTreeIterator<K, V> begin() const;
		AvlTreeIterator<K, V> end() const;
		ReverseAvlTreeIterator<K, V> rBegin() const;
		ReverseAvlTreeIterator<K, V> rEnd() const;

		// Public help functions:
		TreeNode<K, V>* getMin(TreeNode<K, V>* node) const;
		TreeNode<K, V>* getMax(TreeNode<K, V>* node) const;
		size_t size() const;


	private:
		// INSERT, FIND, REMOVE:
		TreeNode<K, V>* insert(TreeNode<K, V>* node, const K& key, const V& value);

		TreeNode<K, V>* find(TreeNode<K, V>* node, const K& key) const;

		TreeNode<K, V>* remove(TreeNode<K, V>* node, const K& key);

		void clear(TreeNode<K, V>* node);

		// Balance functions:
		// Main balance function.
		TreeNode<K, V>* balancing(TreeNode<K, V>* node);

		// Left and right rotation.
		TreeNode<K, V>* leftRotation(TreeNode<K, V>* node);
		TreeNode<K, V>* rightRotation(TreeNode<K, V>* node);

		// Help functions:
		unsigned char level(TreeNode<K, V>* node) const;
		void fixLevel(TreeNode<K, V>* node);

		// Data:
		TreeNode<K, V>* m_root;

		size_t treeSize;
	};



	// PUBLIC:

	template<typename K, typename V>
	void AvlTree<K, V>::insert(const K & key, const V & value)
	{
		m_root = insert(m_root, key, value);
	}



	template<typename K, typename V>
	inline void AvlTree<K, V>::remove(const K & key)
	{
		m_root = remove(m_root, key);
	}



	template<typename K, typename V>
	inline void AvlTree<K, V>::remove(AvlTreeIterator<K, V>& iter)
	{
		m_root = remove(m_root, iter.m_node->key);
	}



	template<typename K, typename V>
	inline void AvlTree<K, V>::clear()
	{
        clear(m_root);
		m_root = nullptr;
		treeSize = 0;
	}



	template<typename K, typename V>
	V& AvlTree<K, V>::find(const K& key)
	{
		return find(m_root, key)->value;
	}



	template<typename K, typename V>
	AvlTreeIterator<K, V> AvlTree<K, V>::begin() const
	{
		return AvlTreeIterator<K, V>(getMin(m_root));
	}



	template<typename K, typename V>
	AvlTreeIterator<K, V> AvlTree<K, V>::end() const
	{
		return AvlTreeIterator<K, V>();
	}

	template<typename K, typename V>
	inline ReverseAvlTreeIterator<K, V> AvlTree<K, V>::rBegin() const
	{
		return ReverseAvlTreeIterator<K, V>(getMax(m_root));
	}

	template<typename K, typename V>
	inline ReverseAvlTreeIterator<K, V> AvlTree<K, V>::rEnd() const
	{
		return ReverseAvlTreeIterator<K, V>();
	}



	// PRIVATE:

	template<typename K, typename V>
	TreeNode<K, V>* AvlTree<K, V>::insert(TreeNode<K, V>* node, const K & key, const V & value)
	{
		// Add tree node.
		static TreeNode<K, V>* currentParent;
		if (node == m_root)
		{
			currentParent = nullptr;
		}

		if (node == nullptr)
		{
			node = new TreeNode<K, V>();
			node->parent = currentParent;
			node->left = nullptr;
			node->right = nullptr;
			node->key = key;
			node->value = value;
			node->level = 1;
			++treeSize;
		}
		else if (key == node->key)
		{
			node->value = value;
		}
		else
		{
			currentParent = node;

			if (key > node->key)
			{
				node->right = insert(node->right, key, value);
			}
			else
			{
				node->left = insert(node->left, key, value);
			}
		}

		// Now the recursion goes back.
		// Fixed node level.
		fixLevel(node);

		// Check the balance. If we need to balance.
		node = balancing(node);
		return node;
	}



	template<typename K, typename V>
	TreeNode<K, V>* AvlTree<K, V>::find(TreeNode<K, V>* node, const K & key) const
	{
		if (node == nullptr)
		{
			throw NOT_FOUND;
		}

		if (key == node->key)
		{
			return node;
		}

		return (key > node->key ? find(node->right, key) : find(node->left, key));
	}



	template<typename K, typename V>
	TreeNode<K, V>* AvlTree<K, V>::remove(TreeNode<K, V>* node, const K & key)
	{
		if (node == nullptr)
		{
			return node;
		}

		if (key == node->key)
		{
			// 0.
			if (node->left == nullptr && node->right == nullptr)
			{
				if (node->parent != nullptr)
				{
					if (node->key > node->parent->key)
					{
						node->parent->right = nullptr;
					}
					else
					{
						node->parent->left = nullptr;
					}
				}
				delete node;
				--treeSize;
				node = nullptr;
			}
			// 2.
			else if (node->left != nullptr && node->right != nullptr)
			{
				if (node->right->left == nullptr)
				{
					auto temp = node->right;
					node->key = temp->key;
					node->value = temp->value;
					node->right = temp->right;
					if (temp->right != nullptr)
					{
						temp->right->parent = node;
					}
					delete temp;
					--treeSize;
				}
				else
				{
					auto lNode = node->right;
					while (lNode->left != nullptr)
					{
						lNode = lNode->left;
					}

					node->key = lNode->key;
					node->value = lNode->value;
					remove(lNode, lNode->key);
				}
			}
			// 1.
			else
			{
				auto temp = (node->left != nullptr && node->right == nullptr ?
					node->left : node->right);
				node->key = temp->key;
				node->value = temp->value;
				node->left = temp->left;
				node->right = temp->right;
				if (temp->left != nullptr)
				{
					temp->left->parent = node;
				}
				if (temp->right != nullptr)
				{
					temp->right->parent = node;
				}
				delete temp;
				--treeSize;
			}
		}
		else
		{
			if (key > node->key)
			{
				node->right = remove(node->right, key);
			}
			else
			{
				node->left = remove(node->left, key);
			}
		}

		// Now the recursion goes back.
		// Fixed node level.
		fixLevel(node);

		// Check the balance. If we need to balance.
		node = balancing(node);

		return node;
	}



	template<typename K, typename V>
	void AvlTree<K, V>::clear(TreeNode<K, V>* node)
	{
		if (node != nullptr)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}



	template<typename K, typename V>
	TreeNode<K, V>* AvlTree<K, V>::balancing(TreeNode<K, V>* node)
	{
		if (node == nullptr)
		{
			return node;
		}

		// Get balance.
		char balance = (level(node->left) - level(node->right));

		// Balance node and fix children level.
		if (balance > 1)
		{
			node = rightRotation(node);
			fixLevel(node->right);
		}
		else if (balance < -1)
		{
			node = leftRotation(node);
			fixLevel(node->left);
		}

		// Fixed node level.
		fixLevel(node);

		return node;
	}



	template<typename K, typename V>
	TreeNode<K, V>* AvlTree<K, V>::leftRotation(TreeNode<K, V>* node)
	{
		auto tNode = node->right;
		tNode->parent = node->parent;
		node->parent = tNode;
		node->right = tNode->left;
		tNode->left = node;

		if (node->right != nullptr)
		{
			node->right->parent = node;
		}

		return tNode;
	}



	template<typename K, typename V>
	TreeNode<K, V>* AvlTree<K, V>::rightRotation(TreeNode<K, V>* node)
	{
		auto tNode = node->left;
		tNode->parent = node->parent;
		node->parent = tNode;
		node->left = tNode->right;
		tNode->right = node;

		if (node->left != nullptr)
		{
			node->left->parent = node;
		}

		return tNode;
	}



	template<typename K, typename V>
	unsigned char AvlTree<K, V>::level(TreeNode<K, V>* node) const
	{
		return (node != nullptr ? node->level : 0);
	}



	template<typename K, typename V>
	void AvlTree<K, V>::fixLevel(TreeNode<K, V>* node)
	{
		if (node == nullptr)
		{
			return;
		}

		node->level = (level(node->left) > level(node->right) ?
			level(node->left) : level(node->right)) + 1;
	}



	template<typename K, typename V>
	TreeNode<K, V>* AvlTree<K, V>::getMin(TreeNode<K, V>* node) const
	{
		return (node->left == nullptr ? node : getMin(node->left));
	}



	template<typename K, typename V>
	TreeNode<K, V>* AvlTree<K, V>::getMax(TreeNode<K, V>* node) const
	{
		return (node->right == nullptr ? node : getMax(node->right));
	}



	template<typename K, typename V>
	inline size_t AvlTree<K, V>::size() const
	{
		return treeSize;
	}
}

#endif // !LIB_AVL_TREE
