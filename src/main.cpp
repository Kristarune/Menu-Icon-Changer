#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLogoChanger, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto oldLogo = this->getChildByID("main-title");

        if (!oldLogo) {
            log::warn("main-title not found");
            return true;
        }

        auto pos = oldLogo->getPosition();
        auto scale = oldLogo->getScale();

        oldLogo->setVisible(false);

        auto logoPath = Mod::get()->getConfigDir() / "menu-logo.png";

        if (!std::filesystem::exists(logoPath)) {
            log::warn("menu-logo.png not found");

            auto label = CCLabelBMFont::create(
                "Put menu-logo.png in the mod config folder",
                "goldFont.fnt"
            );

            label->setScale(0.3f);
            label->setPosition(pos);

            this->addChild(label);

            return true;
        }

        auto texture =
            CCTextureCache::sharedTextureCache()->addImage(
                logoPath.string().c_str()
            );

        if (!texture) {
            log::error("Failed to load menu-logo.png");
            return true;
        }

        auto logo = CCSprite::createWithTexture(texture);

        if (!logo) {
            log::error("Failed to create sprite");
            return true;
        }

        logo->setPosition(pos);
        logo->setScale(scale);

        this->addChild(logo);

        return true;
    }
};
