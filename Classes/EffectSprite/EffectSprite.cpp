/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */

#include "EffectSprite.h"
#include "LightEffect.h"
#include "LightsHolder.h"
USING_NS_CC;


EffectSprite *EffectSprite::create(const std::string& filename)
{
    auto ret = new (std::nothrow) EffectSprite;
    if(ret && ret->initWithFile(filename)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}


EffectSprite *EffectSprite::createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)
{
    auto ret = new (std::nothrow) EffectSprite;
    if(ret && ret->initWithSpriteFrame(spriteFrame)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
    
}
void EffectSprite::addEffect(LightEffect *effect) {
    _effectsArray.push_back(effect);
}
void EffectSprite::initLamp(const std::string &normalMapFilename,Color3B darkValue)
{

    if(_effectHolder == nullptr) {
        CC_SAFE_RELEASE(_effectHolder);
        _effectHolder = LightsHolder::create(_effectsArray,this);
        _effectHolder->retain();
        _effectHolder->setAmbientLightColor(darkValue);
        
        _normalmap = cocos2d::Director::getInstance()->getTextureCache()->addImage(normalMapFilename);

        CC_SAFE_RETAIN(_effectHolder);
        setGLProgramState(_effectHolder->getGLProgramState());
    }
   
}


void EffectSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{

    if (_effectHolder!=nullptr&& _effectsArray.size()>0) {
        _effectHolder->prepareForRender(this, _normalmap);
    }
    
    Sprite::draw(renderer, transform, flags);
    renderer->render();
    
}

EffectSprite::~EffectSprite()
{
    


    CC_SAFE_DELETE(_effectHolder);
    CC_SAFE_RELEASE(_effectHolder);
  
}
/*remove

 sprite->setGLProgramState(
 GLProgramState::getOrCreateWithGLProgramName(
 GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP
 )
 );
*/