
#ifndef _LIB_LIST_
#define _LIB_LIST_

#include "listiterator.h"
#include "constlistiterator.h"
#include "reverselistiterator.h"


namespace Lib
{
	template <typename T>
	class List
	{
	public:
		typedef ListIterator<T> iterator;
		typedef ConstListIterator<T> const_iterator;
		typedef ReverseListIterator<T> reverse_iterator;

		List() : m_begin(nullptr), m_end(nullptr),
					listSize(0)
		{ }

		//List(const List<T>& other)
		//{ }

		~List()
		{ clear(); }

		// Non const main functions:
		void push_back(const T&);
		void push_front(const T&);
		void pop_back();
		void pop_front();
		void remove(ListIterator<T>&);
        void clear();

		// Const main functions:
		const T& back() const;
		const T& front() const;
		
		// Const help functions:
		size_t size() const;
		bool isEmpty() const;

		// For iterators:
		ListIterator<T> begin() const;
		ListIterator<T> end() const;
		const ConstListIterator<T> cBegin() const;
		const ConstListIterator<T> cEnd() const;
		ReverseListIterator<T> rBegin() const;
		ReverseListIterator<T> rEnd() const;


	private:
		// Basic data:
		ListNode<T>* m_begin;
		ListNode<T>* m_end;

		// Help data:
		size_t listSize;
	};


	
	template <typename T>
	void List<T>::push_back(const T& object)
	{
		ListNode<T>* newElement = new ListNode<T>();
		newElement->value = object;
		newElement->next = nullptr;
		newElement->prew = m_end;

		if (isEmpty())
		{
			m_begin = newElement;
		}
		else
		{
			m_end->next = newElement;
		}

		m_end = newElement;
		++listSize;
	}



	template <typename T>
	void List<T>::push_front(const T& object)
	{
		ListNode<T>* newElement = new ListNode<T>();
		newElement->value = object;
		newElement->next = m_begin;
		newElement->prew = nullptr;

		if (isEmpty())
		{
			m_end = newElement;
		}
		else
		{
			m_begin->prew = newElement;
		}

		m_begin = newElement;
		++listSize;
	}



	template <typename T>
	void List<T>::pop_back()
	{
		if (isEmpty())
		{
			return;
		}
		
		ListNode<T>* temp = m_end;
		if (m_end->prew != nullptr)
		{
			m_end->prew->next = nullptr;
		}
		else
		{
			m_begin = nullptr;
		}

		m_end = m_end->prew;

		delete temp;
		--listSize;
	}



	template <typename T>
	void List<T>::pop_front()
	{
		if (isEmpty())
		{
			return;
		}

		ListNode<T>* temp = m_begin;
		if (m_begin->next != nullptr)
		{
			m_begin->next->prew = nullptr;
		}
		else
		{
			m_end = nullptr;
		}

		m_begin = m_begin->next;

		delete temp;
		--listSize;
	}



	template<typename T>
	void List<T>::remove(ListIterator<T>& iter)
	{
		if (iter.m_node->prew != nullptr)
		{
			iter.m_node->prew->next = iter.m_node->next;
		}
		else
		{
			m_begin = iter.m_node->next;
		}

		if (iter.m_node->next != nullptr)
		{
			iter.m_node->next->prew = iter.m_node->prew;
		}
		else
		{
			m_end = iter.m_node->prew;
		}

		delete iter.m_node;

        --listSize;
    }



    template<typename T>
    void List<T>::clear()
    {
        for (auto iter = begin();
             iter != end(); ++iter)
        {
            remove(iter);
        }
    }



	template <typename T>
	const T& List<T>::back() const
	{
		return m_end->value;
	}



	template <typename T>
	const T& List<T>::front() const
	{
		return m_begin->value;
	}



	template <typename T>
	size_t List<T>::size() const
	{
		return listSize;
	}



	template <typename T>
	bool List<T>::isEmpty() const
	{
		return (listSize ? 0 : 1);
	}
	
	
	
	template<typename T>
	inline ListIterator<T> List<T>::begin() const
	{
		return ListIterator<T>(m_begin);
	}



	template<typename T>
	inline ListIterator<T> List<T>::end() const
	{
		return ListIterator<T>();
	}



	template<typename T>
	inline const ConstListIterator<T> List<T>::cBegin() const
	{
		return ConstListIterator<T>(m_begin);
	}



	template<typename T>
	inline const ConstListIterator<T> List<T>::cEnd() const
	{
		return ConstListIterator<T>();
	}



	template<typename T>
	inline ReverseListIterator<T> List<T>::rBegin() const
	{
		return ReverseListIterator<T>(m_end);
	}



	template<typename T>
	inline ReverseListIterator<T> List<T>::rEnd() const
	{
		return ReverseListIterator<T>();
	}
}

#endif // !_LIB_LIST_

