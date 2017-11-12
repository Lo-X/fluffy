//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#ifndef FLUFFY_SIGNAL_HPP
#define FLUFFY_SIGNAL_HPP

#include <Fluffy/Event/Slot.hpp>
#include <functional>
#include <map>
#include <vector>

namespace Fluffy {
namespace Event {

template <typename... Args>
class Signal
{
public:
    Signal() = default;

    Slot connect(std::function<void(Args...)> callback);
    void disconnect(Slot slot);
    void disconnect(Slot::Id id);
    void emit(Args... args);

private:
    mutable std::map<Slot::Id, std::function<void(Args...)>> mCallbacks;
    mutable std::uint64_t mNextId = 0;
};
}
}

#include <Fluffy/Event/Signal.inl>

#endif //FLUFFY_SIGNAL_HPP
