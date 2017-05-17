
#ifndef COMPOUNDKEY_H
#define COMPOUNDKEY_H

namespace Lib
{
	template <typename K1, typename K2>
	class CompoundKey
	{
	public:
		CompoundKey() :
			m_k1(), m_k2()
		{ }

		CompoundKey(const K1& k1, const K2 k2) :
			m_k1(k1), m_k2(k2)
		{ }

		virtual ~CompoundKey()
		{ }

		virtual bool operator<(const CompoundKey& other) const;
		virtual bool operator>(const CompoundKey& other) const;
		virtual bool operator==(const CompoundKey& other) const;
		virtual bool operator!=(const CompoundKey& other) const;

	protected:
		K1 m_k1;
		K2 m_k2;
	};



	template<typename K1, typename K2>
	bool CompoundKey<K1, K2>::operator<(const CompoundKey<K1, K2>& other) const
	{
		if (this->m_k1 == other.m_k1)
		{
			return (this->m_k2 < other.m_k2);
		}
		else if (this->m_k1 < other.m_k1)
		{
			return true;
		}
		return false;
	}



	template<typename K1, typename K2>
	bool CompoundKey<K1, K2>::operator>(const CompoundKey<K1, K2> &other) const
	{
		if (this->m_k1 == other.m_k1)
		{
			return (this->m_k2 > other.m_k2);
		}
		else if (this->m_k1 > other.m_k1)
		{
			return true;
		}
		return false;
	}



	template<typename K1, typename K2>
	bool CompoundKey<K1, K2>::operator==(const CompoundKey<K1, K2> &other) const
	{
		return (this->m_k1 == other.m_k1 && this->m_k2 == other.m_k2);
	}



	template<typename K1, typename K2>
	bool CompoundKey<K1, K2>::operator!=(const CompoundKey<K1, K2> &other) const
	{
		return !(this->operator==(other));
	}



}


#endif // COMPOUNDKEY_H
