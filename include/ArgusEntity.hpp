#ifndef ARGUS_ENTITY_HPP
#define ARGUS_ENTITY_HPP


/**
 * ----- Entity Class -----
 * Is a 'bundle' of components with no real use itself other than a wrapper.
 * Entity is not meant to be inherited or extended, to add functionality to entities,
 * add components to them.
 */


#include <vector>

#include "ArgusTypes.hpp"
#include "ArgusComponent.hpp"


// Entity can NOT be inherited

class Entity final
{
    private:
        friend class Engine;
        std::vector<Component*> components;
        
        // Use private constructor to have better encapsulation

        
    public:
        
        Entity() = default;

        // Get reference to components
        const std::vector<Component*>& getComponents() const
        {
            return components;
        }

        template <typename T>
        T* getComponent()
        {
            for (auto* comp : components)
            {
                T* result = dynamic_cast<T*>(comp);
                if (result) return result;
            }
            return nullptr;
        }


        // TODO: Add definition in .cpp
        void addComponent(Component* comp);

        void Init()
        {
            for (auto& comp : components)
            {
                comp->Init();
            }
            for (auto& comp : components)
            {
                comp->Ready();
            }
            
        }

        ~Entity()
        {
            for (auto* comp : components)
            {
                delete comp;
            }
            components.clear();
        }

        
};

#endif