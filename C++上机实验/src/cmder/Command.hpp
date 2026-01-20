#pragma once

#include".\core\PoseHandler.hpp"
#include "CmderOrchestrator.hpp"
#include<functional>

namespace adas{
    /*class ICommand
    {
        public:
        virtual ~ICommand() = default;
        virtual void DoOperate(PoseHandler&PoseHandler) const noexcept=0;
    };
    */
    
    class MoveCommand final   //:public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler& poseHandler,const CmderOrchestrator& orchestrator) const noexcept
        {
            return orchestrator.Move(poseHandler);
        }
    };
    class TurnLeftCommand final   //:public ICommand  
    {
    public:
    ActionGroup operator()(PoseHandler& poseHandler,const CmderOrchestrator& orchestrator) const noexcept {
        return orchestrator.TurnLeft(poseHandler);
    }
    };
    class TurnRightCommand final    //:public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.TurnRight(poseHandler);
        }
    };
    class FastCommand final    //:public ICommand
    {
    public:
    ActionGroup operator()(PoseHandler& poseHandler,const CmderOrchestrator &orchestrator) const noexcept {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_FAST_ACTION);
        return actionGroup;
    }
    };
    class ReverseCommand final
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);
            return actionGroup;
        }
    };
    class TurnRoundCommand final{
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.TurnRound(poseHandler);
        }
    };
};