#pragma once
#include <math/Mth.hpp>
#include <sound/SoundDesc.hpp>
#include <string>
#include <map>
#include <vector>

struct SoundRepository{
	std::map<std::string, std::vector<SoundDesc>> sounds;

	void add(const std::string& a2, struct SoundDesc& a3) {
		if (a3.pcmData) {
			this->add(a2, (const SoundDesc&) (a3));
			a3.field_18 = a2;
		}
	}
	void add(const std::string& a2, const struct SoundDesc& a3) {
		if (a3.pcmData) {
			auto&& p = this->sounds.find(a2);
			if (p == this->sounds.end()) {
				std::vector<SoundDesc> v11;
				v11.push_back(a3);
				this->sounds.insert(std::pair<std::string, std::vector<SoundDesc>>(a2, v11));
			} else {
				p->second.push_back(a3);
			}
		}
	}
	bool_t get(const std::string& a2, struct SoundDesc& a3) {
		auto&& p = this->sounds.find(a2);
		if (p == this->sounds.end()) {
			return 0;
		}
		a3 = p->second[Mth::random(p->second.size())]; //inlined
		return 1;
	}
};
