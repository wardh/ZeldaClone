#pragma once
#include "../Common Utilities/EnumDictionary.h"
#include "StaticArray.h"
#include "PoolPointer.h"


#include "../Common Utilities/Observer.h"

namespace GameSpace
{
	class Scene;
}


namespace CommonUtilities
{

//#define GET_TERRAIN_HEIGHT_AT_POSITION(x,y) CU::PollingStation::GetInstance()->GetValue<const float(float x, float y)>(CU::ePollingStationVariables::GETTERRAINHEIGHT)(x, y);

	enum class ePollingStationVariables
	{
		GETTERRAINHEIGHT, // std::function<const float(float x, float y)
		CAMERA_ORIENTATION, //const Matrix44<float>*
		CAMERA_PROJECTION, //const Matrix44<float>*
		HERO_OBJECT,	// CU::PoolPointer<CS::GameObject>
		PLAYER_NUMBER_OF_SOULS, // const int*
	};

	class PollingStation : public CU::Observer
	{
	public:
		static PollingStation* GetInstance();

		template<typename value>
		void SetValue(const ePollingStationVariables aKey, const value& aValue);

		template<typename value>
		value& GetValue(const ePollingStationVariables aKey);

		template<typename value>
		const bool ValueExists(const ePollingStationVariables aKey);

		const CU::GrowingArray<CU::PoolPointer<CS::GameObject>>* GetUnits(CS::eFaction aFaction);

		//Returns nullptr when no unit with ID is found
		CU::PoolPointer<CS::GameObject> GetUnit(int aUnitID);

		void SetUnits(CU::GrowingArray<CU::PoolPointer<CS::GameObject>>* someUnits, CS::eFaction aFaction);

		CU::PoolPointer<CS::GameObject> GetGameObjectFromActiveScene(int aID);

		void SetActiveScene(GameSpace::Scene* aActiveScene);
		int GetObjectIDByTag(const std::string& aObjectTag);
	private:
		PollingStation();
		~PollingStation();


		bool HandleUnitDeath(const CU::PoolPointer<CU::Event>& anEvent);
		StaticArray<CU::GrowingArray<CU::PoolPointer<CS::GameObject>>*, static_cast<int>(CS::eFaction::MAX_SIZE)> myUnits;
		static PollingStation* ourInstance;
		CU::EnumDictionary<ePollingStationVariables, 256> myVariables;
		GameSpace::Scene* myActiveScene;
	};

	template<typename value>
	void PollingStation::SetValue(const ePollingStationVariables aKey, const value& aValue)
	{
		myVariables.SetValue(aKey, aValue);
	}

	template<typename value>
	value& PollingStation::GetValue(const ePollingStationVariables aKey)
	{
		return *myVariables.GetValue<value>(aKey);

	}

	template<typename value>
	const bool PollingStation::ValueExists(const ePollingStationVariables aKey)
	{
		return myVariables.ValueExists<value>(aKey);
	}

}
namespace CU = CommonUtilities;