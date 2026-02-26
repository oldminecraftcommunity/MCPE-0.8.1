#include <network/mco/MojangConnector.hpp>
#include <util/ThreadCollection.hpp>
#include <network/mco/LoginInformation.hpp>
#include <Minecraft.hpp>

MojangConnector::MojangConnector(Minecraft* minecraft) {
	this->serviceEnabled = 0;
	this->status = STATUS_0;
	this->threadCollection = std::shared_ptr<ThreadCollection>(new ThreadCollection(4));
	printf("MojangConnector::MojangConnector - not implemented\n"); //TODO
}

void MojangConnector::clearLoginInformation() {
	this->setLoginInformation(LoginInformation());
}
std::shared_ptr<RestService> MojangConnector::getAccountSercice() {
	return this->accountService;
}
MojangConnectionStatus MojangConnector::getConnectionStatus() {
	return this->status;
}
std::string MojangConnector::getEncryptedJoinDataString(int64_t, const std::string&, const std::string&) {
	printf("MojangConnector::getEncryptedJoinDataString - not implemented\n"); //TODO
	return "";
}
std::string* MojangConnector::getJoinMCOPayload() {
	return &this->joinMCOPayload;
}
std::shared_ptr<LoginInformation> MojangConnector::getLoginInformation() {
	return this->loginInformation;
}
std::shared_ptr<MCOParser> MojangConnector::getMCOParser() {
	return this->mcoParser;
}
std::shared_ptr<MCOServerListItem> MojangConnector::getMCOServerList() {
	return this->serverList;
}
std::shared_ptr<RestService> MojangConnector::getMCOSercice() {
	return this->mcoService;
}
std::string* MojangConnector::getServerKey() {
	return &this->serverKey;
}
std::shared_ptr<ThreadCollection> MojangConnector::getThreadCollection() {
	return this->threadCollection;
}
bool_t MojangConnector::isMCOCreateServersEnabled() {
	return this->status == STATUS_2 && this->serverCreationEnabled;
}
bool_t MojangConnector::isServiceEnabled() {
	return this->serviceEnabled;
}
void MojangConnector::setLoginInformation(const LoginInformation&) {
	printf("MojangConnector::setLoginInformation - not implemented\n"); //TODO
}
void MojangConnector::setMCOCreateServersEnabled(bool_t a2) {
	this->serverCreationEnabled = a2;
}
void MojangConnector::setMCOServerList(std::shared_ptr<std::unordered_map<int64_t, MCOServerListItem>> a2){
	printf("MojangConnector::setMCOServerList - not implemented\n"); //TODO
}
void MojangConnector::setMCOServiceEnabled(bool_t a2) {
	this->serviceEnabled = a2;
}
void MojangConnector::setPayload(const std::string& a2) {
	this->joinMCOPayload = a2;
}
void MojangConnector::setServerKey(const std::string&) {
	printf("MojangConnector::setServerKey - not implemented\n"); //TODO
}
void MojangConnector::setStatus(MojangConnectionStatus a2){
	printf("MojangConnector::setStatus(%d) - not implemented\n", a2); //TODO
}
void MojangConnector::updateUIThread() {
	this->threadCollection->processUIThread();
}
std::string MojangConnector::urlEncode(std::string a2) {
	printf("MojangConnector::urlEncode(%s) - not implemented\n", a2.c_str()); //TODO
	return "";
}
MojangConnector::~MojangConnector() {
}
