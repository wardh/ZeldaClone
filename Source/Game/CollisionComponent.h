#pragma once
#include "../Common Utilities/Vector2.h"
#include "Component.h"

class CollisionBoxComponent;
struct CircleStruct;
class CollisionComponent : public Component
{
public:
	CollisionComponent(GameObject& aGameObject);
	CollisionComponent(GameObject& aGameObject, const Vector2<float>& aCenterPosition);

	~CollisionComponent();

	virtual bool CheckCollision(const Vector2<float>& aPosition) const = 0;
	virtual bool CheckCollision(const CollisionBoxComponent& aCollisionBox) const = 0;
	virtual bool CheckCollision(const CircleStruct& aCircle) const = 0;

	void SetPosition(const Vector2<float>& aPosition);
	const Vector2<float>& GetPosition() const;
	virtual void SetData() override;


protected:
	Vector2<float> myPosition;

private:

};

