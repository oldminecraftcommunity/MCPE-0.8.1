#include <util/Common.hpp>
#include <util/Util.hpp>

std::string Common::getGameVersionString(){
	std::string s = Common::getGameVersionStringNet();
	s.insert(0, "v");
	return s+" alpha";
}

std::string Common::getGameVersionStringNet(){
	return Util::toString(0) + '.' + Util::toString(8) + '.' + Util::toString(1);
}
