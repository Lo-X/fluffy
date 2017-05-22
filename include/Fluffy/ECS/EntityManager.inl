//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 21/05/17.
//

#include <Fluffy/ECS/EntityManager.hpp>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

template <typename C>
std::size_t EntityManager::componentFamily()
{
    return Component<typename std::remove_const<C>::type>::getFamily();
}

template <typename C, typename... Args>
ComponentHandle<C> EntityManager::assign(Entity::Id id, Args&&... args)
{
    assertValid(id);
    const BaseComponent::Family family = componentFamily<C>();
    assert(!mEntityComponentMask[id.getIndex()].test(family));

    Pool<C>*          pool   = getComponentPool<C>();
    ::new (pool->get(id.getIndex())) C(std::forward<Args>(args)...);

    ComponentHandle<C> component(this, id);
    mEntityComponentMask[id.getIndex()].set(family);

    // @todo emit event

    return component;
};

template <typename C>
void EntityManager::remove(Entity::Id id)
{
    assertValid(id);
    const BaseComponent::Family family = componentFamily<C>();
    assert(mEntityComponentMask[id.getIndex()].test(family));

    BasePool* pool = mComponentPools[family];

    ComponentHandle<C> component(this, id);
    // @todo emit event component about to be deleted including the ComponentHandle

    mEntityComponentMask[id.getIndex()].reset(family);
    pool->destroy(id.getIndex());
};

template <typename C>
bool EntityManager::hasComponent(Entity::Id id) const
{
    assertValid(id);
    const BaseComponent::Family family = componentFamily<C>();

    if (family > mComponentPools.size()) {
        return false;
    }

    BasePool* pool = mComponentPools[family];

    return (pool && mEntityComponentMask[id.getIndex()][family]);
}

template <typename C>
ComponentHandle<C> EntityManager::component(Entity::Id id)
{
    assertValid(id);
    const BaseComponent::Family family = componentFamily<C>();

    if (family > mComponentPools.size()) {
        return ComponentHandle<C>();
    }

    BasePool* pool = mComponentPools[family];
    if (!pool || !mEntityComponentMask[id.getIndex()][family]) {
        return ComponentHandle<C>();
    }

    ComponentHandle<C> component(this, id);
    return component;
}

template <typename... Components>
std::tuple<ComponentHandle<Components>...> EntityManager::components(Entity::Id id)
{
    return std::make_tuple(component<Components>(id)...);
}



// Private

template <typename C>
C* EntityManager::getComponentPointer(std::uint32_t entity)
{
    BasePool* pool = mComponentPools[componentFamily<C>()];
    assert(pool);

    return static_cast<C*>(pool->get(entity));
}

template <typename C>
Pool<C>* EntityManager::getComponentPool()
{
    BaseComponent::Family family = componentFamily<C>();
    if (mComponentPools.size() <= family) {
        mComponentPools.resize(family + 1, nullptr);
    }
    if (!mComponentPools[family]) {
        Pool<C>* pool = new Pool<C>;
        pool->expand(mIndexCounter);
        mComponentPools[family] = pool;

        return pool;
    }

    return static_cast<Pool<C>*>(mComponentPools[family]);
}