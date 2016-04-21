
/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */
#include "LightEffect.h"
#include "EffectSprite.h"

USING_NS_CC;


LightEffect* LightEffect::create()
{
    LightEffect *normalMappedSprite = new (std::nothrow) LightEffect();
    if (normalMappedSprite && normalMappedSprite->init())
    {
        normalMappedSprite->autorelease();
        return normalMappedSprite;
    }
    CC_SAFE_DELETE(normalMappedSprite);
    return nullptr;
}

bool LightEffect::init()
{

    setLightColor(cocos2d::Color3B::WHITE);
    setLightCutoffRadius(500.0f);
    setLightHalfRadius(0.5f);
    
    
    return true;

}

void LightEffect::setLightPos(const Vec3 &pos)
{
    _lightPos = pos;
}

void LightEffect::setLightColor(const Color3B &color)
{
    _lightColor = color;
  //  getGLProgramState()->setUniformVec3("u_lightColor", Vec3(_lightColor.r,_lightColor.g,_lightColor.b)/255.0f);
}


void LightEffect::setBrightness(float value)
{
    _brightness = value;
   // getGLProgramState()->setUniformFloat("u_brightness", value);
}

void LightEffect::setLightCutoffRadius(float value)
{
    _lightCutoffRadius = std::max(1.0f, value);
 //   getGLProgramState()->setUniformFloat("u_cutoffRadius", _lightCutoffRadius);
}

void LightEffect::setLightHalfRadius(float value)
{
    _lightHalfRadius = std::max(0.01f, std::min(0.99f, value));
  //  getGLProgramState()->setUniformFloat("u_halfRadius", _lightHalfRadius);
}
