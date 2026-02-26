#include <ICreator.hpp>
#include <util/OffsetPosTranslator.hpp>

void ICreator::TileEvent::write(std::basic_stringstream<char_t>& a2, IPosTranslator& a3) {
	int32_t v13 = this->field_4;
	int32_t v14 = this->field_8;
	int32_t v15 = this->field_C;

	a3.to(v13, v14, v15);

}
