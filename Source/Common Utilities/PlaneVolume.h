#pragma once
#include "Plane.h"
#include "Vector.h"
#include <vector>

#define PLANE_VOLUME_TEMPLATE template <typename Type>
#define PLANE_VOLUME_OBJECT PlaneVolume<Type>


PLANE_VOLUME_TEMPLATE
class PlaneVolume
{
public:
	PlaneVolume();
	~PlaneVolume();

	PlaneVolume(std::vector<Plane<Type>> aPlaneList);
	void AddPlane(Plane<Type> aPlane);
	void RemovePlane(Plane<Type> aPlane);
	bool Inside(Vector3<Type> aPosition);
private:
	std::vector<Plane<Type>> myPlaneList;
};


PLANE_VOLUME_TEMPLATE
PLANE_VOLUME_OBJECT::PlaneVolume()
{

}

PLANE_VOLUME_TEMPLATE
PLANE_VOLUME_OBJECT::~PlaneVolume()
{

}

PLANE_VOLUME_TEMPLATE
PLANE_VOLUME_OBJECT::PlaneVolume(std::vector<Plane<Type>> aPlaneList)
{
	for (unsigned int i = 0; i < aPlaneList.size(); i++)
	{
		myPlaneList.push_back(aPlaneList.at(i));
	}
}

PLANE_VOLUME_TEMPLATE
void PLANE_VOLUME_OBJECT::AddPlane(Plane<Type> aPlane)
{
	myPlaneList.push_back(aPlane);
}

PLANE_VOLUME_TEMPLATE
void PLANE_VOLUME_OBJECT::RemovePlane(Plane<Type> aPlane)
{
	for (unsigned int i = 0; i < myPlaneList.size(); i++)
	{
		if (myPlaneList.at(i) == aPlane)
		{
			myPlaneList.at(i) = myPlaneList.at(myPlaneList.size() - 1);
			myPlaneList.pop_back();
			break;
		}
	}
}

PLANE_VOLUME_TEMPLATE
bool PLANE_VOLUME_OBJECT::Inside(Vector3<Type> aPosition)
{
	for (unsigned int i = 0; i < myPlaneList.size(); i++)
	{
		if (myPlaneList.at(i).Inside(aPosition) == false)
		{
			return false;
		}
	}
	return true;
}