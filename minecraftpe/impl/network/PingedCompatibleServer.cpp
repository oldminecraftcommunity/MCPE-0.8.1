#include <network/PingedCompatibleServer.hpp>

PingedCompatibleServer::PingedCompatibleServer(){

}
PingedCompatibleServer::PingedCompatibleServer(const PingedCompatibleServer& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_18 = a2.field_18;
	this->field_1C = a2.field_1C;
}
PingedCompatibleServer& PingedCompatibleServer::operator=(const PingedCompatibleServer& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_18 = a2.field_18;
	this->field_1C = a2.field_1C;

	return *this;
}
