#pragma once

#include "NormalOrchestrator.hpp"

namespace adas
{
    class BusOrchestrator : public NormalOrchestrator
    {
    public:
        ActionGroup TurnLeft(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;
            if(poseHandler.IsFast()){
                if(poseHandler.IsReverse()){
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
                }
                else{
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
                }
            }
            else{
                if(poseHandler.IsReverse()){
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
                }
                else{
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
                }
            }
            return actionGroup;
        }

        ActionGroup TurnRight(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            if (poseHandler.IsFast())
            {
                if (poseHandler.IsReverse())
                {
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
                }
                else
                {
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
                }
            }
            else
            {
                if (poseHandler.IsReverse())
                {
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
                }
                else
                {
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
                }
            }
            return actionGroup;
        }
    };
}
