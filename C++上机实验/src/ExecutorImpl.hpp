#pragma once
#include<memory>
#include"Executor.hpp"
#include"core/PoseHandler.hpp"
#include<string>
#include"cmder/CmderOrchestrator.hpp"

namespace adas{
    class ExecutorImpl final: public Executor{
    public:
        //构造函数
        explicit ExecutorImpl(const Pose& pose,CmderOrchestrator* orchestrator) noexcept;
        //默认析构函数
        ~ExecutorImpl() noexcept = default;
        //不能拷贝
        ExecutorImpl(const ExecutorImpl &) = default;
        //不能赋值
        ExecutorImpl &operator=(const ExecutorImpl &) = delete;

    public:
        Pose Query(void) const noexcept override;
        void Execute(const std::string &commands) noexcept override;
    private:
        PoseHandler poseHandler;
        std::unique_ptr<CmderOrchestrator> orchestrator;
};
}