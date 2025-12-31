#include "ArgusEngine.hpp"


bool Engine::Loop()
{
    // Calculate dt
    // ...

    for (auto sys : systems)
    {
        sys->Update(/*Add dt */1/60 , *this);
    }

    bus.Dispatch();

    return true;

}