#pragma once

#include <new>
#include <unordered_map>
#include <assert.h>
#include <typeinfo>

namespace CommonUtilities
{
	template<typename key, short MAXSIZE = 64>
	class OpaqueDictionary
	{
	public:
						OpaqueDictionary();
						~OpaqueDictionary();

		template<typename value>
		void				SetValue(const key& aKey, const value& aValue);

		template<typename value>
		const value&		GetValue(const key& aKey) const;

		template<typename value>
		const bool			ValueExists(const key& aKey) const;

		void				Clear();


	private:
		std::unordered_map <key, void*> myDataPointers;
		char myData[MAXSIZE];
		int myCurrentIndex;

#ifndef NDEBUG
		std::unordered_map < key, const std::type_info* >
							myDataTypes;
#endif	
	};

	template<typename key, short MAXSIZE>
	OpaqueDictionary<key, MAXSIZE>::OpaqueDictionary()
	{
		myCurrentIndex = 0;
	}

	template<typename key, short MAXSIZE>
	OpaqueDictionary<key, MAXSIZE>::~OpaqueDictionary()
	{

	}

	template<typename key, short MAXSIZE>
	void OpaqueDictionary<key, MAXSIZE>::Clear()
	{
		myCurrentIndex = 0;
		myDataPointers.clear();

#ifndef NDEBUG
		myDataTypes.clear();
#endif
	}

	template<typename key, short MAXSIZE>
	template<typename value>
	void OpaqueDictionary<key, MAXSIZE>::SetValue(const key& aKey, const value& aValue)
	{
		assert(myCurrentIndex + sizeof(value) < MAXSIZE && "Error! Not enough memory in OpaqueDictionary!");
		auto it = myDataPointers.find(aKey);

		if (it == myDataPointers.end())
		{
			myDataPointers[aKey] = new (&myData[myCurrentIndex]) value(aValue);

			myCurrentIndex += sizeof(value);

#ifndef NDEBUG
			myDataTypes[aKey] = &typeid(value);
#endif
		}
		else
		{
			assert(typeid(value) == *myDataTypes[aKey] && "OpaqueDictionary: Trying to set a value to a different type than it was created with!");
			*(reinterpret_cast<value*>((*it).second)) = aValue;
		}
	}


	template<typename key, short MAXSIZE>
	template<typename value>
	const value& OpaqueDictionary<key, MAXSIZE>::GetValue(const key& aKey) const
	{
#ifndef NDEBUG
		auto type = myDataTypes.find(aKey);
		assert(type != myDataTypes.end() && "Key not found in Opaque Dictionary!");
		assert(typeid(value) == *(*type).second && "Incorrect type!");
#endif

		auto it = myDataPointers.find(aKey);
		assert(it != myDataPointers.end() && "Key not found in Opaque Dictionary!");
		return *(reinterpret_cast<value*>((*it).second));
	}

	template<typename key, short MAXSIZE>
	template<typename value>
	const bool OpaqueDictionary<key, MAXSIZE>::ValueExists(const key& aKey) const
	{

	/*	auto type = myDataTypes.find(aKey);
		if (type != myDataTypes.end())
		{
			return true;
		}
		else
		{
			return false;
		}*/
		auto it = myDataPointers.find(aKey);
		if (it != myDataPointers.end())
		{
			return true;
		}
		return false;
	}
}

namespace CU = CommonUtilities;