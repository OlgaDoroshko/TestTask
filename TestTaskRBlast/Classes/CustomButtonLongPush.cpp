//
//  CustomButtonLongPush.cpp
//  TestTaskRBlast
//
//  Created by Volha Doroshko on 10/15/20.
//

#include "CustomButtonLongPush.hpp"

CustomButtonLongPush* CustomButtonLongPush::create(){
    auto ptr = new CustomButtonLongPush();
    if(ptr && ptr->init()){
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

bool CustomButtonLongPush::init(){
    if(!CustomButton::init()){ return false; }
    
    mTimerLabel = Label::create();
    mTimerLabel->setAnchorPoint({0.5f, 0.5f});
    mTimerLabel->setPosition(0,-mSafeZone->getContentSize().height/2-40);
    mTimerLabel->setTextColor(Color4B::RED);
    mTimerLabel->setVisible(false);
    addChild(mTimerLabel);
    
    return true;
}

void CustomButtonLongPush::changeState(ButtonState state)
{
    if(state == ButtonState::PUSHED && mTimerTime/60 > mTimeOut)
    {
        state = ButtonState::LONGPUSH;
    }
    if(mCurrentState != state)
    {
        switch (state) {
            case ButtonState::IDLE:
            {
                mCurrentState = ButtonState::IDLE;
                mStateLabel->setString("IDLE");
                stopTimer();
            }
                break;
            case ButtonState::PUSHED:
            {
                mCurrentState = ButtonState::PUSHED;
                mStateLabel->setString("PUSHED");
                startTimer();
            }
                break;
            case ButtonState::DRAGOUT:
            {
                if(mCurrentState == ButtonState::PUSHED || mCurrentState == ButtonState::LONGPUSH)
                {
                    mCurrentState = ButtonState::DRAGOUT;
                    mTimerLabel->setVisible(false);
                    unscheduleUpdate();
                    mTimerTime = 0;
                    mStateLabel->setString("DRAGOUT");
                }
            }
                break;
            case ButtonState::LONGPUSH:
            {
                mCurrentState = ButtonState::LONGPUSH;
                mStateLabel->setString("LONGPUSH");
            }
                break;
            default:
                break;
        }
    }
}

void CustomButtonLongPush::startTimer()
{
    scheduleUpdate();
}

void CustomButtonLongPush::stopTimer()
{
    mTimerLabel->setVisible(false);
    unscheduleUpdate();
    mTimerTime = 0;
}

void CustomButtonLongPush::update(float delta){
    mTimerTime +=1;
    if(mTimerTime%60 == 0)
    {
        mTimerLabel->setVisible(true);
        mTimerLabel->setString(std::to_string(mTimerTime/60));
        if(mTimerTime/60 >mTimeOut)
        {
            changeState(ButtonState::LONGPUSH);
        }
    }
}
