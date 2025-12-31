#ifndef ARGUS_COMPONENT_HPP
#define ARGUS_COMPONENT_HPP

/**
 * ----- Components -----
 * The base component class is meant to be extended to add functionality.
 * The coding will be mostly done here and in Systems.
 */



class Entity;

class Component
{
    private:
        Entity* owner = nullptr;

        friend class Entity;

        virtual bool Ready() {return true;}; // Ready to begin engine
        virtual bool Init() {return true;}; // First initiialized
        virtual bool Update(float dt) {return true;};
        virtual void OnDeath() {};

        void setOwner(Entity* e) { owner = e;}
    public:
        virtual ~Component() = default;
    protected:
        virtual Entity& getOwner() final {
            return *owner;
        }
        
};

#endif