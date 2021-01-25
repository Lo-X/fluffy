#include <fluffy/time/time.hpp>

using namespace Fluffy;

const Time Time::Zero = 0;

Time::Time(std::int64_t microseconds)
  : mMicroseconds(microseconds)
{
}

Time::Time(std::chrono::microseconds microseconds)
  : mMicroseconds(microseconds.count())
{
}

float Time::seconds() const
{
    return mMicroseconds / 1000000.f;
}

float Time::milliseconds() const
{
    return mMicroseconds / 1000.f;
}

std::int64_t Time::microseconds() const
{
    return mMicroseconds;
}

/**********************************************************************************************************************/

Time Fluffy::seconds(float sec)
{
    return { static_cast<std::int64_t>(sec * 1000000) };
}

Time Fluffy::seconds(std::chrono::seconds sec)
{
    return { std::chrono::microseconds(sec) };
}

Time Fluffy::milliseconds(float ms)
{
    return { static_cast<std::int64_t>(ms * 1000) };
}

Time Fluffy::milliseconds(std::chrono::milliseconds ms)
{
    return { std::chrono::microseconds(ms) };
}

Time Fluffy::microseconds(std::int64_t us)
{
    return { us };
}

Time Fluffy::microseconds(std::chrono::microseconds us)
{
    return { std::chrono::microseconds(us) };
}

/**********************************************************************************************************************/

bool Fluffy::operator==(Time left, Time right)
{
    return left.microseconds() == right.microseconds();
}

bool Fluffy::operator!=(Time left, Time right)
{
    return left.microseconds() != right.microseconds();
}

bool Fluffy::operator<(Time left, Time right)
{
    return left.microseconds() < right.microseconds();
}

bool Fluffy::operator>(Time left, Time right)
{
    return left.microseconds() > right.microseconds();
}

bool Fluffy::operator<=(Time left, Time right)
{
    return left.microseconds() <= right.microseconds();
}

bool Fluffy::operator>=(Time left, Time right)
{
    return left.microseconds() >= right.microseconds();
}

Time Fluffy::operator-(Time right)
{
    return microseconds(-right.microseconds());
}

Time Fluffy::operator+(Time left, Time right)
{
    return microseconds(left.microseconds() + right.microseconds());
}

Time& Fluffy::operator+=(Time& left, Time right)
{
    return left = left + right;
}

Time Fluffy::operator-(Time left, Time right)
{
    return microseconds(left.microseconds() - right.microseconds());
}

Time& Fluffy::operator-=(Time& left, Time right)
{
    return left = left - right;
}

Time Fluffy::operator*(Time left, float right)
{
    return seconds(left.seconds() * right);
}

Time Fluffy::operator*(Time left, std::uint64_t right)
{
    return microseconds(left.microseconds() * right);
}

Time Fluffy::operator*(float left, Time right)
{
    return right * left;
}

Time Fluffy::operator*(std::uint64_t left, Time right)
{
    return right * left;
}

Time& Fluffy::operator*=(Time& left, float right)
{
    return left = left * right;
}

Time& Fluffy::operator*=(Time& left, std::uint64_t right)
{
    return left = left * right;
}

Time Fluffy::operator/(Time left, float right)
{
    return seconds(left.seconds() / right);
}

Time Fluffy::operator/(Time left, std::uint64_t right)
{
    return microseconds(left.microseconds() / right);
}

Time& Fluffy::operator/=(Time& left, float right)
{
    return left = left / right;
}

Time& Fluffy::operator/=(Time& left, std::uint64_t right)
{
    return left = left / right;
}

float Fluffy::operator/(Time left, Time right)
{
    return left.seconds() / right.seconds();
}