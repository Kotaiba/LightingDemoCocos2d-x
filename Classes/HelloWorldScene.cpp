#include "HelloWorldScene.h"
#include "EffectSprite/LightEffect.h"
#include "EffectSprite/EffectSprite.h"
#include "EffectSprite/LightsHolder.h"
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

bool HelloWorld::init()
{
    if (!Layer::init())
        return false;
    
    _darkValue=Color3B(55, 55, 55);
    _screenW = Director::getInstance()->getWinSize().width;
    _screenH = Director::getInstance()->getWinSize().height;
    _scale = _screenW / 1920;
    
    _effect = LightEffect::create();
    _effect->retain();
    _lightPos = Vec3(_screenW-100, _screenH-100, 100);
    _effect->setLightPos(_lightPos);
    _effect->setLightCutoffRadius(400);
    _effect->setLightHalfRadius(.8);
    _effect->setBrightness(2.0);
    _effect->setLightColor(Color3B(255, 255, 255));
    _lightSprite = Sprite::create("res/lightbulb.png");
    _lightSprite->setPosition(_screenW-100,  _screenH-100);
    this->addChild(_lightSprite,50);
    
    //shivering effect for the light
  //  this->runAction(RepeatForever::create((Sequence::create(DelayTime::create(0.01),CallFunc::create(CC_CALLBACK_0(LightEffect::setBrightness, _effect,1.7)),DelayTime::create(0.01),CallFunc::create(CC_CALLBACK_0(LightEffect::setBrightness, _effect,2)), NULL))));
 
    {
        _effect2 = LightEffect::create();
        _effect2->retain();

        _effect2->setLightPos(Vec3(_screenW/4, _screenH/5, 140));
        _effect2->setLightCutoffRadius(5000);
        _effect2->setBrightness(2.0);
        _effect2->setLightColor(Color3B(0, 0, 255));
     
        Sprite* lightSprite = Sprite::create("res/lightbulb.png");
        lightSprite->setPosition(_screenW/4, _screenH/5);
        this->addChild(lightSprite,50);
        
    }
    {
        _effect3 = LightEffect::create();
        _effect3->retain();
        
        _effect3->setLightPos(Vec3(_screenW/7, _screenH/3, 140));
        _effect3->setLightCutoffRadius(300);
        _effect3->setBrightness(2.0);
        _effect3->setLightColor(Color3B(0, 255, 0));
        Sprite* lightSprite = Sprite::create("res/lightbulb.png");
        lightSprite->setPosition(_screenW/7, _screenH/3);
        this->addChild(lightSprite,50);
    }
  

    initBackground();
  
     auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("res/spritesheet.plist");
    
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= 8; i++)
    {
        sprintf(str, "character/%02d.png", i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    
    auto sprite = EffectSprite::createWithSpriteFrame(animFrames.front());
    
    Animation *animation = Animation::createWithSpriteFrames(animFrames, 1.0f/8);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));
    sprite->setPosition(_screenW / 2.0, _screenH / 2.0 - 75.0 * _scale);

    {
        
        sprite->addEffect(_effect2);
        sprite->addEffect(_effect);
        sprite->addEffect(_effect3);
        
        sprite->initLamp("res/spritesheet_n.png",_darkValue);
        
        
    }
    sprite->setScale(-_scale,_scale);
    
    addChild(sprite,12);
  
    
    auto listerner = EventListenerTouchAllAtOnce::create();
    listerner->onTouchesBegan = CC_CALLBACK_2(HelloWorld::handleTouches, this);
    listerner->onTouchesMoved = CC_CALLBACK_2(HelloWorld::handleTouches, this);
    listerner->onTouchesEnded = CC_CALLBACK_2(HelloWorld::handleTouches, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listerner, this);
    
    
    //keep replacing scene
    this->runAction(Sequence::create(DelayTime::create(.1),CallFunc::create(CC_CALLBACK_0(HelloWorld::restartS, this)), NULL));
    
    return true;
}
void   HelloWorld::restartS(){
    Director::getInstance()->replaceScene(HelloWorld::createScene());
    
}
void HelloWorld::handleTouches(const std::vector<Touch *> &touches, cocos2d::Event *)
{
    for (auto &touch: touches)
    {
        Point pos = touch->getLocation();
        _lightSprite->setPosition(pos);
        _lightPos.set(pos.x, pos.y, _lightPos.z);
        _effect->setLightPos(_lightPos);
   
    }
}


void HelloWorld::initBackground()
{
    addBackgroundTile("res/background_01.png", 0, 100);
    addBackgroundTile("res/background_01.png", 1920, 100);
    addBackgroundTile("res/foreground_01.png", 0, 200, "res/foreground_01_n.png");
    addBackgroundTile("res/foreground_02.png", 1920, 200, "res/foreground_02_n.png");
}


EffectSprite *HelloWorld::addBackgroundTile(const std::string &spriteFile, float offsetX, float speed, const std::string &normalsFile)
{
    auto background = EffectSprite::create(spriteFile);

    if (!normalsFile.empty())
    {
        //addeffects
        background->addEffect(_effect);
        background->addEffect(_effect2);
        background->addEffect(_effect3);
        //init the lights to start the effect
        background->initLamp(normalsFile,_darkValue);
 
    }
    else
    {
        //if no effect keep it dark
       background->setColor(_darkValue);
    }

  
    background->setAnchorPoint(Vec2(0,0));
    background->setScale(_scale);
    addChild(background,10);
    
    
    return background;
}
HelloWorld::HelloWorld(){


}
HelloWorld::~HelloWorld(){

  
}