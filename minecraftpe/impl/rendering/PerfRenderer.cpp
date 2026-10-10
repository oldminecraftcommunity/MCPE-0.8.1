#include <rendering/PerfRenderer.hpp>
#include <Minecraft.hpp>
#include <rendering/Font.hpp>
#include <perf/PerfTimer.hpp>
#include <cpputils.hpp>
#include <rendering/states/DisableState.hpp>
#include <rendering/Tesselator.hpp>
#include <sstream>

PerfRenderer::PerfRenderer(Minecraft* mc, Font* font){
	this->minecraft = mc;
	this->font = font;
	this->field_8 = "root";
	this->field_24 = 0;
	this->lastRenderedAt = -1;
	int32_t cnt = 512;
	do{
		this->field_C.push_back(0.0f);
		this->field_18.push_back(0.0f);
		--cnt;
	}while(cnt);
}

void PerfRenderer::debugFpsMeterKeyPress(int32_t n) {
	std::vector<PerfTimer::ResultField> v9 = PerfTimer::getLog(this->field_8);
	if(!v9.empty()) {
		PerfTimer::ResultField res = v9[0];
		v9.erase(v9.begin());
		if(n) {
			int32_t v6 = n - 1;
			if(v6 < v9.size()) {
				if(v9[0].sectionName != "unspecified") {
					if(this->field_8.size()) {
						this->field_8 += ".";
					}
					this->field_8 += v9[0].sectionName;
				}
			}
		} else if(res.sectionName.size()) {
			int32_t v5 = this->field_8.rfind(".");
			if(v5 != -1) {
				this->field_8 = this->field_8.substr(0, v5);
			}
		}
	}
}
void PerfRenderer::renderFpsMeter(float f) {
	std::vector<PerfTimer::ResultField> vec = PerfTimer::getLog(this->field_8);
	if(!vec.empty()) {
		PerfTimer::ResultField v75 = vec[0]; //inlined
		vec.erase(vec.begin());
		if(this->lastRenderedAt == -1) {
			this->lastRenderedAt = getTimeS();
		}
		double time = getTimeS();
		this->field_18[this->field_24] = f;
		this->field_C[this->field_24] = time - this->lastRenderedAt;
		this->field_24 += 1;
		if(this->field_24 >= this->field_C.size()) {
			this->field_24 = 0;
		}
		glEnable(0xB57u);
		glClear(0x100u);
		glMatrixMode(0x1701u);
		glLoadIdentity();
#ifdef USEGLES
		glOrthof
#else
		glOrtho
#endif
			(0.0, this->minecraft->width, this->minecraft->height, 0.0, 1000.0, 3000.0);
		glMatrixMode(0x1700u);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -2000.0);
		glLineWidth(1.0);
		//TODO here
		{
			DisableState ds(3553);
			float v10 = this->minecraft->width - 170;
			Tesselator::instance.begin(4, 0);
			Tesselator::instance.color(0x20000000);
			Tesselator::instance.vertex(0.0, (float)(this->minecraft->height - 83), 0.0);
			Tesselator::instance.vertex(0.0, (float)this->minecraft->height, 0.0);
			Tesselator::instance.vertex(this->field_C.size(), (float)this->minecraft->height, 0.0);
			Tesselator::instance.vertex(this->field_C.size(), (float)(this->minecraft->height - 83), 0.0);
			Tesselator::instance.color(0x20200000);
			Tesselator::instance.vertex(0.0, (float)(this->minecraft->height - 166), 0.0);
			Tesselator::instance.vertex(0.0, (float)(this->minecraft->height - 83), 0.0);
			Tesselator::instance.vertex(this->field_C.size(), (float)(this->minecraft->height - 83), 0.0);
			Tesselator::instance.vertex(this->field_C.size(), (float)(this->minecraft->height - 166), 0.0);
			Tesselator::instance.draw(1);
			float v13 = 0;
			int i;
			for(i = 0; i < this->field_C.size(); ++i) {
				v13 += this->field_C[i];
			}
			int v17 = (int)(float)((float)(v13 / 200.0) / (float)i);
			Tesselator::instance.begin(4);
			Tesselator::instance.color(541065216);
			Tesselator::instance.vertex(0.0, (float)(this->minecraft->height - v17), 0.0);
			Tesselator::instance.vertex(0.0, (float)this->minecraft->height, 0.0);
			Tesselator::instance.vertex(this->field_C.size(), (float)this->minecraft->height, 0.0);
			Tesselator::instance.vertex(this->field_C.size(), this->minecraft->height - v17, 0.0);
			Tesselator::instance.draw(1);

			Tesselator::instance.begin(1);
			for(int v19 = 0; v19 < this->field_C.size(); ++v19) {
				//TODO stuff here
			}
			Tesselator::instance.draw(1);
			Tesselator::instance.begin(4);
			Tesselator::instance.color(0, 200);
			float v29 = (float)(this->minecraft->height - 320);
			int v30 = 0;
			float v31 = (float)v10;
			Tesselator::instance.vertex((float)v10 - 176.0, (float)(v29 - 96.0) - 16.0, 0.0);
			Tesselator::instance.vertex((float)v10 - 176.0, v29 + 320.0, 0.0);
			Tesselator::instance.vertex((float)v10 + 176.0, v29 + 320.0, 0.0);
			Tesselator::instance.vertex((float)v10 + 176.0, (float)(v29 - 96.0) - 16.0, 0.0);
			Tesselator::instance.draw(1);

			DisableState ds2(0xB44);
			DisableState ds3(0xBE2);

			float v32 = 0;
			//TODO loop over vec

			//~ ds3, ds2, ds
		}
		{
			std::stringstream v76;
			//TODO more stuff
		}
		//TODO loop over vec again
		glDisable(0xB57u);
	}
	printf("PerfRenderer::renderFpsMeter - not implemented\n"); //TODO PerfRenderer::renderFpsMeter
}

std::string PerfRenderer::toPercentString(float f){
	char s[32];
	sprintf(s, "%3.2f%%", f);
	return s;
}
