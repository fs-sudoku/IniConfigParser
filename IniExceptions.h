#pragma once
#include <stdexcept>

class IniSyntaxException : public std::runtime_error
{
public:
	IniSyntaxException(const std::string& message) : std::runtime_error(message) { }
};

class IniFileNotFoundException : public std::runtime_error
{
public:
	IniFileNotFoundException(const std::string& message) : std::runtime_error(message) { }
};

class IniVariableNotFoundException : public std::runtime_error
{
public:
	IniVariableNotFoundException(const std::string& message) : std::runtime_error(message) { }
};