#ifndef ARGUS_SYSTEM_HPP
#define ARGUS_SYSTEM_HPP

/**
 * TODO: Add desc
*/



#include "ArgusTypes.hpp"

class Engine;

class System
{
    private:
        friend class Engine;
        virtual bool Update(float dt, Engine& engine) = 0;
        virtual bool Init() = 0;
    public:   
        virtual ~System() = default;    
};

#endif