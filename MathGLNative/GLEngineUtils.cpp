#include "pch.h"
#include "GLEngineUtils.h"

int GLEngineUtils::getFrame(int frameStart, int frameEnd, float time, float fps, bool loop)
{
    int frame = frameStart + (int)(fps * time + 0.5f);
    if (loop)
    {
        frame = frame % (frameEnd - frameStart + 1);
    }
    else
    {
        if (frame > frameEnd)
            frame = frameEnd;
    }
    return frame;
}


OdGeVector3d GLEngineUtils::slerp(const OdGeVector3d& from, const OdGeVector3d& to, float alpha, AnimationMode mode)
{
    float t = interpolate(0.0f, 1.0f, alpha, mode);

    float cosine = from.DotProduct(to) / (from.Length() * to.Length());
    float angle = acosf(cosine);
    float invSine = 1.0f / sinf(angle);

    float scale1 = sinf((1 - t) * angle) * invSine;
    float scale2 = sinf(t * angle) * invSine;

    return from * scale1 + to * scale2;
}

Quaternion GLEngineUtils::slerp(const Quaternion& from, const Quaternion& to, float alpha, AnimationMode mode)
{
    // re-compute alpha
    float t = interpolate(0.0f, 1.0f, alpha, mode);

    float dot = from.s * to.s + from.x * to.x + from.y * to.y + from.z * to.z;

    if (1 - dot < 0.001f)
    {
        return Quaternion(from + (to - from) * t);
    }
    else if (fabs(1 + dot) < 0.001f) // dot ~= -1
    {
        OdGeVector3d up, v1, v2;
        v1 = OdGeVector3d(from.x, from.y, from.z);
        v1.Normalize();
        if (fabs(from.x) < 0.001f)
            up = OdGeVector3d(1, 0, 0);
        else
            up = OdGeVector3d(0, 1, 0);
        v2 = v1.CrossProduct(up);
        v2.Normalize();
        float angle = acosf(dot) * t;
        OdGeVector3d v3 = v1 * cosf(angle) + v2 * sinf(angle);
        return Quaternion(0, v3.x, v3.y, v3.z);
    }

    float angle = acosf(dot);
    float invSine = 1.0f / sqrtf(1 - dot * dot);

    // compute the scale factors
    float scale1 = sinf((1 - t) * angle) * invSine;
    float scale2 = sinf(t * angle) * invSine;

    return Quaternion(from * scale1 + to * scale2);
}

float GLEngineUtils::accelerate(bool isMoving, float speed, float maxSpeed, float accel, float deltaTime)
{
    float sign;
    if (maxSpeed > 0)
        sign = 1;
    else
        sign = -1;

    if (isMoving)
    {
        speed += sign * accel * deltaTime;
        if ((sign * speed) > (sign * maxSpeed))
            speed = maxSpeed;
    }
    else
    {
        speed -= sign * accel * deltaTime;
        if ((sign * speed) < 0)
            speed = 0;
    }

    return speed;
}
