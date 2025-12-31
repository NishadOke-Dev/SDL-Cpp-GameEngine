#ifndef ARGUS_ENGINE_HPP
#define ARGUS_ENGINE_HPP




#include <vector>
#include <iostream>
#include "ArgusSystem.hpp"
#include "ArgusComponent.hpp"
#include "ArgusEntity.hpp"
#include "ArgusTypes.hpp"
#include "ArgusBus.hpp"



/**
 * ----- Engine -----
 * The engine is the gateway into the Game Engine.
 * Initilaze and add Systems to get functionality.
 * TODO: Finish writing desc
 */

class Engine
{
    
    // Use pointers for polymorphism
    
    Bus bus;
    std::vector<System*> systems;
    std::vector<Entity> scene; 
    bool isRunning;


    /**
     * @returns true if no error, false if it failed
     */
    bool AddSystem(System* newSystem)
    {
        try
        {
            systems.push_back(newSystem);
        }
        catch(const std::exception& e)
        {
            return false;
        }
        return true;
        
        
    
    }

    // TODO: Add Init all systems
    void Start()
    {
        isRunning = true;
        for (auto& entity : scene)
        {
            entity.Init();
        }
        Loop();
    }


    // Returns false if error occurs. TODO: Add errorData struct to have in-engine error managment
    bool Loop();

    public:
        const std::vector<Entity>& GetEntities()
        {
            return scene;
        }

        const Bus& GetBus() { return bus; }

        Entity& CreateEntity()
        {
            scene.emplace_back();
            return scene.back();
        }
        
        // TODO: ADD WRAPPER FUNCTIONS THAT START SYSTEMS

};

#endif