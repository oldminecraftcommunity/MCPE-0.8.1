#include <rendering/PerfRenderer.hpp>
#include <Minecraft.hpp>
#include <rendering/Font.hpp>
#include <perf/PerfTimer.hpp>

PerfRenderer::PerfRenderer(Minecraft* mc, Font* font){
	this->minecraft = mc;
	this->font = font;
	this->field_8 = "root";
	this->field_24 = 0;
	this->field_28 = -1;
	int32_t cnt = 512;
	do{
		this->field_C.emplace_back(0);
		this->field_18.emplace_back(0);
		--cnt;
	}while(cnt);
}

void PerfRenderer::debugFpsMeterKeyPress(int32_t n) {
	std::vector<PerfTimer::ResultField> v9 = PerfTimer::getLog(this->field_8);
	if(!v9.empty()) {
		std::string v12(v9[0].field_8);
		v9.erase(v9.begin());
		if(n) {
			int32_t v6 = n - 1;
			if(v6 < v9.size()) {
				if(v9[0].field_8 == "unspecified") {
					if(this->field_8.size()) {
						this->field_8 += ".";
					}
					this->field_8 += v9[0].field_8;
				}
			}
		} else if(v12.size()) {
			int32_t v5 = this->field_8.rfind(".");
			if(v5 != -1) {
				this->field_8 = this->field_8.substr(0, v5);
			}
		}
	}
}
void PerfRenderer::renderFpsMeter(float f) {
	printf("PerfRenderer::renderFpsMeter - not implemented\n"); //TODO PerfRenderer::renderFpsMeter
}

std::string PerfRenderer::toPercentString(float f){
	char s[32];
	sprintf(s, "%3.2f%%", f);
	return s;
}
