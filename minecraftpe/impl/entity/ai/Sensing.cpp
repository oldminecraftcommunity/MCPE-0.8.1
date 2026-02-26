#include <entity/ai/Sensing.hpp>
#include <entity/Mob.hpp>

Sensing::Sensing(Mob* a2) {
	this->holder = a2;
}

bool_t Sensing::canSee(Entity* a2) {
	bool_t r;
	int32_t eid = a2->entityId;
	if(this->_canSee.find(eid) == this->_canSee.end()) {
		if(this->_cannotSee.find(eid) == this->_cannotSee.end()) {
			r = this->holder->canSee(a2);
			if(r) {
				this->_canSee.insert(eid);
			} else {
				this->_cannotSee.insert(eid);
			}
		} else {
			return 0;
		}
	} else {
		return 1;
	}
	return r;
}
