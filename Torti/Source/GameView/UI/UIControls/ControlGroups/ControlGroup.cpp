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
    
    controls.push_back(ctrl);
    margins.push_back(m);
    VIncreaseUsedSpace(ctrl, m);
    VRecalculatePositions();
        
    return true;
}

bool ControlGroup::RemoveControl(IControlPtr ctrl)
{
    for (auto it = controls.begin(); it != controls.end(); it++)
    {
        if ((*it) == ctrl)
            controls.erase(it);
    }
    
    return true;
}

///
/// Recalculates the positions of all controls based on their dimensions and the margins list, centering along the direction's axis
///
void ControlGroup::VRecalculatePositions()
{
    std::list<std::pair<IControlPtr, int>> ctrls = std::list<std::pair<IControlPtr, int>>();
    for (int i = 0; i < controls.size(); i++)
    {
        // Get height for horizontal because we're centering around horizontal axis
        int effectiveSize = direction == HORIZONTAL ? GetEffectiveHeight(controls[i], margins[i]) : GetEffectiveWidth(controls[i], margins[i]);
        ctrls.push_back(std::pair<IControlPtr, int>(controls[i], effectiveSize));
    }
    
    // Sort controls by effective size, then determine axis center from largest control
    ctrls.sort(SortByEffectiveSize);
    int center = ctrls.front().second / 2; // center = Largest Ctrl effective size / 2
    
    // Set new control positions
    for (int i = 0; i < controls.size(); i++)
    {
        int newPosition = 0;
        if (i != 0)
        {
            IControlPtr previousCtrl = controls[i-1];
            Margins previousMargins = margins[i-1];
            if (direction == HORIZONTAL)
                newPosition = previousCtrl->VGetPosition().x + previousCtrl->VGetWidth() + previousMargins.right;
            else if (direction == VERTICAL)
                newPosition = previousCtrl->VGetPosition().y + previousCtrl->VGetHeight() + previousMargins.bottom;
        }
        
        IControlPtr ctrl = controls[i];
        if (direction == HORIZONTAL)
            ctrl->VSetPosition(Point(newPosition + margins[i].left, center - ctrl->VGetHeight() / 2));
        else
            ctrl->VSetPosition(Point(center - ctrl->VGetWidth() / 2, newPosition + margins[i].top));
        
    }
}

///
/// Check if the control and its margins will fit in control group with remaining space
///
bool ControlGroup::VCheckIfCtrlFits(IControlPtr ctrl, Margins m)
{
    int ctrlSize = direction == VERTICAL ? GetEffectiveHeight(ctrl, m) : GetEffectiveWidth(ctrl, m);
    int availableSpace = direction == VERTICAL ? height - usedHeight : width - usedWidth;
    
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
    for (const IControlPtr &ctrl : controls)
    {
        ctrl->VOnRender(fTime, fElapsedTime);
    }
}

void ControlGroup::VOnRestore()
{
    for (const IControlPtr &ctrl : controls)
    {
        ctrl->VOnRestore();
    }
}

void ControlGroup::VOnLostDevice()
{
    for (const IControlPtr &ctrl : controls)
    {
        ctrl->VOnLostDevice();
    }
}

void ControlGroup::VOnUpdate(int deltaMilliseconds)
{
    for (const IControlPtr &ctrl : controls)
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
    if (direction == VERTICAL)
        usedHeight += (GetEffectiveHeight(ctrl, m));
    else
        usedWidth += (GetEffectiveWidth(ctrl, m));
}

bool ControlGroup::SortByEffectiveSize(const std::pair<IControlPtr, int> &a, const std::pair<IControlPtr, int> &b)
{
    return a.second < b.second;
}
}
