/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */
#ifndef _LightsHolder_H_
#define _LightsHolder_H_

#include "Effect.h"

class LightEffect;
class LightsHolder : public Effect
{
public:
    static LightsHolder* create( std::vector<LightEffect*> effectsArray,cocos2d::Sprite* image);

    void setLightPos();
    void setLightColor();
    void setAmbientLightColor(const cocos2d::Color3B& color);
    void setBrightness();
    void setLightCutoffRadius();
    void setLightHalfRadius();
    
    void prepareForRender(cocos2d::Sprite *_sprite, cocos2d::Texture2D *normalmap);
    cocos2d::Color3B getAmbientLightColor() const { return _ambientLightColor; }
    std::vector<LightEffect*> _effectsArray;
    LightsHolder(){
        
    }
    ~LightsHolder(){
    
        CC_SAFE_DELETE_ARRAY(v3Color);
        CC_SAFE_DELETE_ARRAY(_lightPos);
        CC_SAFE_DELETE_ARRAY(lightCutoffRadius);
        CC_SAFE_DELETE_ARRAY(lightHalfRadius);
        CC_SAFE_DELETE_ARRAY(brightness);
    }
protected:
    bool init(std::vector<LightEffect*> effectsArray,cocos2d::Sprite* image);
    cocos2d::Sprite* sprite;
    cocos2d::Color3B _ambientLightColor;

    int _lightsNumber=0;
    
    float* brightness = new float[100];
    
    cocos2d::Vec3* v3Color=new cocos2d::Vec3[100];
    cocos2d::Vec3* _lightPos=new cocos2d::Vec3[100];
    
    float* lightCutoffRadius = new float[100];
    float* lightHalfRadius = new float[100];
 

};

#endif
