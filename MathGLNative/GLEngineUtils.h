#pragma once
#include "OdGeVector3d.h"
#include <cmath>
#include <OdGeQuaternion.h>

using namespace Geometry;

enum class AnimationMode
{
    LINEAR = 0,
    EASE_IN,
    EASE_IN2,       // using circle
    EASE_OUT,
    EASE_OUT2,      // using circle
    EASE_IN_OUT,
    EASE_IN_OUT2,   // using circle
    BOUNCE,
    ELASTIC
};

class GLEngineUtils
{
public:
    static int getFrame(int frameStart, int frameEnd, float elapsedTime, float frameRate = 30, bool loop = true);

    static OdGeVector3d slerp(const OdGeVector3d& from, const OdGeVector3d& to, float alpha, AnimationMode mode = AnimationMode::LINEAR);

    // spherical linear interpolation between 2 quaternions
    // the alpha value should be 0 ~ 1
    static Quaternion slerp(const Quaternion& from, const Quaternion& to, float alpha, AnimationMode mode = AnimationMode::LINEAR);


    static float accelerate(bool isMoving, float currSpeed, float maxSpeed, float accel, float deltaTime);

    template <class T>
    static bool move(T& vec, const T& from, const T& to, float elapsedTime, float speed)
    {
        if (from == to)
        {
            vec = to;
            return true;
        }

        bool done = false;

        vec = to - from;
        float length1 = vec.length();

        vec.normalize();
        float distance = elapsedTime * speed;
        vec *= distance;
        float length2 = vec.length();

        vec = from + vec;
        if (length2 > length1)
        {
            vec = to;
            done = true;
        }

        return done;
    }

    template <class T>
    static T lerp(const T& from, const T& to, float alpha)
    {
        return from + alpha * (to - from);
    }

    template <class T>
    static T interpolate(const T& from, const T& to, float alpha, AnimationMode mode)
    {
        if (mode == AnimationMode::EASE_IN)
        {
            alpha = alpha * alpha * alpha;
        }
        else if (mode == AnimationMode::EASE_IN2)
        {
            alpha = 1 - sqrtf(1 - alpha * alpha);
        }
        else if (mode == AnimationMode::EASE_OUT)
        {
            float beta = 1 - alpha;
            alpha = 1 - beta * beta * beta;
        }
        else if (mode == AnimationMode::EASE_OUT2)
        {
            alpha = sqrtf(1 - (1 - alpha) * (1 - alpha));
        }
        else if (mode == AnimationMode::EASE_IN_OUT)
        {
            float beta = 1 - alpha;
            float scale = 4.0f;
            if (alpha < 0.5f)
                alpha = alpha * alpha * alpha * scale;
            else
                alpha = 1 - (beta * beta * beta * scale);
        }
        else if (mode == AnimationMode::EASE_IN_OUT2)
        {
            if (alpha < 0.5f)
                alpha = 0.5f * (1 - sqrtf(1 - alpha * alpha));
            else
                alpha = 0.5f * sqrtf(1 - (1 - alpha) * (1 - alpha)) + 0.5f;
        }
        else if (mode == AnimationMode::BOUNCE)
        {
        }
        else if (mode == AnimationMode::ELASTIC)
        {
        }

        return from + (to - from) * alpha;
    }
};

