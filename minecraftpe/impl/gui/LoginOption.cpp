#include <gui/LoginOption.hpp>
#include <Minecraft.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/elements/Label.hpp>
#include <network/mco/LoginInformation.hpp>
#include <network/mco/MCOStringify.hpp>
#include <network/mco/MojangConnector.hpp>
#include <network/mco/RestRequestJob.hpp>
#include <util/Util.hpp>

LoginOption::LoginOption(Minecraft* mc)
	: GuiElementContainer(0, 1, 0, 0, 24, 24) {
	this->loginButton = std::shared_ptr<Button>(new Touch::TButton(1, "Login", 0));
	((Touch::TButton*)this->loginButton.get())->init(mc);
	this->logoutButton = std::shared_ptr<Button>(new Touch::TButton(1, "Logout", 0));
	((Touch::TButton*)this->logoutButton.get())->init(mc);
	this->beepLabel = std::shared_ptr<Label>(new Label("Beep", mc, -1, 0, 0, 0, 1));
	this->addChild(this->loginButton);
	this->addChild(this->logoutButton);
}

LoginOption::~LoginOption() {
}
void LoginOption::tick(Minecraft* a2) {
	MojangConnectionStatus cs; // r0
	GuiElement* v4;			   // r0
	GuiElement* v5;			   // r0
	bool_t v6;				   // r1
	GuiElement* v7;			   // r0
	bool_t v8;				   // r1

	cs = a2->mojangConnector->getConnectionStatus();
	if(cs != STATUS_2) {
		if(cs) {
			if(cs != STATUS_1) {
				return;
			}
			v5 = this->loginButton.get();
			v6 = 0;
		} else {
			if(!this->logoutButton->visible && this->loginButton->visible) {
				return;
			}
			v5 = this->loginButton.get();
			v6 = 1;
		}
		v5->setActiveAndVisibility(v6);
		v7 = this->logoutButton.get();
		v8 = 0;
		goto LABEL_14;
	}
	v4 = this->loginButton.get();
	if(v4->visible || !this->logoutButton->visible) {
		v4->setActiveAndVisibility(0);
		v7 = this->logoutButton.get();
		v8 = 1;
LABEL_14:
		v7->setActiveAndVisibility(v8);
		this->field_50 = 0;
		this->setupPositions();
	}
}
void LoginOption::setupPositions() {
	int32_t posX; // r3
	int32_t v4;	  // r3

	posX = this->posX;
	this->logoutButton->posX = posX;
	this->loginButton->posX = posX;
	v4 = this->posY + 3;
	this->logoutButton->posY = v4;
	this->loginButton->posY = v4;
	this->logoutButton->height = 18;
	this->loginButton->height = 18;
	this->height = this->logoutButton->height + 6;
}
void LoginOption::mouseClicked(Minecraft* mc, int32_t a3, int32_t a4, int32_t a5) {
	Button* v9;
	if(this->loginButton->clicked(mc, a3, a4)) {
		v9 = this->loginButton.get();
	} else {
		if(!this->logoutButton->clicked(mc, a3, a4)) return;
		v9 = this->logoutButton.get();
	}
	this->field_50 = v9;
	v9->setPressed();
}

void LoginOption::mouseReleased(Minecraft* mc, int32_t a3, int32_t a4, int32_t a5) {
	if(this->field_50 == this->loginButton.get() && this->field_50->clicked(mc, a3, a4)) {
		mc->platform()->openLoginWindow();
	} else {
		if(this->field_50 == this->logoutButton.get()) {
			if(this->field_50->clicked(mc, a3, a4)) {
				std::shared_ptr<LoginInformation> v19 = mc->mojangConnector->getLoginInformation();
				std::string body = MCOStringify::stringifySignOut(v19->accessToken, v19->clientId);
				std::shared_ptr<RestRequestJob> v20 = RestRequestJob::CreateJob(RRT_1, mc->mojangConnector->getAccountSercice(), mc);
				v20->field_30 = Util::simpleFormat("/invalidate", {});
				v20->setBody(body);
				RestRequestJob::launchRequest( //TODO check is this stuff corrent, std is pain
					v20,
					mc->mojangConnector->getThreadCollection(),
					[mc](int32_t a2, const std::string& a3, const RestCallTagData& a4, std::shared_ptr<RestRequestJob> a5) {
						mc->mojangConnector->setLoginInformation({});
					},
					[](bool_t, bool_t, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>) {

					});
			}
		}
	}
	this->field_50 = 0;
	this->loginButton->released(a3, a4);
	this->logoutButton->released(a3, a4);
}
