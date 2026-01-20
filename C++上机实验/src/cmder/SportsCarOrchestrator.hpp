#pragma once

#include "NormalOrchestrator.hpp"

namespace adas {
    class SportsCarOrchestrator : public NormalOrchestrator{
    public:
        ActionGroup Move(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;
            if(poseHandler.IsFast()){
                if(poseHandler.IsReverse()){
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                }
                else{
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                }
            }
            else{
                if(poseHandler.IsReverse()){
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                }
                else{
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                }
            }
            return actionGroup;
        }
    
        ActionGroup TurnLeft(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;
            if(poseHandler.IsFast()){
                if(poseHandler.IsReverse()){
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                }
                else{
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                }
            }
            else{
                if(poseHandler.IsReverse()){
                    actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                }
                else{
                    actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                }
            }
            return actionGroup;
        }
    
        ActionGroup TurnRight(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;
            if (poseHandler.IsFast())
            {
                if (poseHandler.IsReverse())
                {
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                }
                else
                {
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                    actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                }
            }
            else
            {
                if (poseHandler.IsReverse())
                {
                    actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                }
                else
                {
                    actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                }
            }
            return actionGroup;
        }
    };
}