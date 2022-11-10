//
// Created by god on 10.11.2022.
//

#ifndef _VECTOR_H
#define _VECTOR_H


#include <cmath>
#include <string>

struct Vector {
public:
    float x = 0, y = 0;
    Vector() : x(0), y(0) {}
    Vector(float x, float y) : x(x), y(y) {}

    Vector(const Vector& v) = default;
    Vector& operator=(const Vector& v) = default;

    float mag() const {
        return std::sqrt(x * x + y * y);
    }

    float dot(const Vector& v) const {
        return this->x * v.x + this->y * v.y;
    }

    float cross(const Vector& v) const {
        return this->x * v.y - this->y * v.x;
    }

    Vector operator+(const Vector& v) const {
        return Vector(this->x + v.x, this->y + v.y);
    }

    Vector operator-(const Vector& v) const {
        return Vector(this->x - v.x, this->y - v.y);
    }

    Vector operator*(const Vector& v) const {
        return Vector(this->x * v.x, this->y * v.y);
    }

    Vector operator/(const Vector& v) const {
        return Vector(this->x / v.x, this->y / v.y);
    }

    Vector operator*(const float a) const {
        return Vector(this->x * a, this->y * a);
    }

    Vector operator/(const float a) const {
        return Vector(this->x / a, this->y / a);
    }

    Vector operator+() const {
        return Vector(+this->x, +this->y);
    }

    Vector operator-() const {
        return Vector(-this->x, -this->y);
    }

    Vector& operator+=(const Vector& v) {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    Vector& operator-=(const Vector& v) {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    Vector& operator*=(const Vector& v) {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    Vector& operator/=(const Vector& v) {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }

    Vector& operator*=(const float a) {
        this->x *= a;
        this->y *= a;
        return *this;
    }

    Vector& operator/=(const float a) {
        this->x /= a;
        this->y /= a;
        return *this;
    }

    bool operator==(const Vector& v) const {
        return this->x == v.x && this->y == v.y;
    }

    bool operator!=(const Vector& v) const {
        return this->x != v.x || this->y != v.y;
    }

    const std::string str() const {
        return std::string("(") + std::to_string(this->x) +
                "," + std::to_string(this->y) + ")";
    }

    friend std::ostream& operator << (std::ostream& os, const Vector& v) {
        os << v.str();
        return os;
    }
};


#endif //_VECTOR_H
