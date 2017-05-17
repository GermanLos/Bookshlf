
#ifndef LIB_AVL_TREE_ITERATOR
#define LOB_AVL_TREE_ITERATOR

#include "avltreenode.h"

namespace Lib
{
	template <typename K, typename V>
	class AvlTree;

	template <typename K, typename V>
	class AvlTreeIterator
	{
	public:
		AvlTreeIterator() : m_node(nullptr)
		{ }

		AvlTreeIterator(const AvlTreeIterator<K, V>& node);

		AvlTreeIterator(TreeNode<K, V>* node);

		~AvlTreeIterator()
		{ }


		bool operator==(const AvlTreeIterator<K, V>& rNode)
			const;
		bool operator!=(const AvlTreeIterator<K, V>& rNode)
			const;

		TreeNode<K, V>& operator++();
		TreeNode<K, V>& operator++(int);

		//TreeNode<K, V>& operator--();
		//TreeNode<K, V>& operator--(int);

		V& operator*() const;

	private:
		TreeNode<K, V>* m_node;

		friend class AvlTree<K, V>;
	};



	template<typename K, typename V>
	AvlTreeIterator<K, V>::AvlTreeIterator(const AvlTreeIterator<K, V> &node)
	{
		m_node = node.m_node;
	}

	template<typename K, typename V>
	AvlTreeIterator<K, V>::AvlTreeIterator(TreeNode<K, V>* node)
	{
		m_node = node;
	}



	template<typename K, typename V>
	bool AvlTreeIterator<K, V>::operator==(const AvlTreeIterator<K, V>& rNode) const
	{
		return (this->m_node == rNode.m_node);
	}



	template<typename K, typename V>
	bool AvlTreeIterator<K, V>::operator!=(const AvlTreeIterator<K, V>& rNode) const
	{
		return !(this->operator==(rNode));
	}



	template<typename K, typename V>
	TreeNode<K, V>& AvlTreeIterator<K, V>::operator++()
	{
		if (m_node->right != nullptr)
		{
			m_node = m_node->right;

			while (m_node->left != nullptr)
			{
				m_node = m_node->left;
			}
		}
		else
		{
			TreeNode<K, V>* pNode = m_node->parent;
			while (pNode->parent != nullptr && m_node == pNode->right)
			{
				m_node = pNode;
				pNode = pNode->parent;
			}

			m_node = pNode;
		}

		return *m_node;
	}



	template<typename K, typename V>
	TreeNode<K, V>& AvlTreeIterator<K, V>::operator++(int)
	{
		auto temp = m_node;
		operator++();
		return temp;
	}



	template<typename K, typename V>
	inline V & AvlTreeIterator<K, V>::operator*() const
	{
		return m_node->value;
	}



}

#endif // !LIB_AVL_TREE_ITERATOR
