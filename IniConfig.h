#pragma once
#include <string>
#include <vector>

class IniData
{
public:
	IniData(const std::string& raw);
public:
	std::string AsString();
	int AsInt();
	float AsFloat();
private:
	std::string m_raw;
};

struct IniVariable
{
	std::string m_name;
	IniData m_value;
};

class IniConfig
{
public:
	IniConfig(const std::string& path);

	void FromString(const std::string& string);
	void FromFile(const std::string& path);

	IniData GetVariable(const std::string& name);
private:
	std::vector<IniVariable> m_variables;
};