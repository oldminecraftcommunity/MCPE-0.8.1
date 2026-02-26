#include <sound/SoundRepository.hpp>
#include <math/Mth.hpp>

void SoundRepository::add(const std::string& a2, struct SoundDesc& a3) {
	if(a3.pcmData) {
		this->add(a2, (const SoundDesc&)a3);
		a3.field_18 = a2;
	}
}
void SoundRepository::add(const std::string& a2, const struct SoundDesc& a3) {
	if(a3.pcmData) {
		auto&& p = this->sounds.find(a2);
		if(p == this->sounds.end()) {
			std::vector<SoundDesc> v11;
			v11.push_back(a3);
			this->sounds.insert({a2, v11});
		} else {
			p->second.push_back(a3);
		}
	}
}
bool_t SoundRepository::get(const std::string& a2, struct SoundDesc& a3) {
	auto&& p = this->sounds.find(a2);
	if(p == this->sounds.end()) return 0;

	a3 = SoundDesc(p->second[Mth::random(p->second.size())]); //inlined
	return 1;
}
