//
//  EventData.hpp
//  Pong
//
//  Contains the declarations and definitions for IEventData, BaseEventData, and
//  several common event types deriving from these classes.
//
//  Created by John Geiger on 3/5/22.
//

#ifndef EventData_hpp
#define EventData_hpp

#include <memory>

namespace Torti {

class IEventData;

using IEventDataPtr = std::shared_ptr<IEventData>;
using EventType = unsigned long;

//
// Top-level interface class for event data being sent by Event Manager.
//
class IEventData
{
public:
    virtual const EventType& VGetEventType() const = 0;
    virtual float VGetTimestamp() const = 0;
//    virtual void VSerialize(std::ostream& out) const = 0;
    virtual IEventDataPtr VCopy() const = 0;
    virtual const char* GetName() const = 0;
};

//
// Base Event Data class to be inherited from when creating custom event data.
//
class BaseEventData : public IEventData
{
    const float mTimestamp;
    
public:
    explicit BaseEventData(const float timestamp = 0.0f) :
        mTimestamp(timestamp) { }
    virtual ~BaseEventData() { }
    
    // Returns the type of the event
    virtual const EventType& VGetEventType() const = 0;
    
    float VGetTimestamp() const { return mTimestamp; }
    
    // Serializing for network out.
//    virtual void VSerialize(std::ostrstream &out) const { }
};

/// Commonly needed Event Data classes

//
// Communicates an update is needed, sent out each game tick.
//
class EventData_UpdateTick : public BaseEventData
{
    int mDeltaMs;

public:
    static const EventType sk_EventType;

    explicit EventData_UpdateTick(const int deltaMilliseconds)
        : mDeltaMs(deltaMilliseconds)
    { }

    virtual const EventType& VGetEventType() const
    {
        return sk_EventType;
    }

    virtual IEventDataPtr VCopy() const
    {
        return IEventDataPtr(new EventData_UpdateTick(mDeltaMs));
    }

//    virtual void VSerialize(std::ostream &out)
//    {
//        printf("You should not be serializing update ticks!");
//    }

    virtual const char* GetName() const
    {
        return "EventData_UpdateTick";
    }
};

// FIXME: Implement
////
//// Communicates that a sound should be played
////
//class EvtData_PlaySound : public ScriptEvent
//{
//    std::string m_soundResource;
//
//public:
//    static const EventType sk_EventType;
//
//    EvtData_PlaySound(void) { }
//    EvtData_PlaySound(const std::string& soundResource)
//        : m_soundResource(soundResource)
//    {
//    }
//
//    virtual const EventType& VGetEventType(void) const
//    {
//        return sk_EventType;
//    }
//
//    virtual IEventDataPointer VCopy() const
//    {
//        return IEventDataPointer(GCC_NEW EvtData_PlaySound(m_soundResource));
//    }
//
//    virtual void VSerialize(std::ostream& out) const
//    {
//        out << m_soundResource;
//    }
//
//    virtual void VDeserialize(std::istream& in)
//    {
//        in >> m_soundResource;
//    }
//
//    const std::string& GetResource(void) const
//    {
//        return m_soundResource;
//    }
//
//    virtual const char* GetName(void) const
//    {
//        return "EvtData_PlaySound";
//    }
//
//    virtual bool VBuildEventFromScript(void);
//
//    EXPORT_FOR_SCRIPT_EVENT(EvtData_PlaySound);
//};

//
// Indicates when a new game is started.
//
class EventData_EnvironmentLoaded : public BaseEventData
{
public:
    static const EventType sk_EventType;

    EventData_EnvironmentLoaded() { }
    virtual const EventType& VGetEventType() const { return sk_EventType; }
    virtual IEventDataPtr VCopy() const
        { return IEventDataPtr(new EventData_EnvironmentLoaded()); }
    virtual const char* GetName() const { return "EventData_EnvironmentLoaded";  }
};

} // namespace Torti

#endif /* EventData_hpp */
