//
//  ControlGroup.hpp
//  Pong
//
//  Created by John Geiger on 7/8/22.
//
#pragma once

#ifndef ControlGroup_hpp
#define ControlGroup_hpp

#include <vector>
#include <list>
#include <memory>
#include "BaseControl.hpp"
#include "Margins.hpp"

namespace Torti {

///
/// Contains a list of controls and their margins, automatically laying them out as they're added to the ControlGroup
///
class ControlGroup : public BaseControl
{
private:
    enum Direction { VERTICAL, HORIZONTAL };
    using IControlPtr = std::shared_ptr<IControl>;
    
    std::vector<IControlPtr> mControls;
    std::vector<Margins> mMargins;
    Direction mDirection;
    
    // Space taken up by all controls, including their margins
    int mUsedWidth;
    int mUsedHeight;
    
public:
    ControlGroup(int width, int height, Point position)
        : BaseControl(width, height, position),
          mDirection(VERTICAL),
          mUsedWidth(0),
          mUsedHeight(0)
    { mControls = std::vector<IControlPtr>(); mMargins = std::vector<Margins>(); }
    virtual ~ControlGroup() { };
    
    bool PushControl(IControlPtr ctrl, Margins m);
    bool RemoveControl(IControlPtr ctrl);
    
    // IControl implementation
    virtual void VOnRender(double fTime, float fElapsedTime) override;
    virtual void VOnRestore() override;
    virtual void VOnLostDevice() override;
    virtual void VOnUpdate(int deltaMilliseconds) override;
    virtual bool VOnAppMessage(AppMessage msg) override { return false; };

protected:
    virtual bool VCheckIfCtrlFits(IControlPtr ctrl, Margins m);
    virtual void VIncreaseUsedSpace(IControlPtr ctrl, Margins m);
    virtual void VRecalculatePositions();
    
    int GetEffectiveHeight(IControlPtr ctrl, Margins m);
    int GetEffectiveWidth(IControlPtr ctrl, Margins m);
    
    static bool SortByEffectiveSize(const std::pair<IControlPtr, int> &a, const std::pair<IControlPtr, int> &b);
};

}
#endif /* ControlGroup_hpp */
