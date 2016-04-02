#pragma once
#include "OpaqueDictionary.h"

class PollingStation
{
public:

	static PollingStation* GetInstance();

	template<typename value>
	void SetValue(const std::string& aKey, const value& aValue);

	template<typename value>
	const value& GetValue(const std::string& aKey) const;

	template<typename value>
	const bool ValueExists(const std::string& aKey) const;


private:
	PollingStation();
	~PollingStation();

	CU::OpaqueDictionary<std::string, 128> myData;
	static PollingStation* ourInstance;
};


template<typename value>
void PollingStation::SetValue(const std::string& aKey, const value& aValue)
{
	myData.SetValue(aKey, aValue);
}

template<typename value>
const value& PollingStation::GetValue(const std::string& aKey) const
{
	return myData.GetValue<value>(aKey);
}


template<typename value>
const bool PollingStation::ValueExists(const std::string& aKey) const
{
	return myData.ValueExists<value>(aKey);
}