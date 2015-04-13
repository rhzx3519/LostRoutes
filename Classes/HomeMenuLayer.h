//
//  HomeMenuLayer.h
//  LostRoutes
//
//  Created by Louzhenghao on 15/4/13.
//
//


#ifndef __LostRoutes__HomeMenuLayer__
#define __LostRoutes__HomeMenuLayer__

typedef enum{
    MenuItemStart,
    MenuItemSetting,
    MenuItemHelp
} ActionType;

#include <cocos2d.h>

#include "SystemHeader.h"

class HomeMenuLayer : cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    virtual void onEnterTransitionDidFinish() override;
    
    void menuItemCallBack(cocos2d::Ref *pSender);
    
    CREATE_FUNC(HomeMenuLayer);
};

#endif /* defined(__LostRoutes__HomeMenuLayer__) */
