//
//  CustomButton.cpp
//  TestTaskRBlast
//
//  Created by Volha Doroshko on 10/15/20.
//

#include "CustomButton.hpp"

CustomButton* CustomButton::create(){
    auto ptr = new CustomButton();
    if(ptr && ptr->init()){
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

bool CustomButton::init(){
    if(!Node::init()){ return false; }
    
    
    mSafeZone = LayerColor::create(Color4B::RED, 200, 150);
    mSafeZone->setPosition(-mSafeZone->getContentSize().width/2,-mSafeZone->getContentSize().height/2);
    mSafeZone->setVisible(false);
    addChild(mSafeZone);
    
    mExpandZone = LayerColor::create(Color4B::BLUE, 150, 100);
    mExpandZone->setPosition(-mExpandZone->getContentSize().width/2,-mExpandZone->getContentSize().height/2);
    mExpandZone->setVisible(false);
    addChild(mExpandZone);
    
    mButton = LayerColor::create(Color4B::GREEN, 100, 50);
    mButton->setPosition(-mButton->getContentSize().width/2,-mButton->getContentSize().height/2);
    addChild(mButton);
    
    
    
    mStateLabel = Label::create();
    mStateLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    mStateLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    mStateLabel->setTextColor(Color4B::WHITE);
    mStateLabel->setPosition(0,-mSafeZone->getContentSize().height/2-20);
    mStateLabel->setString("IDLE");
    addChild(mStateLabel);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = CC_CALLBACK_2(CustomButton::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(CustomButton::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(CustomButton::onTouchEnded,this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,mButton);
    
    return true;
}

bool CustomButton::onTouchBegan(Touch* touch, Event* event)
{
    auto point = touch->getLocationInView();
    if(isPointIn(point, mButton) || isPointIn(point, mExpandZone)){
        if(mOnTouchCallBack)
        {
            mOnTouchCallBack();
        }
        changeState(ButtonState::PUSHED);
        return true;
    }
    return false;
}

void CustomButton::onTouchMoved(Touch* touch, Event* event)
{
    auto point = touch->getLocationInView();
    if (isPointIn(point, mButton) || isPointIn(point, mExpandZone)){
        if(mCurrentState == ButtonState::DRAGOUT)
        {
            changeState(ButtonState::PUSHED);
        }
    }
    else if (isPointIn(point, mSafeZone)){
        changeState(ButtonState::DRAGOUT);
    }
    else
    {
        changeState(ButtonState::IDLE);
    }
}

void CustomButton::onTouchEnded(Touch* touch, Event* event)
{
    changeState(ButtonState::IDLE);
}

void CustomButton::setOnTouch(const std::function<void()>& callback){
    mOnTouchCallBack = callback;
}

bool CustomButton::isPointIn(Point point, LayerColor* layerColor)
{
    point = Director::getInstance()->convertToGL(point);
    point = PointApplyAffineTransform(point, layerColor->getWorldToNodeAffineTransform());
    auto size = layerColor->getContentSize();
    auto rect =  Rect(0, 0, size.width, size.height);
    return rect.containsPoint(point);
}

void CustomButton::changeState(ButtonState state)
{
    
    if(mCurrentState != state)
    {
        switch (state) {
            case ButtonState::IDLE:
            {
                mCurrentState = ButtonState::IDLE;
                mStateLabel->setString("IDLE");
            }
                break;
            case ButtonState::PUSHED:
            {
                mCurrentState = ButtonState::PUSHED;
                mStateLabel->setString("PUSHED");
            }
                break;
            case ButtonState::DRAGOUT:
            {
                if(mCurrentState == ButtonState::PUSHED )
                {
                    mCurrentState = ButtonState::DRAGOUT;
                    mStateLabel->setString("DRAGOUT");
                }
            }
                break;
            default:
                break;
        }
    }
}
