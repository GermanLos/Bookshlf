
#ifndef _LIB_REVERSE_LIST_SORT_
#define _LIB_REVERSE_LIST_SORT_

#include "listnode.h"


namespace Lib
{
	template <typename T>
	class List;

	template <typename T>
	class ReverseListIterator
	{
	public:
		ReverseListIterator() : m_node(nullptr)
		{ }

		ReverseListIterator(ListNode<T>* other) :
			m_node(other)
		{ }

		~ReverseListIterator()
		{ }

		// Comparsion operators:
		bool operator==(const ReverseListIterator<T>& other) const;
		bool operator!=(const ReverseListIterator<T>& other) const;
		bool operator<(const ReverseListIterator<T>& other) const;
		bool operator>(const ReverseListIterator<T>& other) const;

		// Increment and decrement operators:
		ReverseListIterator<T>& operator++();
		ReverseListIterator<T> operator++(int);

		// Help operator:
		T& operator*() const;


	private:
		ListNode<T>* m_node;

		friend class List<T>;
	};



	template<typename T>
	inline bool ReverseListIterator<T>::operator==(const ReverseListIterator<T>& other) const
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
	inline bool ReverseListIterator<T>::operator!=(const ReverseListIterator<T>& other) const
	{
		return !(this->operator==(other));
	}



	template<typename T>
	inline bool ReverseListIterator<T>::operator<(const ReverseListIterator<T>& other) const
	{
		return (this->m_node->value < other.m_node->value);
	}



	template<typename T>
	inline bool ReverseListIterator<T>::operator>(const ReverseListIterator<T>& other) const
	{
		return (this->m_node->value > other.m_node->value);
	}



	template<typename T>
	inline ReverseListIterator<T>& ReverseListIterator<T>::operator++()
	{
		m_node = m_node->prew;
		return *this;
	}



	template<typename T>
	inline ReverseListIterator<T> ReverseListIterator<T>::operator++(int)
	{
		ReverseListIterator<T> temp = *this;
		this->operator++();
		return temp;
	}



	template<typename T>
	inline T& ReverseListIterator<T>::operator*() const
	{
		return m_node->value;
	}
}


#endif // !_LIB_REVERSE_LIST_SORT_
