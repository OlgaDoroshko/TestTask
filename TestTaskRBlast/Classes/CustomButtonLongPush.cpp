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
    if(state == ButtonState::PUSHED && getUTCTime()-mTimeStart>mTimeOut && mTimeStart != 0)
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
                if(mOnTouchCallBack)
                {
                    mOnTouchCallBack();
                }
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
                    stopTimer();
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
    mTimeStart = getUTCTime();
    mTimerLabel->setVisible(true);
}

void CustomButtonLongPush::stopTimer()
{
    mTimerLabel->setVisible(false);
    mTimerLabel->setString("0");
    unscheduleUpdate();
    mTimeStart = 0;
}

void CustomButtonLongPush::update(float delta){
    auto timeFromStart = getUTCTime()-mTimeStart;
        mTimerLabel->setString(std::to_string(timeFromStart));
        if(timeFromStart>mTimeOut)
        {
            changeState(ButtonState::LONGPUSH);
        }
}

int64_t CustomButtonLongPush::getUTCTime(){
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
}
