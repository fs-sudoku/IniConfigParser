#include "IniConfig.h"
#include "IniExceptions.h"

#include <fstream>
#include <iostream>
#include <algorithm>

namespace Util
{
	std::string ReadFile(const std::string& path)
	{
		std::ifstream stream(path);
		if (stream.fail()) {
			throw IniFileNotFoundException("Cannot read '.ini' file, path: " + path);
		}
		return std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
	}
}

IniConfig::IniConfig(const std::string& path)
{
	this->FromFile(path);
}

void IniConfig::FromString(const std::string& string)
{
	auto remove_spaces = [&](std::string& string) {
		string.erase(std::remove_if(string.begin(), string.end(), std::isspace), string.end());
	};
	auto remove_comments = [&](std::string& string) {
		const auto& commentFind = string.find_first_of(';');
		string = string.substr(0, commentFind);
		remove_spaces(string);
	};

	std::vector<std::string> lines;
	size_t lastLine = 0;

	for (size_t i = 0; i < string.size() + 1; i++) {
		if (string[i] == '\n' || i == string.size()) {
			lines.push_back(string.substr(lastLine, i - lastLine));
			lastLine = i+1;
		}
	}

	for (size_t i = 0; i < lines.size(); i++) {
		auto& path = lines[i];
		const auto& equalFind = path.find_first_of('=');
		if (equalFind != std::string::npos) {
			std::string name = path.substr(0, equalFind);
			std::string value = path.substr(equalFind + 1, path.size() - equalFind);

			remove_spaces(name);
			remove_comments(value);
			
			m_variables.push_back({ name, IniData(value) });
		}
		else {
			if (path.find('[') == std::string::npos || path.find(']') == std::string::npos) {
				throw IniSyntaxException("Cannot find in '=' in variable deftion, line: " + i);
				return;
			}
		}
	}
}

void IniConfig::FromFile(const std::string& path)
{
	this->FromString(Util::ReadFile(path));
}

IniData IniConfig::GetVariable(const std::string& name)
{
	for (size_t i = 0; i < m_variables.size(); i++) {
		if (m_variables[i].m_name == name) {
			return m_variables[i].m_value;
		}
	}
	throw IniVariableNotFoundException("Cannot find variable, name: " + name);
}

IniData::IniData(const std::string& raw) : m_raw(raw)
{ }

std::string IniData::AsString()
{
	return m_raw;
}

int IniData::AsInt()
{
	return std::stoi(m_raw);
}

float IniData::AsFloat()
{
	return std::stof(m_raw);
}
