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
    
    std::vector<IControlPtr> controls;
    std::vector<Margins> margins;
    Direction direction;
    
    // Space taken up by all controls, including their margins
    int usedWidth;
    int usedHeight;
    bool isCenteredOnCrossAxis;
    
public:
    ControlGroup(int width, int height, Point position)
        : BaseControl(width, height, position),
          direction(VERTICAL),
          usedWidth(0),
          usedHeight(0),
          isCenteredOnCrossAxis(true)
    { controls = std::vector<IControlPtr>(); margins = std::vector<Margins>(); }
    virtual ~ControlGroup();
    
    bool PushControl(IControlPtr ctrl, Margins m);
    bool RemoveControl(IControlPtr ctrl);
    
    // IControl implementation
    virtual void VOnRender(double fTime, float fElapsedTime);
    virtual void VOnRestore();
    virtual void VOnLostDevice();
    virtual void VOnUpdate(int deltaMilliseconds);
    
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
