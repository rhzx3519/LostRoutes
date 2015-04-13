#include "HelloWorldScene.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. 加载loading界面精灵帧缓存

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/loading_texture.plist");
    
    auto bg = TMXTiledMap::create("map/red_bg.tmx");
    this->addChild(bg);
    
    auto logo = Sprite::createWithSpriteFrameName("logo.png");
    this->addChild(logo);
    logo->setPosition(cocos2d::Vec2(visibleSize.width/2 , visibleSize.height/2));
    
    auto sprite = Sprite::createWithSpriteFrameName("loding4.png");
    this->addChild(sprite);
    sprite->setPosition(logo->getPosition() - Vec2(0, logo->getContentSize().height/2+30));
    
    /////////////////////////////动画开始//////////////////////////////
    Animation* animation = Animation::create();
    for (int i = 1; i <= 4; i++) {
        __String *frameName = __String::createWithFormat("loding%d.png",i);
        log("frameName = %s",frameName->getCString());
        SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
        animation->addSpriteFrame(spriteFrame);
    }
    
    animation->setDelayPerUnit(0.5f);
    animation->setRestoreOriginalFrame(true);
    
    Animate* action = Animate::create(animation);
    sprite->runAction(RepeatForever::create(action));
    ////////////////////////////动画结束////////////////////////////
    
    
    ///////////////////////////异步加载纹理缓存/////////////////////
    m_nNumberOfLoaded = 0;
    
    Director::getInstance()->getTextureCache()->addImageAsync("texture/home_texture.png",
                                                              CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));
    
    Director::getInstance()->getTextureCache()->addImageAsync("texture/setting_texture.png",
                                                              CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));
    
    Director::getInstance()->getTextureCache()->addImageAsync("texture/gameplay_texture.png",
                                                              CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));
    
    _loadingAudioThread = new std::thread(&HelloWorld::loadingAudio,this);
    /////////////////////////////异步加载纹理缓存结束/////////////////////
    
    
    return true;
}

void HelloWorld::loadingTextureCallBack(cocos2d::Texture2D *texture)
{
    switch (m_nNumberOfLoaded++) {
        case 0:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/home_texture.plist", texture);
            log("home texture ok.");
            break;
        case 1:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/setting_texture.plist",texture);
            log("setting texture ok.");
            break;
        default:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/gameplay_texture.plist",texture);
            log("gameplay texture ok.");
            // 第一个参数是回调，第二个参数是中断事件间隔，第三个参数是回调函数会被执行repeat+1次,kCCRepeatForever时无限次回调;第四个参数时第一次调用延迟时间
            this->schedule(schedule_selector(HelloWorld::delayCall), 1, 1, 3);
            break;
    }
}

void HelloWorld::delayCall(float dt)
{
    log("HelloWorld::delayCall");
}

void HelloWorld::loadingAudio()
{
    log("loading audio.");
    //初始化音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music_1);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music_2);
    
}

void HelloWorld::onExit()
{
    Layer::onExit();
    _loadingAudioThread->join();
    CC_SAFE_DELETE(_loadingAudioThread);
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("texture/loading_texture.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("texture/loading_texture.png");
    this->unschedule(schedule_selector(HelloWorld::delayCall));
}

