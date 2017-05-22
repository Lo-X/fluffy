//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_ENTITYMANAGER_HPP
#define FLUFFY_ENTITYMANAGER_HPP

#include <Fluffy/ECS/Component.hpp>
#include <Fluffy/ECS/Entity.hpp>
#include <Fluffy/ECS/View/EntityComponentView.hpp>
#include <Fluffy/Lua/Bindable.hpp>
#include <Fluffy/Utility/NonCopyable.hpp>
#include <Fluffy/Utility/Pool.hpp>
#include <stack>
#include <typeindex>
#include <vector>

namespace Fluffy {
namespace ECS {

class EntityManager : public Utility::NonCopyable
{
public:
    typedef std::bitset<ECS::MAX_COMPONENTS> ComponentMask;

public:
    EntityManager();
    virtual ~EntityManager();

    /**
     * How many entities are handled
     */
    std::size_t size() const;
    std::size_t capacity() const;

    bool isValid(Entity::Id id) const;

    Entity createEntity();
    void destroyEntity(Entity::Id id);
    Entity getEntity(Entity::Id id);
    Entity::Id createEntityId(std::uint32_t index) const;

    template <typename C>
    static std::size_t componentFamily();

    template <typename C, typename... Args>
    ComponentHandle<C> assign(Entity::Id id, Args&&... args);

    template <typename C>
    void remove(Entity::Id id);

    template <typename C>
    bool hasComponent(Entity::Id id) const;

    template <typename C>
    ComponentHandle<C> component(Entity::Id id);

    template <typename... Components>
    std::tuple<ComponentHandle<Components>...> components(Entity::Id id);

    template <typename... Components>
    EntityComponentView<Components...> each();

private:
    void prepareForEntity(std::uint32_t index);
    void assertValid(Entity::Id id) const;

    template <typename C>
    C* getComponentPointer(std::uint32_t entity);

    template <typename C>
    Pool<C>* getComponentPool();

private:
    friend class Entity;
    template <typename C>
    friend class ComponentHandle;

    std::uint32_t                     mIndexCounter = 0;
    std::stack<std::uint32_t>         mFreeIndexes;
    std::vector<std::uint32_t>        mEntityVersion;
    std::vector<BasePool*>            mComponentPools; // indexed by Component::family()
    std::vector<ComponentMask>        mEntityComponentMask;
    std::vector<BaseComponentHelper*> mComponentHelpers;

    //    Entity::WeakPtr createEntity();
    //    void removeEntity(Entity::WeakPtr entity);
    //    Entity::WeakPtr entityByIndex(std::size_t index) const;
    //    Entity::WeakPtr entity(Entity::Ref ref) const;
    //    template <typename... Types>
    //    EntityComponentView<Types...> each();
    //
    //    void        removeAllEntities();
    //    void        clear();
    //    std::size_t size() const;
    //
    //    virtual void bind(sel::State& state);
    //
    //private:
    //    Entity::Ref             mNextRef;
    //    std::stack<Entity::Ref> mFreeRefs;
    //
    //    std::vector<Entity::Ptr> mEntities;
    //    std::map<Entity::Ref, Entity::Ptr> mEntitiesByRef;
};

#include <Fluffy/ECS/EntityManager.inl>
#include <Fluffy/ECS/View/EntityComponentView.inl>
}
}

#endif //FLUFFY_ENTITYMANAGER_HPP
