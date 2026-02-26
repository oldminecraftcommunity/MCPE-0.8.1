#include <network/IRakNetInstance.hpp>

IRakNetInstance::~IRakNetInstance() {
}
bool_t IRakNetInstance::host(const std::string&, int32_t, int32_t) {
	return 0;
}
bool_t IRakNetInstance::connect(const char_t*, int32_t) {
	return 0;
}
void IRakNetInstance::setIsLoggedIn(bool_t) {
}
void IRakNetInstance::pingForHosts(int32_t) {
}
void IRakNetInstance::stopPingForHosts() {
}
std::vector<PingedCompatibleServer>* IRakNetInstance::getServerList() {
	static std::vector<PingedCompatibleServer>* l; //TODO this thing has guard lock stuff, maybe this is some kind of std::ptr~

	return l;
}
void IRakNetInstance::clearServerList() {
}
void IRakNetInstance::disconnect() {
}
void IRakNetInstance::announceServer(const std::string&) {
}
RakNet::RakPeer* IRakNetInstance::getPeer() {
	return 0;
}
bool_t IRakNetInstance::isMyLocalGuid(const RakNet::RakNetGUID&) {
	return 1;
}
void IRakNetInstance::runEvents(struct NetEventCallback*) {
}
void IRakNetInstance::send(Packet&) {
}
void IRakNetInstance::send(const RakNet::RakNetGUID&, Packet&) {
}
void IRakNetInstance::send(Packet* a2) {
	delete a2;
}
void IRakNetInstance::send(const RakNet::RakNetGUID&, Packet* a3) {
	delete a3;
}
bool_t IRakNetInstance::isServer() {
	return 1;
}
bool_t IRakNetInstance::isProbablyBroken() {
	return 0;
}
void IRakNetInstance::resetIsBroken() {
}
