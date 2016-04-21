/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */

#ifndef _EFFECT_H_
#define _EFFECT_H_


#include "cocos2d.h"


class Effect : public cocos2d::Ref
{
public:
    cocos2d::GLProgramState* getGLProgramState() const { return _glprogramstate; }
 
    Effect();
  virtual  ~Effect();
protected:
    bool initGLProgramState(const std::string &fragmentFilename);

    cocos2d::GLProgramState* _glprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::string _fragSource;
    cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

#endif
