//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 14/11/17.
//

#ifndef FLUFFY_TIME_HPP
#define FLUFFY_TIME_HPP

#include <chrono>

namespace Fluffy {
namespace Utility {

/**
 * Represent an elapsed time, a duration
 */
class Time
{
public:
    static const Time Zero;

public:
    Time() = default;

    float        seconds() const;
    std::int32_t milliseconds() const;
    std::int64_t microseconds() const;

private:
    Time(std::int64_t microseconds);
    Time(std::chrono::microseconds microseconds);

    friend Time seconds(float);
    friend Time seconds(std::chrono::seconds);
    friend Time milliseconds(std::int32_t);
    friend Time milliseconds(std::chrono::milliseconds);
    friend Time microseconds(std::int64_t);
    friend Time microseconds(std::chrono::microseconds);

private:
    std::int64_t mMicroseconds = 0;
};

Time seconds(float sec);
Time seconds(std::chrono::seconds);
Time milliseconds(std::int32_t ms);
Time milliseconds(std::chrono::milliseconds);
Time microseconds(std::int64_t);
Time microseconds(std::chrono::microseconds);

bool operator==(Time left, Time right);
bool operator!=(Time left, Time right);
bool operator<(Time left, Time right);
bool operator>(Time left, Time right);
bool operator<=(Time left, Time right);
bool operator>=(Time left, Time right);
Time operator-(Time right);
Time operator+(Time left, Time right);
Time& operator+=(Time& left, Time right);
Time operator-(Time left, Time right);
Time& operator-=(Time& left, Time right);
Time operator*(Time left, float right);
Time operator*(Time left, std::uint64_t right);
Time operator*(float left, Time right);
Time operator*(std::uint64_t left, Time right);
Time& operator*=(Time& left, float right);
Time& operator*=(Time& left, std::uint64_t right);
Time operator/(Time left, float right);
Time operator/(Time left, std::uint64_t right);
Time& operator/=(Time& left, float right);
Time& operator/=(Time& left, std::uint64_t right);
float operator/(Time left, Time right);
}
}

#endif //FLUFFY_TIME_HPP
