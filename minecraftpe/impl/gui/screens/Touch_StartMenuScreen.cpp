#include <gui/screens/Touch_StartMenuScreen.hpp>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>
#include <gui/buttons/ImageWithBackground.hpp>
#include <util/IntRectangle.hpp>
#include <rendering/Tesselator.hpp>
#include <util/Common.hpp>
#include <rendering/Font.hpp>
#include <gui/screens/PlayScreen.hpp>
#include <gui/screens/OptionsScreen.hpp>
#include<gui/screens/InvalidLicenseScreen.hpp>
#include <network/mco/MojangConnector.hpp>

char_t* gSplashes[] = {
	"Scientific!",
	"Cooler than Spock!",
	"Collaborate and listen!",
	"Never dig down!",
	"Take frequent breaks!",
	"Not linear!",
	"Han shot first!",
	"Nice to meet you!",
	"Buckets of lava!",
	"Ride the pig!",
	"Larger than Earth!",
	"sqrt(-1) love you!",
	"Phobos anomaly!",
	"Punching wood!",
	"Falling off cliffs!",
	"0% sugar!",
	"150% hyperbole!",
	"Synecdoche!",
	"Let's danec!",
	"Seecret Friday update!",
	"Ported implementation!",
	"Lewd with two dudes with food!",
	"Kiss the sky!",
	"20 GOTO 10!",
	"Verlet intregration!",
	"Peter Griffin!",
	"Do not distribute!",
	"Cogito ergo sum!",
	"4815162342 lines of code!",
	"A skeleton popped out!",
	"The Work of Notch!",
	"The sum of its parts!",
	"BTAF used to be good!",
	"I miss ADOM!",
	"umop-apisdn!",
	"OICU812!",
	"Bring me Ray Cokes!",
	"Finger-licking!",
	"Thematic!",
	"Pneumatic!",
	"Sublime!",
	"Octagonal!",
	"Une baguette!",
	"Gargamel plays it!",
	"Rita is the new top dog!",
	"SWM forever!",
	"Representing Edsbyn!",
	"Matt Damon!",
	"Supercalifragilisticexpialidocious!",
	"Consummate V's!",
	"Cow Tools!",
	"Double buffered!",
	"V-synched!",
	"Fan fiction!",
	"Flaxkikare!",
	"Jason! Jason! Jason!",
	"Hotter than the sun!",
	"Internet enabled!",
	"Autonomous!",
	"Engage!",
	"Fantasy!",
	"DRR! DRR! DRR!",
	"Kick it root down!",
	"Regional resources!",
	"Woo, facepunch!",
	"Woo, somethingawful!",
	"Woo, /v/!",
	"Woo, tigsource!",
	"Woo, minecraftforum!",
	"Woo, worldofminecraft!",
	"Woo, reddit!",
	"Woo, 2pp!",
	"Google anlyticsed!",
	"Give us Gordon!",
	"Tip your waiter!",
	"Very fun!",
	"12345 is a bad password!",
	"Vote for net neutrality!",
	"Lives in a pineapple under the sea!",
	"Omnipotent!",
	"Gasp!",
	"...!",
	"Bees, bees, bees, bees!",
	"Haha, LOL!",
	"Hampsterdance!",
	"Switches and ores!",
	"Menger sponge!",
	"idspispopd!",
	"Eple (original edit)!",
	"So fresh, so clean!",
	"Don't look directly at the bugs!",
	"Oh, ok, Pigmen!",
	"Scary!",
	"Play Minecraft, Watch Topgear, Get Pig!",
	"Twittered about!",
	"Jump up, jump up, and get down!",
	"Joel is neat!",
	"A riddle, wrapped in a mystery!",
	"Huge tracts of land!",
	"Welcome to your Doom!",
	"Stay a while, stay forever!",
	"Stay a while and listen!",
	"Treatment for your rash!",
	"\"Autological\" is!",
	"Information wants to be free!",
	"\"Almost never\" is an interesting concept!",
	"Lots of truthiness!",
	"The creeper is a spy!",
	"It's groundbreaking!",
	"Let our battle's begin!",
	"The sky is the limit!",
	"Jeb has amazing hair!",
	"Casual gaming!",
	"Undefeated!",
	"Kinda like Lemmings!",
	"Follow the train, CJ!",
	"Leveraging synergy!",
	"DungeonQuest is unfair!",
	"110813!",
	"90210!",
	"Tyrion would love it!",
	"Also try VVVVVV!",
	"Also try Super Meat Boy!",
	"Also try Terraria!",
	"Also try Mount And Blade!",
	"Also try Project Zomboid!",
	"Also try World of Goo!",
	"Also try Limbo!",
	"Also try Pixeljunk Shooter!",
	"Also try Braid!",
	"That's super!",
	"Bread is pain!",
	"Read more books!",
	"Khaaaaaaaaan!",
	"Less addictive than TV Tropes!",
	"More addictive than lemonade!",
	"Bigger than a bread box!",
	"Millions of peaches!",
	"Fnord!",
	"This is my true form!",
	"Totally forgot about Dre!",
	"Don't bother with the clones!",
	"Pumpkinhead!",
	"Hobo humping slobo babe!",
	"Endless!",
	"Feature packed!",
	"Boots with the fur!",
	"Stop, hammertime!",
	"Conventional!",
	"Homeomorphic to a 3-sphere!",
	"Doesn't avoid double negatives!",
	"Place ALL the blocks!",
	"Does barrel rolls!",
	"Meeting expectations!",
	"PC gaming since 1873!",
	"Ghoughpteighbteau tchoghs!",
	"Got your nose!",
	"Haley loves Elan!",
	"Afraid of the big, black bat!",
	"Doesn't use the U-word!",
	"Child's play!",
	"See you next Friday or so!",
	"150 bpm for 400000 minutes!",
	"Technologic!",
	"Funk soul brother!",
	"Pumpa kungen!",
	"Helo Cymru!",
	"My life for Aiur!",
	"Lennart lennart = new Lennart();",
	"I see your vocabulary has improved!",
	"Who put it there?",
	"You can't explain that!",
	"if not ok then return end",
	"SOPA means LOSER in Swedish!",
	"Big Pointy Teeth!",
	"Bekarton guards the gate!",
	"Mmmph, mmph!",
	"Don't feed avocados to parrots!",
	"Swords for everyone!",
	"Plz reply to my tweet!",
	".party()!",
	"Take her pillow!",
	"Put that cookie down!",
	"Pretty scary!",
	"I have a suggestion.",
	"Now with extra hugs!",
	"Almost C++11!",
	"Woah.",
	"HURNERJSGER?",
	"What's up, Doc?",
	"1 star! Deal with it notch!",
	"100% more yellow text!",
	"Glowing creepy eyes!",
	"Toilet friendly!",
	"Annoying touch buttons!",
	"Astronomically accurate!",
	"0xffff-1 chunks!",
	"Cubism!",
	"Pocket!",
	"Mostly harmless!",
	"!!!1!",
	"Dramatic lighting!",
	"As seen on TV!",
	"Awesome!",
	"100% pure!",
	"May contain nuts!",
	"Better than Prey!",
	"Less polygons!",
	"Sexy!",
	"Limited edition!",
	"Flashing letters!",
	"Made by Mojang!",
	"It's here!",
	"Best in class!",
	"It's alpha!",
	"100% dragon free!",
	"Excitement!",
	"More than 500 sold!",
	"One of a kind!",
	"Heaps of hits on YouTube!",
	"Indev!",
	"Spiders everywhere!",
	"Check it out!",
	"Holy cow, man!",
	"It's a game!",
	"Made in Sweden!",
	"Uses C++!",
	"Reticulating splines!",
	"Minecraft!",
	"Yaaay!",
	"Multiplayer!",
	"Touch compatible!",
	"Undocumented!",
	"Ingots!",
	"Exploding creepers!",
	"That's no moon!",
	"l33t!",
	"Create!",
	"Survive!",
	"Dungeon!",
	"Exclusive!",
	"The bee's knees!",
	"Down with O.P.P.!",
	"Closed source!",
	"Classy!",
	"Wow!",
	"Not on steam!",
	"Oh man!",
	"Awesome community!",
	"Pixels!",
	"Teetsuuuuoooo!",
	"Kaaneeeedaaaa!",
	"Enhanced!",
	"90% bug free!",
	"Pretty!",
	"12 herbs and spices!",
	"Fat free!",
	"Absolutely no memes!",
	"Free dental!",
	"Ask your doctor!",
	"Minors welcome!",
	"Cloud computing!",
	"Legal in Finland!",
	"Hard to label!",
	"Technically good!",
	"Bringing home the bacon!",
	"Quite Indie!",
	"GOTY!",
	"Euclidian!",
	"Now in 3D!",
	"Inspirational!",
	"Herregud!",
	"Complex cellular automata!",
	"Yes, sir!",
	"Played by cowboys!",
	"OpenGL ES 1.1!",
	"Thousands of colors!",
	"Try it!",
	"Age of Wonders is better!",
	"Try the mushroom stew!",
	"Sensational!",
	"Hot tamale, hot hot tamale!",
	"Play him off, keyboard cat!",
	"Guaranteed!",
	"Macroscopic!",
	"Bring it on!",
	"Random splash!",
	"Call your mother!",
	"Monster infighting!",
	"Loved by millions!",
	"Ultimate edition!",
	"Freaky!",
	"You've got a brand new key!",
	"Water proof!",
	"Uninflammable!",
	"Whoa, dude!",
	"All inclusive!",
	"Tell your friends!",
	"NP is not in P!",
	"Notch <3 ez!",
	"Livestreamed!",
	"Haunted!",
	"Polynomial!",
	"Terrestrial!",
	"All is full of love!",
	"Full of stars!",
	0
};
int32_t Touch::StartMenuScreen::currentSplash = -1;

