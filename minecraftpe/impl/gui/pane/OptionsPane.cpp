#include <gui/pane/OptionsPane.hpp>
#include <gui/OptionsGroup.hpp>
#include <memory>

OptionsPane::OptionsPane()
	: PackedScrollContainer(1, 0, 0) {
}
OptionsGroup* OptionsPane::createOptionsGroup(std::string a2) {
	OptionsGroup* g = new OptionsGroup(a2);
	this->children.emplace_back(std::shared_ptr<OptionsGroup>(g));
	return g;
}

OptionsPane::~OptionsPane() {
}
void OptionsPane::setupPositions() {
	PackedScrollContainer::setupPositions();
}
