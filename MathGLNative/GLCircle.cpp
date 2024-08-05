#include "pch.h"
#include "GLCircle.h"
#include <cmath>

OdGePoint3d GLCircle::getCenter() const
{
    return m_center;
}

void GLCircle::setCenter(OdGePoint3d center)
{
    m_center = center;
}

double GLCircle::getRadius() const
{
    return m_radius;
}

void GLCircle::setRadius(double radius)
{
    m_radius = radius;
}

void GLCircle::render()
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(m_center.x, m_center.y);
    for (int i = 0; i <= num_segments; i++) {
        float angle = 2.0f * MATH_PI * i / num_segments;
        float dx = cosf(angle) * m_radius;
        float dy = sinf(angle) * m_radius;
        glVertex2f(m_center.x + dx, m_center.y + dy);
    }
    glEnd();
}