Touch::StartMenuScreen::StartMenuScreen() :
	playButton(2, "Play", 0), playOnRealmsButton(3, "Play on Realms", 0),
	buyButton(5)
{
	this->settingsButtonMaybe = 0;
	this->field_140 = 0;
	this->field_148 = 0;
	this->field_14C = 1;
	this->field_144 = 0;
	this->field_150 = 0;
}

void Touch::StartMenuScreen::_updateLicense(){
	bool_t v4;
	int32_t licenseId = this->minecraft->getLicenseId();
	if(licenseId < 0) v4 = 0;
	else{
		if((uint32_t)licenseId > 1){
			this->minecraft->setScreen(new InvalidLicenseScreen(licenseId, this->minecraft->platform()->hasBuyButtonWhenInvalidLicense()));
			return;
		}
		v4 = 1;
	}
	this->playOnRealmsButton.active = v4;
	this->playButton.active = v4;
}

void Touch::StartMenuScreen::chooseRandomSplash(){
	Random rng;
	int32_t splashcnt = 0;
	while(gSplashes[splashcnt]) ++splashcnt;
	Touch::StartMenuScreen::currentSplash = rng.genrand_int32() % splashcnt;

}
void Touch::StartMenuScreen::setupPlayButtons(bool_t a2){
	int32_t width, height;
	int32_t v4, v5, v6;
	width = this->width;
	this->playButton.width = 100;
	this->playButton.height = 30;
	height = this->height;
	v4 = width/2 - 50;
	this->playButton.posX = v4;
	v5 = height/2;
	if(a2) v6 = v5-15;
	else v6 = v5+10;

	this->playButton.posY = v6;
	this->playOnRealmsButton.width = 100;
	this->playOnRealmsButton.posX = v4;
	this->playOnRealmsButton.height = 30;
	this->playOnRealmsButton.posY = v6+40;
}

