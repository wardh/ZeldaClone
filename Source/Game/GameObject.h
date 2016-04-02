#pragma once
#include "../Common Utilities/Matrix.h"
#include "../Common Utilities/Observer.h"
#include "Component.h"
#include "OpaqueDictionary.h"

enum class eGameObjectType
{
	PLAYER,
	ENEMY,
	TILE
};


class GameObject : CU::Observer
{
public:
	GameObject();
	GameObject(const std::string& aGameObjectId, const std::string& aTag);

	~GameObject();

	void Update();
	virtual bool HandleEvent(const CU::Event& anEvent);
	//void HandleInternalEvent(const CU::Event& anEvent);
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent);
	void AddComponent(Component* aComponent);

	void Destroy();

	void SetPosition(const Vector2<float>& aPosition);
	const Vector2<float> GetPosition() const;
	void SetSpace(const Matrix33<float>& aSpace);
	const Matrix33<float>& GetSpace() const;
	const std::string& GetTag() const;

	const bool& GetShouldBeRemoved() const;
	void SetShouldBeRemoved(const bool& aTruth);

	GameObject& operator=(const GameObject& aGameObject);

	template<typename value>
	void SetValue(const std::string& aKey, const value& aValue);

	template<typename value>
	const value& GetValue(const std::string& aKey) const;

	template<typename value>
	const bool ValueExists(const std::string& aKey) const;

private:

	std::string myGameObjectID;
	std::string myTag;
	Matrix33<float> mySpace;
	CU::GrowingArray<Component*> myComponents;
	CU::OpaqueDictionary<std::string, 128> myComponentData;
	bool myShouldBeRemoved;
};

template<typename value>
void GameObject::SetValue(const std::string& aKey, const value& aValue)
{
	myComponentData.SetValue(aKey, aValue);
}

template<typename value>
const value& GameObject::GetValue(const std::string& aKey) const
{
	return myComponentData.GetValue<value>(aKey);
}


template<typename value>
const bool GameObject::ValueExists(const std::string& aKey) const
{
	return myComponentData.ValueExists<value>(aKey);
}