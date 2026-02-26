#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>

struct GuiMessage;
struct ServerCommandParser
{
	struct Command
	{
		//TODO figure out what those 2 fields are
		//std::vector field_0;
		int32_t exceptedParamCnt;
		//std::function field_10;

		//TODO checkParameters function
		~Command();
	};

	struct Token
	{
		std::string field_0;
		int32_t n;
		int32_t field_8;
		bool_t field_C;
		int8_t field_D, field_E, field_F;

		Token(const std::string&);
	};

	std::string field_0;
	std::unordered_map<std::string, std::unique_ptr<ServerCommandParser::Command>> field_4;

	static std::string executeCommand(const GuiMessage&);
};
