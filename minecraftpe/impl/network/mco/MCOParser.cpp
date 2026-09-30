#include <network/mco/MCOParser.hpp>
#include <json/json.h>
#include <network/mco/LoginInformation.hpp>

void MCOParser::parseErrorMessage(const std::string& a2, std::string& reason, int32_t& error) {
	Json::Value v8;
	Json::Reader v11;
	v11.parse(a2, v8, 1);
	error = v8.get("error", Json::Value()).asInt();
	reason = v8.get("reason", Json::Value()).asString();
}
void MCOParser::parseJoinWorld(const std::string& a2, std::string& ip, uint16_t& port, std::string& key) {
	Json::Value v9;
	Json::Reader v12;
	if(v12.parse(a2, v9, 1)) {
		ip = v9.get("ip", Json::Value("127.0.0.1")).asString();
		port = v9.get("port", Json::Value(25675)).asInt();
		key = v9.get("key", Json::Value("")).asString();
	}
}
LoginInformation MCOParser::parseMCOAccountValidSessionReturnValue(const std::string& a3) {
	LoginInformation ret;
	Json::Value v7;
	Json::Reader v11;
	v11.parse(a3, v7, 1);
	ret.accessToken = v7.get("accessToken", Json::Value("")).asString();
	ret.clientId = v7.get("clientToken", Json::Value("")).asString();
	ret.profileId = v7.get("selectedProfile", Json::Value(7)).asString();
	ret.profileName = v7.get("name", Json::Value("")).asString();
	return ret;
}
std::shared_ptr<std::unordered_map<long long, MCOServerListItem>> MCOParser::parseServerList(const std::string& a3){
	std::shared_ptr<std::unordered_map<long long, MCOServerListItem>> ret(new std::unordered_map<long long, MCOServerListItem>());
	int v6 = 0;
	Json::Value v29;
	Json::Reader v37;
	if(v37.parse(a3, v29)) {
		while(v6 < v29.size()) {
			int v9 = 0;
			MCOServerListItem v33;
			Json::Value v30 = v29[v6];
			v33.serverId = v30.get("serverId", Json::Value(-1)).asInt64();
			v33.worldName = v30.get("name", Json::Value("wrong_name")).asString();
			v33.open = v30.get("open", Json::Value(0)).asBool();
			v33.ownerName = v30.get("ownerName", Json::Value("wrong_owner_name")).asString();
			v33.myWorld = v30.get("myWorld", Json::Value(0)).asBool();
			v33.maxNrPlayers = v30.get("maxNrPlayers", Json::Value(0)).asInt();
			v33.gamemodeName = v30.get("type", Json::Value("wrong_game_type")).asString();
			Json::Value v31 = v30["playerNames"];
			while(v9 < v31.size()) {
				v33.playerNames.push_back(v31[v9].asString());
				++v9;
			}
			int v13 = 0;
			Json::Value v32 = v30["invited"];
			while(v13 < v32.size()) {
				v33.invited.insert(v32[v13++].asString());
			}
			ret->insert(std::pair<long long, MCOServerListItem>(v33.serverId, v33));
			++v6;
		}
	}

	return ret;
}
void MCOParser::parseStatus(const std::string& a2, bool& buyServerEnabled, bool& createServersEnabled, bool& serviceEnabled) {
	Json::Value v8;
	Json::Reader v11;
	v11.parse(a2, v8, 1);
	buyServerEnabled = v8.get("buyServerEnabled", Json::Value()).asBool();
	createServersEnabled = v8.get("createServerEnabled", Json::Value()).asBool();
	serviceEnabled = v8.get("serviceEnabled", Json::Value()).asBool();
}
