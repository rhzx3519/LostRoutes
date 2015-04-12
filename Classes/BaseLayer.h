//
//  BaseLayer.h
//  LostRoutes
//
//  Created by Louzhenghao on 15/4/12.
//
//

#ifndef __LostRoutes__BaseLayer__
#define __LostRoutes__BaseLayer__

#include <cocos2d.h>

#include "SystemHeader.h"

class BaseLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    virtual void onEnterTransitionDidFinish();
    
    void menuBackCallback(cocos2d::Ref &pSender);
};

#endif /* defined(__LostRoutes__BaseLayer__) */