Touch::StartMenuScreen::~StartMenuScreen(){
	if(this->settingsButtonMaybe){
		delete this->settingsButtonMaybe;
		this->settingsButtonMaybe = 0;
	}
}
#include <rendering/entity/ItemRenderer.hpp>
#include <item/ItemInstance.hpp>

void Touch::StartMenuScreen::render(int32_t a2, int32_t a3, float a4){
	bool_t mco = this->minecraft->mojangConnector->isServiceEnabled();
	this->playOnRealmsButton.setActiveAndVisibility(mco);
	this->setupPositions();
	this->renderMenuBackground(a4);
	int32_t v10 = this->minecraft->texturesPtr->loadTexture("gui/title.png", 1, 0);
	if(v10){
		if(this->minecraft->texturesPtr->currentTexture != v10){
			glBindTexture(GL_TEXTURE_2D, v10);
			this->minecraft->texturesPtr->currentTexture = v10;
			++Textures::textureChanges;
		}
	}
	glColor4f(1, 1, 1, 1);
	Tesselator::instance.begin(4);

	int32_t v12 = this->field_140;
	int32_t v13 = this->field_144;
	float v14 = v12;
	float v15 = v12+this->field_148;
	float v16 = v13+this->field_14C;
	Tesselator::instance.vertexUV(v12, v16, this->zLayer, 0, 1);
	Tesselator::instance.vertexUV(v15, v16, this->zLayer, 1, 1);
	Tesselator::instance.vertexUV(v15, v13, this->zLayer, 1, 0);
	Tesselator::instance.vertexUV(v14, v13, this->zLayer, 0, 0);
	Tesselator::instance.draw(1);
	this->drawString(this->font, this->field_138, 1, this->height-10, 0xffffff);
	this->drawString(this->font, this->field_13C, 1, this->height-20, 0xffffff);
	if(Touch::StartMenuScreen::currentSplash == -1){
		Touch::StartMenuScreen::chooseRandomSplash();
	}
	double v17 = this->field_150 + this->minecraft->field_D34;
	this->field_150 = v17;

	this->font->drawTransformed(gSplashes[Touch::StartMenuScreen::currentSplash], v15 * 0.71, v16 - 15, 0xFFFFFF00, -20, (float)(powf(sin(v17 * 3.14 * 2.3), 4.0) * 0.06) + 1.3, 1, (float)this->width * 0.3125);
	Screen::render(a2, a3, a4);
}
void Touch::StartMenuScreen::init(){
	this->playButton.init(this->minecraft);
	this->playOnRealmsButton.init(this->minecraft);
	this->settingsButtonMaybe = new ImageWithBackground(4);
	IntRectangle v8, v12;
	ImageDef v13;
	//v13.field_0 = 120; wat *(_QWORD *)&v13.field_0 = 120i64;
	v12.width = 0x00000008; //XXX *(_QWORD *)&v12.width = 0x4300000008i64;
	v12.height = 0x43;
	v13.field_8 = 0x00000008; //XXX *(_QWORD *)&v13.field_8 = 0x4300000008i64;
	v13.width = 0x43;
	v12.minX = 112;
	v12.minY = 0;
	v8.minX = 0x78;
	v8.minY = 0;
	v8.width = 8;
	v8.height = 0x43;
	this->settingsButtonMaybe->init(this->minecraft->texturesPtr, 32, 32, v12, v8, 2, 2, "gui/spritesheet.png");
	v13.field_1C = 1;
	v13.field_20 = 1;
	v13.field_0 = ""; //*(_QWORD *)&v13.field_0 = (unsigned int)&_used_as_empty_string__[8];
	v13.field_4 = 0;
	v13.field_8 = 0x00000000;
	v13.width = 16;
	v13.height = 16;
	v13.field_14 = 0;
	v13.field_18 = 0;
	v13.field_24 = 0;
	v13.field_0 = "gui/touchgui.png";
	v13.field_24 = 1;
	v13.width = 22;
	v13.field_18 = 0;
	v13.height = 21;
	v13.field_14 = 218;
	v13.field_1C = 22;
	v13.field_20 = 21;
	this->settingsButtonMaybe->setImageDef(v13, 0);
	this->settingsButtonMaybe->width = 32;
	this->settingsButtonMaybe->height = 32;
	this->settingsButtonMaybe->setupPositions();
	this->buttons.emplace_back(&this->playButton);
	this->buttons.emplace_back(&this->playOnRealmsButton);
	this->buttons.emplace_back(this->settingsButtonMaybe);
	this->field_2C.emplace_back(&this->playButton);
	this->field_2C.emplace_back(&this->playOnRealmsButton);
	this->field_2C.emplace_back(this->settingsButtonMaybe);
	this->field_138 = "\x0fMojang AB";
	this->field_13C = Common::getGameVersionString();
	this->playOnRealmsButton.active = 0;
	this->playButton.active = 0;
}

