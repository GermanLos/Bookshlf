
#ifndef _LIB_CONST_LIST_ITERATOR_
#define _LIB_CONST_LIST_ITERATOR_

#include "listnode.h"

namespace Lib
{
	template <typename T>
	class List;

	template <typename T>
	class ConstListIterator
	{
	public:
		ConstListIterator() : m_node(nullptr)
		{ }

		ConstListIterator(const ListNode<T>* other) :
			m_node(other)
		{ }

		~ConstListIterator()
		{ }


		// Comparsion operators:
		bool operator==(const ConstListIterator<T>& other) const;
		bool operator!=(const ConstListIterator<T>& other) const;
		bool operator<(const ConstListIterator<T>& other) const;
		bool operator>(const ConstListIterator<T>& other) const;

		// Increment and decrement operators:
		const ConstListIterator<T>& operator++();
		const ConstListIterator<T> operator++(int);

		// Help operator:
		const T& operator*() const;


	private:
		const ListNode<T>* m_node;

		friend class List<T>;
	};



	template<typename T>
	inline bool ConstListIterator<T>::operator==(const ConstListIterator<T>& other) const
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
	inline bool ConstListIterator<T>::operator!=(const ConstListIterator<T>& other) const
	{
		return !(this->operator==(other));
	}



	template<typename T>
	inline bool ConstListIterator<T>::operator<(const ConstListIterator<T>& other) const
	{
		return (this->m_node->value < other.m_node->value);
	}



	template<typename T>
	inline bool ConstListIterator<T>::operator>(const ConstListIterator<T>& other) const
	{
		return (this->m_node->value > other.m_node->value);
	}



	template<typename T>
	inline const ConstListIterator<T>& ConstListIterator<T>::operator++()
	{
		m_node = m_node->next;
		return *this;
	}



	template<typename T>
	inline const ConstListIterator<T> ConstListIterator<T>::operator++(int)
	{
		ConstListIterator<T> temp = *this;
		this->operator++();
		return temp;
	}



	template<typename T>
	inline const T& ConstListIterator<T>::operator*() const
	{
		return m_node->value;
	}
}

#endif // !_LIB_CONST_LIST_ITERATOR_

