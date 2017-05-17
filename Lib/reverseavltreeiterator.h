
#ifndef LIB_REVERSE_AVL_TREE_ITERATOR
#define LIB_REVERSE_AVL_TREE_ITERATOR

#include "avltreenode.h"

namespace Lib
{
	template <typename K, typename V>
	class AvlTree;

	template <typename K, typename V>
	class ReverseAvlTreeIterator
	{
	public:
		ReverseAvlTreeIterator() : m_node(nullptr)
		{ }

		ReverseAvlTreeIterator(const ReverseAvlTreeIterator<K, V>& node);

		ReverseAvlTreeIterator(TreeNode<K, V>* node);

		~ReverseAvlTreeIterator()
		{ }


		bool operator==(const ReverseAvlTreeIterator<K, V>& rNode)
			const;
		bool operator!=(const ReverseAvlTreeIterator<K, V>& rNode)
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
	ReverseAvlTreeIterator<K, V>::ReverseAvlTreeIterator(const ReverseAvlTreeIterator<K, V>& node)
	{
		m_node = node.m_node;
	}

	template<typename K, typename V>
	ReverseAvlTreeIterator<K, V>::ReverseAvlTreeIterator(TreeNode<K, V>* node)
	{
		m_node = node;
	}



	template<typename K, typename V>
	bool ReverseAvlTreeIterator<K, V>::operator==(const ReverseAvlTreeIterator<K, V>& rNode) const
	{
		return (this->m_node == rNode.m_node);
	}



	template<typename K, typename V>
	bool ReverseAvlTreeIterator<K, V>::operator!=(const ReverseAvlTreeIterator<K, V>& rNode) const
	{
		return !(this->operator==(rNode));
	}



	template<typename K, typename V>
	TreeNode<K, V>& ReverseAvlTreeIterator<K, V>::operator++()
	{
		if (m_node->left != nullptr)
		{
			m_node = m_node->left;

			while (m_node->right != nullptr)
			{
				m_node = m_node->right;
			}
		}
		else
		{
			TreeNode<K, V>* lNode = m_node->parent;
			while (lNode->parent != nullptr && m_node == lNode->left)
			{
				m_node = lNode;
				lNode = lNode->parent;
			}

			m_node = lNode;
		}

		return *m_node;
	}



	template<typename K, typename V>
	TreeNode<K, V>& ReverseAvlTreeIterator<K, V>::operator++(int)
	{
		auto temp = m_node;
		operator++();
		return temp;
	}



	template<typename K, typename V>
	inline V & ReverseAvlTreeIterator<K, V>::operator*() const
	{
		return m_node->value;
	}



}

#endif // !LIB_REVERSE_AVL_TREE_ITERATOR
