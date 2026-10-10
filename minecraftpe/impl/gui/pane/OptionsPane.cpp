#include <gui/pane/OptionsPane.hpp>
#include <gui/OptionsGroup.hpp>
#include <memory>

OptionsPane::OptionsPane()
	: PackedScrollContainer(1, 0, 0) {
}
OptionsGroup* OptionsPane::createOptionsGroup(std::string a2) {
	std::shared_ptr<OptionsGroup> g(new OptionsGroup(a2));
	this->children.push_back(std::shared_ptr<GuiElement>(g));
	return (OptionsGroup*) g.get();
}

void OptionsPane::setupPositions() {
	PackedScrollContainer::setupPositions();
}
