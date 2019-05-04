//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#include <fluffy/game/game.hpp>

using namespace Fluffy;

bool Game::isRunning() const
{
    return mStateStack && !mStateStack->isEmpty();
}

void Game::setStartingState(BaseState::Ptr state, const Context& context)
{
    if (!mStateStack) {
        mStateStack = std::make_unique<StateStack>(context);
    }

    mStateStack->push(std::move(state));
    mStateStack->forcePendingChanges();
}

void Game::internalUpdate(Time dt)
{
    mStateStack->update(dt);
}