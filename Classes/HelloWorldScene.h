#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class LightEffect;
class EffectSprite;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
        void   restartS();
    HelloWorld();
      ~HelloWorld();
protected:
    void initBackground();
    EffectSprite *addBackgroundTile(const std::string &spriteFile, float offsetX, float speed, const std::string &normalsFile = std::string());
    void handleTouches(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused);
    
    cocos2d::Vec3 _lightPos;
    LightEffect *_effect;
    LightEffect *_effect2;
    LightEffect *_effect3;
 

    cocos2d::Sprite *_lightSprite;
    Color3B _darkValue;
    float _scale, _screenW, _screenH;
};

#endif // __HELLOWORLD_SCENE_H__
