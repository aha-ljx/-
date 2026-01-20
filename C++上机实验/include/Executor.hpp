#pragma once
#include<string>
namespace adas
{
    /*车辆类型枚举*/
    enum class ExecutorType{
        NORMAL,
        SPORTS_CAR,
        BUS,
    };
    /*汽车姿态*/
    struct Pose
    {
        int x;
        int y;
        char heading;
    };
    /*驾驶动作执行器接口*/
    class Executor
    {
    public:
        static Executor *NewExecutor(const Pose &pose = {0,0,'N'},
        const ExecutorType executorType = ExecutorType::NORMAL) noexcept;

    public:
        Executor(void) = default;
        virtual ~Executor(void) = default;
        Executor(const Executor &) = delete;
        Executor &operator =(const Executor &) = delete;

    public:
        virtual Pose Query(void) const noexcept = 0;
        virtual void Execute(const std::string &commands) noexcept = 0;
    };
}