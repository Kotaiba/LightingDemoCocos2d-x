

#include "LightsHolder.h"
#include "EffectSprite.h"
#include "LightEffect.h"
USING_NS_CC;


LightsHolder* LightsHolder::create(std::vector<LightEffect*> effectsArray,Sprite* image)
{
    LightsHolder *normalMappedSprite = new (std::nothrow) LightsHolder();
    if (normalMappedSprite && normalMappedSprite->init(effectsArray,image))
    {
        normalMappedSprite->autorelease();
        return normalMappedSprite;
    }
    CC_SAFE_DELETE(normalMappedSprite);
    return nullptr;
}

bool LightsHolder::init(std::vector<LightEffect*> effectsArray,Sprite* image)
{
    if (initGLProgramState("shaders/pointlight.frag"))
    {
        _effectsArray=effectsArray;
        int idx=0;
        
        sprite=image;
        for(auto &ef : _effectsArray) {
            
            if (ef != nullptr)
            {
                
                v3Color[idx]=  Vec3(ef->getLightColor().r, ef->getLightColor().g, ef->getLightColor().b)/255;
                
                lightCutoffRadius[idx]=ef->getLightCutoffRadius();
                lightHalfRadius[idx]=ef->getLightHalfRadius();
                
                Point posRelToSprite = PointApplyAffineTransform(Point(ef->getLightPos().x, ef->getLightPos().y),sprite->getWorldToNodeAffineTransform());
                _lightPos[idx]=Vec3(posRelToSprite.x, posRelToSprite.y, ef->getLightPos().z);
                
                
                brightness[idx]=ef->getBrightness();
            }
            idx++;
        }
        _lightsNumber=idx;
        setLightColor();
        setAmbientLightColor(cocos2d::Color3B(55,55,55));
        setLightCutoffRadius();
        setLightHalfRadius();
        //  setBrightness();
        return true;
    }
    return false;
}


void LightsHolder::setLightColor()
{
    Vec3 test;
    getGLProgramState()->setUniformVec3v("u_lightColor",_lightsNumber, v3Color);
}

void LightsHolder::setAmbientLightColor(const cocos2d::Color3B& color)
{
    _ambientLightColor = color;
    getGLProgramState()->setUniformVec3("u_ambientColor", Vec3(_ambientLightColor.r,_ambientLightColor.g,_ambientLightColor.b)/255.0f/_lightsNumber);
}

void LightsHolder::setBrightness()
{
    int idx=0;
    for(auto &ef : _effectsArray) {
 
        if (ef != nullptr)
        {
            brightness[idx]=ef->getBrightness();
        }
        idx++;
    }
   getGLProgramState()->setUniformFloatv("u_brightness",_lightsNumber, brightness);
}

void LightsHolder::setLightCutoffRadius()
{
    int idx=0;
    for(auto &ef : _effectsArray) {
      
        if (ef != nullptr)
        {
            
            lightCutoffRadius[idx]=ef->getLightCutoffRadius();
         
        }
        idx++;
    }
    getGLProgramState()->setUniformFloatv("u_cutoffRadius",_lightsNumber, lightCutoffRadius);
}

void LightsHolder::setLightHalfRadius()
{
    int idx=0;
    for(auto &ef : _effectsArray) {
    
        if (ef != nullptr)
        {
            
            lightHalfRadius[idx]=ef->getLightHalfRadius();

        }
        idx++;
    }
    getGLProgramState()->setUniformFloatv("u_halfRadius",_lightsNumber, lightHalfRadius);
}

void LightsHolder::prepareForRender(Sprite *_sprite, Texture2D *normalmap)
{
    int idx=0;
    for(auto &ef : _effectsArray) {
     
        if (ef != nullptr)
        {
            Point posRelToSprite = PointApplyAffineTransform(Point(ef->getLightPos().x, ef->getLightPos().y),_sprite->getWorldToNodeAffineTransform());
            _lightPos[idx]=Vec3(posRelToSprite.x, posRelToSprite.y, ef->getLightPos().z);
            brightness[idx]=ef->getBrightness();
    
        }
        idx++;
    }
    
    auto gl = getGLProgramState();

    gl->setUniformVec2("u_contentSize", _sprite->getContentSize());


 

    gl->setUniformVec3v("u_lightPos",_lightsNumber,_lightPos);

    gl->setUniformTexture("u_normals", normalmap);

    SpriteFrame *frame = _sprite->getSpriteFrame();
    Size untrimmedSize = frame->getOriginalSize();
    Size trimmedSize = frame->getRect().size;
    Vec2 framePos = frame->getRect().origin;
    Size texSize = frame->getTexture()->getContentSize();
    
    // set sprite position in sheet
    gl->setUniformVec2("u_spritePosInSheet", Vec2(framePos.x / texSize.width, framePos.y / texSize.height));
    gl->setUniformVec2("u_spriteSizeRelToSheet", Vec2(untrimmedSize.width / texSize.width, untrimmedSize.height / texSize.height));
    
    gl->setUniformFloatv("u_brightness",_lightsNumber, brightness);
    
    gl->setUniformInt("u_spriteRotated", frame->isRotated());
    gl->setUniformInt("u_lightsNumber", _lightsNumber);
    
    // set offset of trimmed sprite
    Vec2 bottomLeft = frame->getOffset() + (untrimmedSize - trimmedSize) / 2;
    Vec2 cornerOffset = frame->isRotated() ? Vec2(bottomLeft.y, bottomLeft.x)
                                           : Vec2(bottomLeft.x, untrimmedSize.height - trimmedSize.height - bottomLeft.y);
    gl->setUniformVec2("u_spriteOffset", cornerOffset);

}
