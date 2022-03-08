//
//  EventManager.hpp
//  Torti
//
//  Created by John Geiger on 3/4/22.
//
#pragma once

#ifndef EventManager_hpp
#define EventManager_hpp

#include <list>
#include <map>
#include <memory>
#include "FastDelegate.h"
#include "EventData.hpp"

namespace Torti {

using EventListenerDelegate = fastdelegate::FastDelegate1<IEventDataPtr>;

///
/// Top level interface for the Event Manager. Manages adding, removing, and processing of all events.
///
class IEventManager
{
public:
    enum eConstants { kINIFINITE = 0xffffffff };
    
    explicit IEventManager(const char* pName, bool setAsGlobal);
    virtual ~IEventManager();
    
    ///
    /// Registers delegate function that will be called when event type is triggered.
    /// Returns true if successful.
    ///
    virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
    
    ///
    /// Removes a delegate/event type pairing from the internal tables.
    /// Returns false if pairing wasn't found.
    ///
    virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
    
    ///
    /// Fires off event NOW. Bypasses the event queue and immediately calls all
    ///   delegate functions registered for the event.
    /// Returns true if delegate functions exist? FIXME: when does it return true?
    ///
    virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const = 0;
    
    ///
    /// Fires off event. Adds event to event queue and calls the delegate function on
    ///   the next call to VTickVUpdate(), assuming there's enough time.
    /// Returns true if delegate functions exist? FIXME: when does it return true?
    ///
    virtual bool VQueueEvent(const IEventDataPtr& pEvent) const = 0;
    
    ///
    /// Finds next available instance of named event type and remove it from the
    ///   processing queue. This may be done up to the point that it's actively being
    ///   processed, i.e. when it's safe to happen during event processing itself.
    /// If allOfType is true, then all events of type are cleared from queue.
    /// Returns true if event was found and removed, false otherwise.
    ///
    virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;
    
    ///
    /// Allows for processing of any queued messages, optionally specify a processing
    ///   time limit so that the event processing does not take too long. Note the
    ///   danger of using this artificial limiter is that all messages may not be
    ///   processed.
    /// Returns true if all messages were processed, false otherwise (timeout).
    ///
    virtual bool VTickVUpdate(unsigned long maxMillis = kINIFINITE) = 0;
    
    ///
    /// Getter for the main global event manager. This is the event manager that is used
    ///   by the majority of the engine, though you can define separate, non-global event
    ///   managers. It's invalid to have more than one global event manager.
    ///
    static IEventManager* GetGlobalEventManager();
};

const unsigned int EVENTMANAGER_NUM_QUEUES = 2;
///
/// Implements IEventManager interface. Handles all events and event listeners.
///
class EventManager : public IEventManager
{
    using EventListenerList = std::list<EventListenerDelegate>;
    using EventListenerMap = std::map<EventType, EventListenerList>;
    using EventQueue = std::list<IEventDataPtr>;
    
private:
    EventListenerMap mEventListeners;
    EventQueue mQueues[EVENTMANAGER_NUM_QUEUES];
    int mActiveQueue; // Index of actively processing queue; events enqueue
                      // to the opposing queue.
    
public:
    explicit EventManager(const char* pName, bool setAsGlobal);
    virtual ~EventManager() { }
    
    virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type);
    virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);
    
    virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const;
    virtual bool VQueueEvent(const IEventDataPtr& pEvent);
    virtual bool VAbortEvent(const EventType& type, bool allOfType = false);
    
    virtual bool VTickVUpdate(unsigned long maxMillis = kINIFINITE);
};


} // namespace Torti

#endif /* EventManager_hpp */
