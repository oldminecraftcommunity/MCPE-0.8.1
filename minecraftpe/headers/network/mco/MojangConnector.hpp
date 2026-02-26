#pragma once
#include <_types.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <network/mco/MojangConnectionStatus.hpp>

struct ThreadCollection;
struct LoginInformation;
struct MCOParser;
struct Minecraft;
struct Random;
struct RestService;
struct MCOServerListItem;

struct MojangConnector{
	std::shared_ptr<RestService> accountService;
	std::shared_ptr<RestService> mcoService;
	std::shared_ptr<ThreadCollection> threadCollection;
	std::shared_ptr<LoginInformation> loginInformation;
	std::string field_20;
	MojangConnectionStatus status;
	std::shared_ptr<MCOParser> mcoParser;
	Minecraft* minecraft;
	std::shared_ptr<MCOServerListItem> serverList;
	bool_t serverCreationEnabled;
	int8_t field_3D, field_3E, field_3F;
	std::shared_ptr<Random> random;
	std::string joinMCOPayload;
	std::string serverKey;
	bool_t serviceEnabled;
	int8_t field_51, field_52, field_53;

	MojangConnector(struct Minecraft*);
	void clearLoginInformation();
	std::shared_ptr<RestService> getAccountSercice();
	MojangConnectionStatus getConnectionStatus();
	std::string getEncryptedJoinDataString(int64_t, const std::string&, const std::string&);
	std::string* getJoinMCOPayload();
	std::shared_ptr<LoginInformation> getLoginInformation();
	std::shared_ptr<MCOParser> getMCOParser();
	std::shared_ptr<MCOServerListItem> getMCOServerList();
	std::shared_ptr<RestService> getMCOSercice();
	std::string* getServerKey();
	std::shared_ptr<ThreadCollection> getThreadCollection();
	bool_t isMCOCreateServersEnabled();
	bool_t isServiceEnabled();
	void setLoginInformation(const LoginInformation&);
	void setMCOCreateServersEnabled(bool_t);
	void setMCOServerList(std::shared_ptr<std::unordered_map<int64_t, MCOServerListItem>>); //long long
	void setMCOServiceEnabled(bool_t);
	void setPayload(const std::string&);
	void setServerKey(const std::string&);
	void setStatus(MojangConnectionStatus);
	void updateUIThread();
	std::string urlEncode(std::string);
	~MojangConnector();
};