void Touch::StartMenuScreen::setupPositions(){
	TextureData* data = this->minecraft->texturesPtr->loadAndGetTextureData("gui/title.png");
	if(data){
		this->minecraft->texturesPtr->loadAndBindTexture("gui/title.png");
		int32_t width = this->width;
		float v8 = data->width;
		int32_t td_height = data->height;
		this->field_144 = 12;
		float v10 = v8*0.5;
		if(width*0.5 <= v8*0.5){
			v10 = width*0.5;
		}
		this->field_148 = v10+v10;
		this->field_140 = (float)(width/2) - v10;
		this->field_14C = ((float)(v10+v10)/v8) * (float)td_height;
	}

	bool_t mco = 1; //TODO this.mojangConnector.isMCOCreateServersEnabled();
	this->setupPlayButtons(mco);
	int32_t posY = this->playOnRealmsButton.posY;
	int32_t v13 = this->playButton.posY;
	int32_t v14 = v13 - (this->height - (this->field_144 + this->field_14C) - (posY + this->playOnRealmsButton.height - v13))/2;

	this->playButton.posY = v13+v14;
	this->playOnRealmsButton.posY = posY+v14;
	this->settingsButtonMaybe->height = 32;
	this->settingsButtonMaybe->width = 32;
	this->settingsButtonMaybe->posX = this->width-this->settingsButtonMaybe->width - 2;
	this->settingsButtonMaybe->posY = this->height-this->settingsButtonMaybe->height - 2;
	int32_t v16 = this->width;
	this->buyButton.posY = this->height - this->buyButton.height - 3;
	this->buyButton.posX = (v16 - this->buyButton.width)/2;
}
bool_t Touch::StartMenuScreen::handleBackEvent(bool_t){
	this->minecraft->quit();
	return 1;
}
void Touch::StartMenuScreen::tick(){
	this->_updateLicense();
}
bool_t Touch::StartMenuScreen::isInGameScreen(){
	return 0;
}
void Touch::StartMenuScreen::buttonClicked(struct Button* button) {
	if(button->buttonID == this->playButton.buttonID) {
		this->minecraft->setScreen(new PlayScreen(1));
		return;
	}
	if(button->buttonID == this->playOnRealmsButton.buttonID){
		this->minecraft->setScreen(new PlayScreen(0));
		return;
	}
	if(button->buttonID == this->settingsButtonMaybe->buttonID){
		this->minecraft->setScreen(new OptionsScreen(0));
		return;
	}
	if(button->buttonID == this->buyButton.buttonID){
		this->minecraft->platform()->buyGame();
	}
}
