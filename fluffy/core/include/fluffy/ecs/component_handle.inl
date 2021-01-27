#include <fluffy/ecs/component_handle.hpp>
#include <fluffy/ecs/entity_manager.hpp>

using namespace Fluffy;

template<typename C>
ComponentHandle<C>::ComponentHandle()
  : mManager(nullptr)
  , mId(Entity::INVALID)
{
}

template<typename C>
ComponentHandle<C>::ComponentHandle(EntityManager* manager, Entity::Id id)
  : mManager(manager)
  , mId(id)
{
}

template<typename C>
bool ComponentHandle<C>::operator==(const ComponentHandle<C>& other) const
{
    return mManager == other.mManager && mId == other.mId;
}

template<typename C>
bool ComponentHandle<C>::operator!=(const ComponentHandle<C>& other) const
{
    return !(*this == other);
}

template<typename C>
C* ComponentHandle<C>::get()
{
    FLUFFY_ASSERT(isValid(), "Component is not valid");

    return mManager->template getComponentPointer<C>(mId);
}

template<typename C>
void ComponentHandle<C>::remove()
{
    FLUFFY_ASSERT(isValid(), "Component is not valid");

    mManager->template remove<C>(mId);
}

template<typename C>
Entity ComponentHandle<C>::getEntity()
{
    FLUFFY_ASSERT(isValid(), "Component is not valid");

    return mManager->getEntity(mId);
}

template<typename C>
ComponentHandle<C>::operator bool() const
{
    return isValid();
}

template<typename C>
bool ComponentHandle<C>::isValid() const
{
    return mManager && mManager->isValid(mId) && mManager->template hasComponent<C>(mId);
}

template<typename C>
C* ComponentHandle<C>::operator->()
{
    return get();
}

template<typename C>
const C* ComponentHandle<C>::get() const
{
    FLUFFY_ASSERT(isValid(), "Component is not valid");

    return mManager->template getComponentPointer<C>(mId);
}

template<typename C>
const C* ComponentHandle<C>::operator->() const
{
    return get();
}