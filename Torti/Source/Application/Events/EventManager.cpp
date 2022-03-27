//
//  EventManager.cpp
//  Pong
//
//  Created by John Geiger on 3/4/22.
//

#include "EventManager.hpp"

namespace Torti {

static IEventManager* g_pEventManager;

//GenericObjectFactory<IEventData, EventType> g_eventFactory;

IEventManager* IEventManager::GetGlobalEventManager()
{
    assert(g_pEventManager);
    return g_pEventManager;
}

IEventManager::IEventManager(const char* pName, bool setAsGlobal)
{
    if (setAsGlobal)
    {
        if (g_pEventManager)
        {
            printf("Error: Attempting to create two global event managers! The old one will be destroyed and overwritten with this one.");
            delete g_pEventManager;
        }

        g_pEventManager = this;
    }
}

IEventManager::~IEventManager(void)
{
    if (g_pEventManager == this)
        g_pEventManager = NULL;
}

EventManager::EventManager(char const* pName, bool setAsGlobal)
    : IEventManager(pName, setAsGlobal),
      mActiveQueue(0)
{ }

bool EventManager::VAddListener(const EventListenerDelegate &eventDelegate, const EventType &type)
{
    // Find or create the entry
    EventListenerList& eventListenerList = mEventListeners[type];
    for (const EventListenerDelegate& delegate : eventListenerList)
    {
        if (eventDelegate == delegate)
        {
            printf("Warning: attempting to double-register a delegate");
            return false;
        }
    }
    
    eventListenerList.push_back(eventDelegate);
    return true;
}

bool EventManager::VRemoveListener(const EventListenerDelegate &eventDelegate, const EventType &type)
{
    bool success = false;
    
    auto findIt = mEventListeners.find(type);
    if (findIt != mEventListeners.end())
    {
        EventListenerList& listeners = findIt->second;
        for (const EventListenerDelegate& delegate : listeners)
        {
            if (eventDelegate == delegate)
            {
                listeners.remove(delegate);
                success = true;
                // Break because there should never be two of the same delegate in the list
                break;
            }
        }
    }
    
    return success;
}

bool EventManager::VTriggerEvent(const IEventDataPtr &pEvent) const
{
    bool processed = false;
    
    auto findIt = mEventListeners.find(pEvent->VGetEventType());
    if (findIt != mEventListeners.end())
    {
        const EventListenerList& eventListenerList = findIt->second;
        for (const EventListenerDelegate& delegate : eventListenerList)
        {
            delegate(pEvent);
            processed = true;
        }
    }
    
    return processed;
}

bool EventManager::VQueueEvent(const IEventDataPtr &pEvent)
{
    assert(mActiveQueue >= 0);
    assert(mActiveQueue < EVENTMANAGER_NUM_QUEUES);
    
    auto findIt = mEventListeners.find(pEvent->VGetEventType());
    if (findIt != mEventListeners.end())
    {
        mQueues[mActiveQueue].push_back(pEvent);
        return true;
    }
    else
    {
        return false; // No listeners for event, so don't add it to queue
    }
}

bool EventManager::VAbortEvent(const EventType &type, bool allOfType)
{
    assert(mActiveQueue >= 0);
    assert(mActiveQueue > EVENTMANAGER_NUM_QUEUES);
    
    bool success = false;
    EventListenerMap::iterator findIt = mEventListeners.find(type);
    
    if (findIt != mEventListeners.end())
    {
        EventQueue& queue = mQueues[mActiveQueue];
        auto it = queue.begin();
        while (it != queue.end())
        {
            // Removing an item from the queue will invalidate the iterator, so
            //   have it point to the next member. All work inside this loop will
            //   be dones using thisIt.
            auto thisIt = it;
            ++it;
            
            if ((*thisIt)->VGetEventType() == type)
            {
                queue.erase(thisIt);
                success = true;
                if (!allOfType)
                    break;
            }
        }
    }
    
    return success;
}

bool EventManager::VTickVUpdate(unsigned long maxMillis)
{
//    unsigned long currentMs = GetTickCount(); // FIXME: implement this
    unsigned long currentMs = 0;
    unsigned long maxMs = ((maxMillis == IEventManager::kINIFINITE) ?
                           (IEventManager::kINIFINITE) :
                           (currentMs + maxMillis));
    
    // Swap active queues and clear the new queue after the swap.
    int queueToProcess = mActiveQueue;
    mActiveQueue = (mActiveQueue + 1) % EVENTMANAGER_NUM_QUEUES;
    mQueues[mActiveQueue].clear();
    
    // Process the queue
    while (!mQueues[queueToProcess].empty())
    {
        // Pop the front of the queue
        IEventDataPtr pEvent = mQueues[queueToProcess].front();
        mQueues[queueToProcess].pop_front();
        
        const EventType& eventType = pEvent->VGetEventType();
        
        // Find all delegate functions registered for this event
        auto findIt = mEventListeners.find(eventType);
        if (findIt != mEventListeners.end())
        {
            const EventListenerList& eventListeners = findIt->second;
            
            // Call each listener
            for (const EventListenerDelegate& delegate : eventListeners)
            {
                delegate(pEvent);
            }
        }
        
        // Check to see if time ran out
//        currentMs = GetTickCount(); // FIXME: implement
        currentMs = 0;
        if (maxMillis != IEventManager::kINIFINITE && currentMs >= maxMs)
        {
            printf("Event Loop: Aborting event processing; time ran out.");
            break;
        }
    }
    
    // If we couldn't process all the events, push the remaining ones to the new active queue.
    // Note: to proserve sequencing, go back-to-front, inserting them at the head of active.
    bool queueFlushed = (mQueues[queueToProcess].empty());
    if (!queueFlushed)
    {
        while (!mQueues[queueToProcess].empty())
        {
            IEventDataPtr pEvent = mQueues[queueToProcess].back();
            mQueues[queueToProcess].pop_back();
            mQueues[mActiveQueue].push_front(pEvent);
        }
    }
    return queueFlushed;
}

}
