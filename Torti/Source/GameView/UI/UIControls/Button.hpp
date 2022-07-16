//
//  Button.hpp
//  Pong
//
//  Created by John Geiger on 7/9/22.
//
#pragma once

#ifndef Button_hpp
#define Button_hpp

#include <string>
#include "BaseControl.hpp"

namespace Torti {

enum ButtonType
{
    OK_BTN,
    CANCEL_BTN,
    START_BTN,
    RESTART_BTN,
    RESUME_BTN,
    QUIT_BTN
};

class Button : public BaseControl
{
    std::string mButtonText;
    ButtonType mButtonType;
    bool mIsPressed;
    bool mIsFilled;
    
public:
    Button(int width, int height, Point position, std::string text = "", ButtonType button = OK_BTN)
        : BaseControl(width, height, position),
          mButtonText(text),
          mButtonType(button),
          mIsPressed(false),
          mIsFilled(false)
    { }
    
    void SetButtonText(std::string text) { mButtonText = text; }
    void SetButtonType(ButtonType type) { mButtonType = type; }
    void SetPressed(bool pressed) { mIsPressed = pressed; }
    void SetFilled(bool filled) { mIsFilled = filled; }
    
    std::string GetButtonText() { return mButtonText; }
    ButtonType GetButtonType() { return mButtonType; }
    bool IsPressed() { return mIsPressed; }
    bool IsFilled() { return mIsFilled; }
};

}
#endif /* Button_hpp */
