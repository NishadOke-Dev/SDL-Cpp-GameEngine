#ifndef ARGUS_BUS_HPP
#define ARGUS_BUS_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <typeindex>
#include <map>
#include <algorithm>

/**
 * Event can be extended to create custom events
 */

struct Event
{
    virtual ~Event() = default;
};

using EventCallback = std::function<void(Event*)>;

using SubscriptionID = size_t;

class Bus final
{
    private:
        friend class Engine;

        
        struct CallbackWrapper {
            SubscriptionID id;
            EventCallback func;
        };
        
        std::map<std::type_index, std::vector<CallbackWrapper>> subscribers;
        std::vector<Event*> eventQueue;
        SubscriptionID nextID = 0;


        void Dispatch()
        {
            for (auto* event : eventQueue)
            {
                auto it = subscribers.find(typeid(*event));
                if (it != subscribers.end())
                {
                    for (auto& wrapper : it->second)
                    {
                        wrapper.func(event);
                    }
                }
            }
            Clear();
        }

        void Clear()
        {
            for (auto* e : eventQueue) delete e;
            eventQueue.clear();
        }

    public:
        
        template <typename T>
        SubscriptionID Subscribe(EventCallback callback)
        {
            SubscriptionID id = nextID++;
            subscribers[typeid(T)].push_back({id, [callback](Event* e)
                {
                    callback(static_cast<T*>(e));
                }
            }
            );

            return id;
        }

        void Unsubscribe(SubscriptionID id)
        {
            for (auto& [type, list] : subscribers)
            {
                auto it = std::remove_if(list.begin(), list.end(), [id](const CallbackWrapper& w)
                    {
                        return w.id == id;
                    }
                );
                if (it != list.end())
                {
                    list.erase(it, list.end());
                    return;
                }
            }
        }

        template <typename T, typename...Args>
        void Publish(Args&&...args)
        {
            eventQueue.push_back(new T(std::forward<Args>(args)...));
        }

        

 

};





#endif