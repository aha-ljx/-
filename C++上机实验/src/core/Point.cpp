#include ".\Point.hpp"

namespace adas{
// 构造函数实现
Point::Point(const int x, const int y) noexcept: x(x), y(y) {}

// 拷贝构造函数实现
Point::Point(const Point& rhs) noexcept: x(rhs.x), y(rhs.y) {}

// 拷贝赋值运算符实现
Point& Point::operator=(const Point& rhs) noexcept {
    if (this != &rhs) {  // 避免自赋值
        x = rhs.x;
        y = rhs.y;
    }
    return *this;
}

// +=运算符实现（向量加法，将 rhs 的坐标加到当前对象）
Point& Point::operator+=(const Point& rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

// -=运算符实现（向量减法，将 rhs 的坐标减当前对象）
Point& Point::operator-=(const Point& rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

// 获取x坐标
int Point::GetX(void) const noexcept {
    return x;
}

// 获取y坐标
int Point::GetY(void) const noexcept {
    return y;
}
}