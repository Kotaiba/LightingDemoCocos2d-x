/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */

#ifndef _LIGHTEFFECT_H_
#define _LIGHTEFFECT_H_

#include "Effect.h"


class LightEffect : public cocos2d::Ref
{
public:
    static LightEffect* create();
    
    void setLightPos(const cocos2d::Vec3& pos);
    void setLightColor(const cocos2d::Color3B& color);

    void setBrightness(float value);
    void setLightCutoffRadius(float value);
    void setLightHalfRadius(float value);

    cocos2d::Color3B getLightColor() const { return _lightColor; }
    float getLightCutoffRadius(){return  _lightCutoffRadius;}
    float getLightHalfRadius(){return _lightHalfRadius;}
    float getBrightness(){return _brightness;}
    cocos2d::Vec3 getLightPos(){return _lightPos;}
    
    LightEffect(){}
    ~LightEffect(){
 
    }
protected:
    bool init();

    cocos2d::Vec3 _lightPos;
    cocos2d::Color3B _lightColor;

    float _lightCutoffRadius;
    float _lightHalfRadius;
    float _brightness;

    
   
};

#endif
