#ifndef TRIPLECOMPOUNDKEY_H
#define TRIPLECOMPOUNDKEY_H

#include "compoundkey.h"

namespace Lib
{
	template <typename K1, typename K2, typename K3>
	class TripleCompoundKey : public CompoundKey<K1, K2>
	{
	public:
		TripleCompoundKey() :
			CompoundKey<K1, K2>(), m_k3()
		{ }

		TripleCompoundKey(K1 k1, K2 k2, K3 k3) :
			CompoundKey<K1, K2>(k1, k2), m_k3(k3)
		{ }

		virtual bool operator<(const TripleCompoundKey& other) const;
		virtual bool operator>(const TripleCompoundKey& other) const;
		virtual bool operator==(const TripleCompoundKey& other) const;
		virtual bool operator!=(const TripleCompoundKey& other) const;


	protected:
		K3 m_k3;
	};



	template<typename K1, typename K2, typename K3>
	bool TripleCompoundKey<K1, K2, K3>::operator<(const TripleCompoundKey<K1, K2, K3> &other) const
	{
		const CompoundKey<K1, K2> leftKey = *this;
		const CompoundKey<K1, K2> rightKey = other;


		if (leftKey == rightKey)
		{
			return (this->m_k3 < other.m_k3);
		}
		else if (leftKey < rightKey)
		{
			return true;
		}
		return false;
	}



	template<typename K1, typename K2, typename K3>
	bool TripleCompoundKey<K1, K2, K3>::operator>(const TripleCompoundKey<K1, K2, K3> &other) const
	{
		const CompoundKey<K1, K2> leftKey = *this;
		const CompoundKey<K1, K2> rightKey = other;


		if (leftKey == rightKey)
		{
			return (this->m_k3 > other.m_k3);
		}
		else if (leftKey > rightKey)
		{
			return true;
		}
		return false;
	}



	template<typename K1, typename K2, typename K3>
	bool TripleCompoundKey<K1, K2, K3>::operator==(const TripleCompoundKey<K1, K2, K3> &other) const
	{
		return (this->m_k1 == other.m_k1 &&
			this->m_k2 == other.m_k2 &&
			this->m_k3 == other.m_k3);
	}



	template<typename K1, typename K2, typename K3>
	bool TripleCompoundKey<K1, K2, K3>::operator!=(const TripleCompoundKey<K1, K2, K3> &other) const
	{
		return !(*this == other);
	}

}
#endif // TRIPLECOMPOUNDKEY_H
