#include "ArgusEntity.hpp"
#include "ArgusComponent.hpp"

void Entity::addComponent(Component* comp) {
    if (comp) {
        comp->setOwner(this);   // Entity reaches into Component's private methods
        components.push_back(comp);
    }
}