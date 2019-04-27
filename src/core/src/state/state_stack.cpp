//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#include <fluffy/state/state_stack.hpp>

using namespace Fluffy;

StateStack::PendingChange::PendingChange(Action action, BaseState::Family family)
  : action(action)
  , family(family)
{
}

StateStack::StateStack(ServiceContainer& serviceContainer)
  : mServiceContainer(serviceContainer)
{
    // Subscribe to events that will apply the pending changes
    if (mServiceContainer.has<EventManager>()) {
        auto eventManager   = mServiceContainer.get<EventManager>();
        mBeforeGameTickSlot = eventManager->connect<BeforeGameTickEvent>(std::bind(&StateStack::onBeforeGameTickEvent, this, std::placeholders::_1));
        mAfterGameTickSlot  = eventManager->connect<AfterGameTickEvent>(std::bind(&StateStack::onAfterGameTickEvent, this, std::placeholders::_1));
    }
}

StateStack::~StateStack()
{
    // Unsubscribe from events
    mBeforeGameTickSlot.disconnect();
    mAfterGameTickSlot.disconnect();

    // Terminate all states and clear the stack
    for (BaseState::Ptr& state : mStack) {
        state->terminate();
    }
    mStack.clear();
}

void StateStack::pop()
{
    mPendingList.emplace_back(Action::Pop);
}

void StateStack::clear()
{
    mPendingList.emplace_back(Action::Clear);
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

BaseState::Ptr StateStack::createState(BaseState::Family family)
{
    auto found = mFactories.find(family);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::onBeforeGameTickEvent(const BeforeGameTickEvent&)
{
    applyPendingChanges();
}

void StateStack::onAfterGameTickEvent(const AfterGameTickEvent&)
{
    applyPendingChanges();
}

void StateStack::forcePendingChanges()
{
    applyPendingChanges();
}

void StateStack::applyPendingChanges()
{
    for (PendingChange change : mPendingList) {
        switch (change.action) {
            case Action::Push:
                if (!mStack.empty()) {
                    mStack.back()->pause();
                }
                mStack.push_back(createState(change.family));
                break;

            case Action::Pop:
                mStack.back()->terminate();
                mStack.pop_back();
                if (!mStack.empty()) {
                    mStack.back()->resume();
                }
                break;

            case Action::Clear:
                for (BaseState::Ptr& state : mStack) {
                    state->terminate();
                }
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}