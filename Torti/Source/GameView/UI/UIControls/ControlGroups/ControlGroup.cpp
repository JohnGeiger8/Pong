//
//  ControlGroup.cpp
//  Pong
//
//  Created by John Geiger on 7/8/22.
//

#include "ControlGroup.hpp"

namespace Torti {

bool ControlGroup::PushControl(IControlPtr ctrl, Margins m)
{
    // Check if control will fit
    bool willFit = VCheckIfCtrlFits(ctrl, m);
    if (!willFit)
        return false;
    
    mControls.push_back(ctrl);
    mMargins.push_back(m);
    VIncreaseUsedSpace(ctrl, m);
    VRecalculatePositions();
        
    return true;
}

bool ControlGroup::RemoveControl(IControlPtr ctrl)
{
    // Get correct controls iterator to erase
    int index = 0;
    std::vector<IControlPtr>::iterator it;
    for (it = mControls.begin(); it != mControls.end(); it++)
    {
        if ((*it) == ctrl)
            break;
        index++;
    }
    
    // Return false if control not found
    if (it == mControls.end())
        return false;
    
    // Get correct margins iterator to erase from margins vector
    int count = 0;
    std::vector<Margins>::iterator marginsIt;
    for (marginsIt = mMargins.begin(); marginsIt != mMargins.end(); marginsIt++)
    {
        if (count == index)
            break;
        count++;
    }
    
    // Update used height/width
    if (mDirection == VERTICAL)
        mUsedHeight -= GetEffectiveHeight(*it, *marginsIt);
    else
        mUsedWidth -= GetEffectiveWidth(*it, *marginsIt);

    // Erase objects
    mControls.erase(it);
    mMargins.erase(marginsIt);

    VRecalculatePositions();
    return true;
}

///
/// Recalculates the positions of all controls based on their dimensions and the margins list, centering along the direction's axis
///
void ControlGroup::VRecalculatePositions()
{
    std::list<std::pair<IControlPtr, int>> ctrls = std::list<std::pair<IControlPtr, int>>();
    for (int i = 0; i < mControls.size(); i++)
    {
        // Get height for horizontal because we're centering around horizontal axis
        int effectiveSize = mDirection == HORIZONTAL ? GetEffectiveHeight(mControls[i], mMargins[i]) : GetEffectiveWidth(mControls[i], mMargins[i]);
        ctrls.push_back(std::pair<IControlPtr, int>(mControls[i], effectiveSize));
    }
    
    // Sort controls by effective size, then determine axis center from largest control
    ctrls.sort(SortByEffectiveSize);
    int center = ctrls.front().second / 2; // center = Largest Ctrl effective size / 2
    
    // Set new control positions
    for (int i = 0; i < mControls.size(); i++)
    {
        int newPosition = mDirection == HORIZONTAL ? mPosition.x : mPosition.y;
        if (i != 0)
        {
            IControlPtr previousCtrl = mControls[i-1];
            Margins previousMargins = mMargins[i-1];
            if (mDirection == HORIZONTAL)
                newPosition = previousCtrl->VGetPosition().x + previousCtrl->VGetWidth() + previousMargins.right;
            else if (mDirection == VERTICAL)
                newPosition = previousCtrl->VGetPosition().y + previousCtrl->VGetHeight() + previousMargins.bottom;
        }
        
        IControlPtr ctrl = mControls[i];
        if (mDirection == HORIZONTAL)
            ctrl->VSetPosition(Point(newPosition + mMargins[i].left, mPosition.y + center - ctrl->VGetHeight() / 2));
        else
            ctrl->VSetPosition(Point(mPosition.x + center - ctrl->VGetWidth() / 2, newPosition + mMargins[i].top));
    }
}

///
/// Check if the control and its margins will fit in control group with remaining space
///
bool ControlGroup::VCheckIfCtrlFits(IControlPtr ctrl, Margins m)
{
    int ctrlSize = mDirection == VERTICAL ? GetEffectiveHeight(ctrl, m) : GetEffectiveWidth(ctrl, m);
    int availableSpace = mDirection == VERTICAL ? mHeight - mUsedHeight : mWidth - mUsedWidth;
    
    if (ctrlSize > availableSpace)
    {
        printf("Cannot add control: too large");
        return false;
    }
    
    return true;
}

/* IControl implementation */

void ControlGroup::VOnRender(double fTime, float fElapsedTime)
{
    for (const IControlPtr &ctrl : mControls)
    {
        ctrl->VOnRender(fTime, fElapsedTime);
    }
}

void ControlGroup::VOnRestore()
{
    for (const IControlPtr &ctrl : mControls)
    {
        ctrl->VOnRestore();
    }
}

void ControlGroup::VOnLostDevice()
{
    for (const IControlPtr &ctrl : mControls)
    {
        ctrl->VOnLostDevice();
    }
}

void ControlGroup::VOnUpdate(int deltaMilliseconds)
{
    for (const IControlPtr &ctrl : mControls)
    {
        ctrl->VOnUpdate(deltaMilliseconds);
    }
}

/* Util */

int ControlGroup::GetEffectiveWidth(IControlPtr ctrl, Margins m)
{
    return ctrl->VGetWidth() + m.GetTotalXMargins();
}

int ControlGroup::GetEffectiveHeight(IControlPtr ctrl, Margins m)
{
    return ctrl->VGetHeight() + m.GetTotalYMargins();
}

void ControlGroup::VIncreaseUsedSpace(IControlPtr ctrl, Margins m)
{
    if (mDirection == VERTICAL)
        mUsedHeight += (GetEffectiveHeight(ctrl, m));
    else
        mUsedWidth += (GetEffectiveWidth(ctrl, m));
}

bool ControlGroup::SortByEffectiveSize(const std::pair<IControlPtr, int> &a, const std::pair<IControlPtr, int> &b)
{
    return a.second > b.second;
}
}
