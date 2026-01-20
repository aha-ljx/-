#include ".\PoseHandler.hpp"

namespace adas{
    PoseHandler::PoseHandler(const Pose& pose) noexcept 
    :point(pose.x,pose.y),facing(&Direction::GetDirection(pose.heading)){}

    void PoseHandler::Forward() noexcept{
        point += facing->Move();
    }
    
    void PoseHandler::Backward() noexcept{
        point -=facing->Move();
    }

    void PoseHandler::TurnLeft() noexcept{
        facing = &(facing->LeftOne());
    }

    void PoseHandler::TurnRight() noexcept{
        facing = &(facing->RightOne());
    }

    void PoseHandler::Fast() noexcept{
        if(fast == true){
            fast = false;
        }
        else{
            fast = true;
        }
    }
    
    void PoseHandler::Reverse() noexcept{
        if(reverse == true){
            reverse = false;
        }
        else{
            reverse = true;
        }
    }

    bool PoseHandler::IsFast() const noexcept{
        return fast;
    }

    bool PoseHandler::IsReverse() const noexcept{
        return reverse;
    }

    Pose PoseHandler::Query(void) const noexcept{
        return {point.GetX(),point.GetY(),facing->GetHeading()};
    }
}