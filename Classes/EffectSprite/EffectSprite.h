/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */

#ifndef _EFFECTSPRITE_H_
#define _EFFECTSPRITE_H_

#include "cocos2d.h"

class LightEffect;
class LightsHolder;
class EffectSprite : public cocos2d::Sprite
{
public:
    static EffectSprite *create(const std::string &filename);
    static EffectSprite *createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
    
    void initLamp(const std::string &normalMapFilename,cocos2d::Color3B darkValue);
    void addEffect(LightEffect *effect) ;
    //multiple lights
    std::vector<LightEffect*> _effectsArray;
protected:
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
    ~EffectSprite();
    
    LightsHolder *_effectHolder = nullptr;
    cocos2d::Texture2D *_normalmap = nullptr;
    
  
};

#endif
