#pragma once
#include <_types.h>
#include <vector>
#include <string>
#include <sstream>
#include <util/Util.hpp>

struct ParameterStringify
{

	static inline void stringifyNext(std::vector<std::string>& a1) {}

	template<typename T, typename... _args>
	static void stringifyNext(std::vector<std::string>& a1, T& t, _args... args) {
		std::stringstream s;
		s << t;
		a1.emplace_back(s.str());
		ParameterStringify::stringifyNext(a1, args...);
	}
	template<typename T>
	static void stringifyNext(std::vector<std::string>& a1, T t) {
		std::stringstream s;
		s << t;
		a1.emplace_back(s.str());
	}

	//should be always inlined? might not even be here actually~
	template<typename... _args>
	static std::vector<std::string> stringify(_args... args) {
		std::vector<std::string> vec;
		ParameterStringify::stringifyNext(vec, args...);
		return vec;
	}
};


