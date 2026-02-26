#include <_types.h>
#include <string>
#include <util/Util.hpp>
#include <ctype.h>
#include <algorithm>
#include <utf8proc.h>
#include <string.h>

std::string Util::EMPTY_STRING = "";

bool_t Util::startsWith(const std::string& a1, const std::string& a2) {
	if(a2.size() > a1.size()) {
		return 0;
	}
	std::string v7 = a1.substr(0, a2.size());
	return v7.size() == a2.size() && memcmp(v7.c_str(), a2.c_str(), v7.size()) == 0;
}

std::string Util::getExtension(const std::string& a2) {
	//TODO check
	int32_t dot = a2.find('.');
	if(dot == -1) {
		return "";
	} else {
		return a2.substr(dot);
	}
}

bool_t Util::endsWith(const std::string& str, const std::string& end){
	if (end.size() > str.size()) return false; //XXX might be not as in original
	return std::equal(end.rbegin(), end.rend(), str.rbegin());
}
std::string* Util::stringReplace(std::string& a1, const std::string& a2, const std::string& a3, int32_t a4) {
	uint32_t v9;
	for(uint32_t i = a2.size(); a4; a1.replace(v9, i, a3)) {
		--a4;
		v9 = a1.find(a2, 0);
		if(v9 == -1) break;
	}
	return &a1;
}

int32_t Util::hashCode(const std::string& s){
	int32_t hash, counter;

	hash = 0;
	counter = 0;
	while(counter < s.length()){
		int32_t c = s[counter];
		hash = 31 * hash + c;
		++counter;
	}

	return hash;
}

void Util::removeAll(std::string& a1, const char_t** a2, int32_t a3) {
	int32_t v6 = 0;
	while(v6 < a3) {
		Util::stringReplace(a1, a2[v6], "", -1);
		++v6;
	}
}
int32_t Util::utf8len(const std::string& a1) {
	int32_t v1 = 0;
	const uint8_t* data = (const uint8_t*)a1.c_str();
	int32_t len = a1.size();
	while(1) {
		int32_t v6;
		int32_t v4 = utf8proc_iterate(data, len, &v6);
		if(v4 <= 0) break;
		data += v4;
		len -= v4;
		++v1;
	}
	return v1;
}
std::string Util::utf8substring(const std::string& a2, int32_t start, int32_t end) {
	std::string a1 = "";
	int32_t v8 = 0;
	const uint8_t* data = (const uint8_t*)a2.c_str();
	int32_t len = a2.size();
	do {
		int32_t v6;
		int32_t v12 = utf8proc_iterate(data, len, &v6);
		if(v12 <= 0) break;
		if(v8 >= start && (v8 < end || end < 0)) {
			for(int32_t v10 = 0; v10 != v12; ++v10) {
				a1.push_back(data[v10]);
			}
		}

		data += v12;
		len -= v12;
		++v8;
	} while(end < 0 || v8 < end);
	return a1;
}
std::string Util::simpleFormat(const std::string& a2, std::vector<std::string> a3) {
	//probably not like in original
	std::string ret = "";
	int32_t curFmt = 0;
	bool_t fmt = 0;
	bool_t v8 = 0;
	for(int32_t i = 0; i < a2.length(); ++i) {
		if(fmt) {
			if(a2[i] != '%' && curFmt < a3.size()) {
				ret += a3[curFmt];
				++curFmt;
			}
			ret += a2[i];
			fmt = 0;
		} else if(v8) {
			ret += a2[i];
			v8 = 0;
		} else if(a2[i] == '\x7f') {
			ret += "\x7f";
			v8 = 1;
		} else if(a2[i] == '%') {
			fmt = 1;
		} else {
			ret += a2[i];
		}
	}

	if(fmt) {
		if(curFmt < (a3.size())) {
			ret += a3[curFmt];
		}
	}

	return ret;
}

std::string Util::toLower(const std::string& s){
	//TODO check
	std::string cp = s;
	std::transform(cp.begin(), cp.end(), cp.begin(), tolower);
	return cp;
}
void Util::stringSplit(const std::string& a1, int32_t a2, const float* a3, std::function<void(const std::string&, float)> a4) {
	int32_t v4 = 0;
	float v5 = 0;
	int32_t v10 = -1;
	int32_t v11 = 0;
	while(v4 < a1.size()) {
		int32_t v12 = (uint8_t)a1[v4];
		v5 += a3[v12];
		if(v12 == ' ') {
			v10 = v4;
		} else if(v12 == '\t') {
			v10 = v4;
		}

		if((int)v5 > a2) {
			if(v12 != '\n') {
				if(v10 < 0) {
					--v4;
				}
				if(v10 >= 0) {
					v4 = v10;
				}
				std::string v15 = a1.substr(v11, v4 - v11 + 1);
				a4(v15, v5);
				v11 = v4 + 1;
				v10 = -1;
				v5 = 0;
				++v4;
				continue;
			}
		}else if ( v12 != '\n' )
		{
			++v4;
			continue;
		}
		std::string v15 = a1.substr(v11, v4 - v11);
		a4(v15, 0);
		v11 = v4 + 1;
		v10 = -1;
		v5 = 0;
		++v4;
	}
	std::string v15 = a1.substr(v11, v4 - v11);
	a4(v15, v5);
}

std::string Util::toString(int32_t i){
	std::string s = "";
	if(i < 0) {
		i = -1;
		s += '-';
	}
	uint32_t v4 = 1000000000;
	int32_t v5 = 10;
	while(!(i/v4)){
		i %= v4;
		--v5;
		v4/= 10;
		if(!v5){
			v4 = 0;
			break;
		}
	}
	if(!i) s += '0';
	while(v4){
		s += '0' + (i/v4);
		i %= v4;
		v4 /= 10;
	}
	return s;

}


std::string Util::stringTrim(const std::string& a2, const std::string& a3, bool_t a4, bool_t a5) {
	int32_t v8 = a2.length();
	int32_t v9 = a3.length();
	if(v8 && v9 && (a4 || a5)) {
		int32_t v10 = v8 - 1;
		int32_t i;
		if(a4) { //crop beginning
			for(i = 0; i < v8; ++i) {
				const char_t* c = std::find(a3.data(), a3.data() + a3.length(), a2[i]);
				if(c == a3.data() + a3.length()) break; //no more letters left to crop
			}
		} else {
			i = 0;
		}

		if(a5) { //crop ending
			while(v10 >= i) {
				const char_t* c = std::find(a3.data(), a3.data() + a3.length(), a2[v10]);
				if(c == a3.data() + a3.length()) break;
				--v10;
			}
		}
		return a2.substr(i, v10 - i + 1);
	} else {
		return "";
	}

}
std::string Util::stringTrim(const std::string& a2) {
	return Util::stringTrim(a2, " \t\n\r", 1, 1);
}
