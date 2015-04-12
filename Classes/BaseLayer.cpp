//
//  BaseLayer.cpp
//  LostRoutes
//
//  Created by Louzhenghao on 15/4/12.
//
//

#include "BaseLayer.h"

USING_NS_CC;

bool BaseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = TMXTiledMap::create("map/red_bg.tmx");
    this->addChild(bg);
    
    //眼镜精灵
    auto glassesSprite  = Sprite::createWithSpriteFrameName("setting.glasses.png");
    glassesSprite->setPosition(Vec2(visibleSize.width - glassesSprite->getContentSize().width/2,160));
    this->addChild(glassesSprite);
    
    //手套精灵
    auto glovesSprite = Sprite::createWithSpriteFrameName("setting.hand.png");
    glovesSprite->setPosition(Vec2(glovesSprite->getContentSize().width/2, 60));
    this->addChild(glovesSprite);
    
    //ok菜单
    auto okNormal = Sprite::createWithSpriteFrameName("setting.button.ok.png");
    auto okSelected = Sprite::createWithSpriteFrameName("setting.button.ok-on.png");
    
    auto okMenuItem = MenuItemSprite::create(okNormal, okSelected);
    auto menu = Menu::create(okMenuItem,NULL);
    menu->setPosition(Vec2(visibleSize.width - menu->getContentSize().width/2 + 60 , 60));
    this->addChild(menu);
    
    return true;
}

void BaseLayer::menuBackCallback(cocos2d::Ref &pSender)
{
    Director::getInstance()->popScene();
    if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
        SimpleAudioEngine::getInstance()->playEffect(sound_1);
    }
}

void BaseLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("BaseLayer onEnterTransitionDidFinish");
    UserDefault *defaults = UserDefault::getInstance();
    if (defaults->getBoolForKey(MUSIC_KEY)) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1,true);
    }
}








