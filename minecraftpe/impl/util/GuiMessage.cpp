#include <util/GuiMessage.hpp>

GuiMessage::GuiMessage(const GuiMessage& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_8 = a2.field_8;
	this->field_C = a2.field_C;
	this->field_10 = a2.field_10;
}
GuiMessage::GuiMessage(GuiMessage&& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_8 = a2.field_8;
	a2.field_8 = ""; //TODO ???????
	this->field_C = a2.field_C;
	a2.field_C = "";
	this->field_10 = a2.field_10;
	a2.field_10 = "";
}
GuiMessage::GuiMessage(const std::string& a2, const std::string& a3, int32_t maxMsgLen) {
	this->field_0 = 0;
	this->field_4 = maxMsgLen;
	this->field_8 = a3;
	this->field_C = a2;
	if(a2.size()) {
		this->field_10 = '<' + a2 + "> " + a3;
	} else {
		this->field_10 = a3;
	}
}
GuiMessage& GuiMessage::operator=(const GuiMessage& a2){
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_8 = a2.field_8;
	this->field_C = a2.field_C;
	this->field_10 = a2.field_10;
	return *this;
}
GuiMessage& GuiMessage::operator=(GuiMessage&& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_8 = a2.field_8;
	this->field_C = a2.field_C;
	this->field_10 = a2.field_10;
	return *this;
}
GuiMessage::~GuiMessage(){

}
