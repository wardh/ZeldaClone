#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	myComponents.Init(16);
	myShouldBeRemoved = false;
}

GameObject::GameObject(const std::string& aGameObjectId, const std::string& aTag)
{
	myComponents.Init(16);
	myGameObjectID = aGameObjectId;
	myTag = aTag;
	myShouldBeRemoved = false;
}

GameObject::~GameObject()
{
}

void GameObject::Destroy()
{
	for (unsigned short i = 0; i < myComponents.Size(); i++)
	{
		myComponents[i]->Destroy();
		SAFE_DELETE(myComponents[i])
	}
	myComponents.RemoveAll();
	myComponentData.Clear();
}

void GameObject::Update()
{
	for (unsigned short i = 0; i < myComponents.Size(); i++)
	{
		myComponents[i]->Update();
	}
}

bool GameObject::HandleEvent(const CU::Event& anEvent)
{
	switch (anEvent.GetMyType())
	{
	default:
		break;
	}
	return true;
}

bool GameObject::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	for (unsigned short i = 0; i < myComponents.Size(); i++)
	{
		if (myComponents[i]->HandleInternalEvent(anEvent) == false)
		{
			return false;
		}
	}
	return true;
}

//void GameObject::HandleInternalEvent(const CU::Event& anEvent)
//{
//	for (unsigned short i = 0; i < myComponents.Size(); i++)
//	{
//		myComponents[i]->HandleInternalEvent(anEvent);
//	}
//}

void GameObject::AddComponent(Component* aComponent)
{
	myComponents.Add(aComponent);
}

void GameObject::SetPosition(const Vector2<float>& aPosition)
{
	mySpace.SetPosition(aPosition);
}

const Vector2<float> GameObject::GetPosition() const
{
	return mySpace.GetPosition();
}

void GameObject::SetSpace(const Matrix33<float>& aSpace)
{
	mySpace = aSpace;
}

const Matrix33<float>& GameObject::GetSpace() const
{
	return mySpace;
}

const std::string& GameObject::GetTag() const
{
	return myTag;
}

const bool & GameObject::GetShouldBeRemoved() const
{
	return myShouldBeRemoved;
}

void GameObject::SetShouldBeRemoved(const bool & aTruth)
{
	myShouldBeRemoved = aTruth;
}

GameObject& GameObject::operator = (const GameObject& aGameObject)
{
	mySpace = aGameObject.mySpace;
	myComponents = aGameObject.myComponents;
	myTag = aGameObject.myTag;
	myGameObjectID = aGameObject.myGameObjectID;
	myShouldBeRemoved = aGameObject.myShouldBeRemoved;
	for (unsigned short i = 0; i < myComponents.Size(); i++)
	{
		myComponents[i]->SetParent(this);
		myComponents[i]->SetData();
	}
	return *this;
}