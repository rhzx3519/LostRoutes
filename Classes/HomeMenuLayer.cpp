//
//  HomeMenuLayer.cpp
//  LostRoutes
//
//  Created by Louzhenghao on 15/4/13.
//
//

#include "HomeMenuLayer.h"

USING_NS_CC;

Scene* HomeMenuLayer::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HomeMenuLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool HomeMenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto bg = TMXTiledMap::create("map/red_bg.tmx");
    this->addChild(bg);
    
    auto top = Sprite::createWithSpriteFrameName("home-top.png");
    top->setPosition(Vec2(visibleSize.width/2 , visibleSize.height - top->getContentSize().height/2));
    this->addChild(top);
    
    auto end = Sprite::createWithSpriteFrameName("home-end.png");
    end->setPosition(Vec2(visibleSize.width/2, end->getContentSize().height/2));
    this->addChild(end);
    
    //开始菜单
    auto startSpriteNormal = Sprite::createWithSpriteFrameName("home.button.start.png");
    auto startSpriteSelected = Sprite::createWithSpriteFrameName("home.button.start-on.png");
    auto startMenuItem = MenuItemSprite::create(startSpriteNormal, startSpriteSelected,
                        CC_CALLBACK_1(HomeMenuLayer::menuItemCallBack, this));
    startMenuItem->setTag(ActionType::MenuItemStart);
    
    //设置菜单
    auto settingSpriteNormal = Sprite::createWithSpriteFrameName("home.button.setting.png");
    auto settingSpriteSelected = Sprite::createWithSpriteFrameName("home.button.setting-on.png");
    auto settingMenuItem = MenuItemSprite::create(settingSpriteNormal,settingSpriteSelected,
                        CC_CALLBACK_1(HomeMenuLayer::menuItemCallBack,this));
    settingMenuItem->setTag(ActionType::MenuItemSetting);
    
    //帮助菜单
    auto helpSpriteNormal = Sprite::createWithSpriteFrameName("home.button.help.png");
    auto helpSpriteSelected = Sprite::createWithSpriteFrameName("home.button.help-on.png");
    auto helpMenuItem = MenuItemSprite::create(helpSpriteNormal, helpSpriteSelected,
                        CC_CALLBACK_1(HomeMenuLayer::menuItemCallBack, this));
    helpMenuItem->setTag(ActionType::MenuItemHelp);
    
    auto mu = Menu::create(startMenuItem,settingMenuItem,helpMenuItem, NULL);
    
    mu->setPosition(visibleSize.width/2 , visibleSize.height/2 );
    mu->alignItemsVertically();
    this->addChild(mu);
    
    return true;
}

void HomeMenuLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("HomeMenuLayer::onEnterTransitionDidFinish");
    if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1,true);
    }
}

void HomeMenuLayer::menuItemCallBack(cocos2d::Ref *pSender)
{
    if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
        SimpleAudioEngine::getInstance()->playEffect(sound_1);
    }
    
    Scene* tsc = nullptr;
    
    MenuItem* menuItem = (MenuItem*)pSender;
    log("MenuItem Tag = %d",menuItem->getTag());
    switch (menuItem->getTag()) {
        case ActionType::MenuItemStart :
            log("Enter start scene.");
            break;
        case ActionType::MenuItemSetting:
            log("Enter setting scene.");
            break;
        default:
            log("Enter help scene.");
            break;
    }
    
}



















