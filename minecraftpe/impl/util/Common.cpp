#include <util/Common.hpp>
#include <util/Util.hpp>

std::string Common::getGameVersionString(){
	return "v"+Common::getGameVersionStringNet()+" alpha";
}

std::string Common::getGameVersionStringNet(){
	return Util::toString(0) + '.' + Util::toString(8) + '.' + Util::toString(1);
}
