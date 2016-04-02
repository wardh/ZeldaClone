#pragma once

#include "BaseObjectPool.h"

#define OOP_TEMPLATE template<typename Type>
#define OOP_OBJECT ObjectPoolPointer<Type>

namespace CommonUtilities
{

	OOP_TEMPLATE
	class ObjectPoolPointer
	{
		friend class ObjectPool;
	public:
		
		~ObjectPoolPointer();
		Type& operator->();
		ObjectPoolPointer& operator=(const ObjectPoolPointer& aPoolPointer);
	private:
		ObjectPoolPointer();
		ObjectPoolPointer(BaseObjectPool* aParent, const unsigned int aMemoryID);

		BaseObjectPool* myObjectPool

		unsigned int myMemoryID;

	};

	OOP_TEMPLATE
		OOP_OBJECT::ObjectPoolPointer::ObjectPoolPointer()
	{

	}

	OOP_TEMPLATE
		OOP_OBJECT::ObjectPoolPointer::~ObjectPoolPointer()
	{
		myObjectPool->SubtractPointerCount(myMemoryID);
	}

	OOP_TEMPLATE
		OOP_OBJECT::ObjectPoolPointer::ObjectPoolPointer(BaseObjectPool* aParent, const unsigned int aMemoryID)
	{
		myObjectPool = aParent;
		myMemoryID = aMemoryID;
		aParent->AddPointerCount(myMemoryID);
	}

	OOP_TEMPLATE
		OOP_OBJECT& OOP_OBJECT::operator=(const ObjectPoolPointer& aPoolPointer)
	{
		this = ObjectPoolPointer(myParent, aPoolPointer);
		return this;
	}

		OOP_TEMPLATE
		Type& OOP_OBJECT::operator->()
	{
			return myObjectPool->GetData(myMemoryID);
	}
}

#undef OOP_TEMPLATE
#undef OOP_OBJECT

namespace CU = CommonUtilities;