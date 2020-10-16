//
//  CustomButton.hpp
//  TestTaskRBlast
//
//  Created by Volha Doroshko on 10/15/20.
//

#ifndef CustomButton_hpp
#define CustomButton_hpp

#include "cocos2d.h"

USING_NS_CC;


enum class ButtonState{
    NONE,
    IDLE,
    PUSHED,
    DRAGOUT,
    LONGPUSH
};

class CustomButton: public Node{
public:
    static CustomButton* create();
    ~CustomButton(){};    
    CustomButton(){};
    bool init();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void setOnTouch(const std::function<void()>& callback);
    
    bool isPointIn(Point point, LayerColor* layerColor);
    
    virtual void changeState(ButtonState state);
    
    ButtonState mCurrentState = ButtonState::NONE;
    Label* mStateLabel = nullptr;
    LayerColor* mButton = nullptr;
    LayerColor* mExpandZone = nullptr;
    LayerColor* mSafeZone = nullptr;
    
    std::function<void()> mOnTouchCallBack = nullptr;
    
};


#endif /* CustomButton_hpp */
