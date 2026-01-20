#include"PoseEq.hpp"

bool adas::operator==(const Pose &lhs,const Pose &rhs)
{
    return std::tie(lhs.x,lhs.y,lhs.heading) == std::tie(rhs.x,rhs.y,rhs.heading);
}