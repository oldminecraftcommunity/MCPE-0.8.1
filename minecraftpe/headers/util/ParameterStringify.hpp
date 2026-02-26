#pragma once
#include <_types.h>
#include <vector>
#include <string>

struct ParameterStringify
{
	template<typename... _args>
	static void stringifyNext(std::vector<std::string>&, _args... args)
#ifdef IMTOOLAZYTOFIX16ERRS
	{
		printf("stringifyNext - not implemented\n");
	}
#endif
	;
};


