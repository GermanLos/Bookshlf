
#ifndef _LIB_LIST_ITERATOR_
#define _LIB_LIST_ITERATOR_

#include "listnode.h"

namespace Lib
{
	template <typename T>
	class List;

	template <typename T>
	class ListIterator
	{
	public:
		ListIterator() : m_node(nullptr)
		{ }

		ListIterator(ListNode<T>* other) :
			m_node(other)
		{ }

		~ListIterator()
		{ }

		// Comparsion operators:
		bool operator==(const ListIterator<T>& other) const;
		bool operator!=(const ListIterator<T>& other) const;
		bool operator<(const ListIterator<T>& other) const;
		bool operator>(const ListIterator<T>& other) const;

		// Increment and decrement operators:
		ListIterator<T>& operator++();
		ListIterator<T> operator++(int);

		// Help operator:
		T& operator*() const;


	private:
		ListNode<T>* m_node;

		friend class List<T>;
	};



	template<typename T>
	inline bool ListIterator<T>::operator==(const ListIterator<T>& other) const
	{
		if (this->m_node != nullptr && other.m_node != nullptr)
		{
			return this->m_node->value == other.m_node->value;
		}
		else
		{
			return this->m_node == other.m_node;
		}
	}



	template<typename T>
	inline bool ListIterator<T>::operator!=(const ListIterator<T>& other) const
	{
		return !(this->operator==(other));
	}



	template<typename T>
	inline bool ListIterator<T>::operator<(const ListIterator<T>& other) const
	{
		return (this->m_node->value < other.m_node->value);
	}



	template<typename T>
	inline bool ListIterator<T>::operator>(const ListIterator<T>& other) const
	{
		return (this->m_node->value > other.m_node->value);
	}



	template<typename T>
	inline ListIterator<T>& ListIterator<T>::operator++()
	{
		m_node = m_node->next;
		return *this;
	}



	template<typename T>
	inline ListIterator<T> ListIterator<T>::operator++(int)
	{
		ListIterator<T> temp = *this;
		this->operator++();
		return temp;
	}



	template<typename T>
	inline T& ListIterator<T>::operator*() const
	{
		return m_node->value;
	}
}

#endif // !_LIB_LIST_ITERATOR_

