//
//  CustomButtonLongPush.hpp
//  TestTaskRBlast
//
//  Created by Volha Doroshko on 10/15/20.
//

#ifndef CustomButtonLongPush_hpp
#define CustomButtonLongPush_hpp


#include "cocos2d.h"
#include "CustomButton.hpp"

USING_NS_CC;

class CustomButtonLongPush: public CustomButton{
public:
    static CustomButtonLongPush* create();
    ~CustomButtonLongPush(){};
private:
    
    CustomButtonLongPush(){};
    bool init() override;
    
    void update(float delta) override;
    void startTimer();
    void stopTimer();
    void changeState(ButtonState state) override;
    static int64_t getUTCTime();
    
    Label* mTimerLabel = nullptr;
    int64_t mTimeStart = 0;
    int mTimeOut = 5;
};


#endif /* CustomButtonLongPush_hpp */
