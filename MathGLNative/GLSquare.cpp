#include "pch.h"
#include "GLSquare.h"

OdGePoint2d GLSquare::getMinPnt() const
{
    return m_minPnt;
}

void GLSquare::setMinPnt(OdGePoint2d minPnt)
{
    m_minPnt = minPnt;
}

OdGePoint2d GLSquare::getMaxPnt() const
{
    return m_maxPnt;
}

void GLSquare::setMaxPnt(OdGePoint2d maxPnt)
{
    m_maxPnt = maxPnt;
}

double GLSquare::getHeight() const
{
    return m_height;
}

void GLSquare::setHeight(double height)
{
    m_height = height;
}

void GLSquare::render()
{
    double minX = m_minPnt.x;
    double minY = m_minPnt.y;
    double maxX = m_maxPnt.x;
    double maxY = m_maxPnt.y;
    double zBottom = 0.0;
    double zTop = m_height;

    glBegin(GL_QUADS);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(minX, minY, zBottom);
    glVertex3f(maxX, minY, zBottom);
    glVertex3f(maxX, maxY, zBottom);
    glVertex3f(minX, maxY, zBottom);

    glVertex3f(minX, minY, zTop);
    glVertex3f(maxX, minY, zTop);
    glVertex3f(maxX, maxY, zTop);
    glVertex3f(minX, maxY, zTop);

    glVertex3f(minX, minY, zBottom);
    glVertex3f(maxX, minY, zBottom);
    glVertex3f(maxX, minY, zTop);
    glVertex3f(minX, minY, zTop);

    glVertex3f(maxX, minY, zBottom);
    glVertex3f(maxX, maxY, zBottom);
    glVertex3f(maxX, maxY, zTop);
    glVertex3f(maxX, minY, zTop);

    glVertex3f(maxX, maxY, zBottom);
    glVertex3f(minX, maxY, zBottom);
    glVertex3f(minX, maxY, zTop);
    glVertex3f(maxX, maxY, zTop);

    glVertex3f(minX, maxY, zBottom);
    glVertex3f(minX, minY, zBottom);
    glVertex3f(minX, minY, zTop);
    glVertex3f(minX, maxY, zTop);

    glEnd();

    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);

    glVertex3f(minX, minY, zBottom);
    glVertex3f(maxX, minY, zBottom);

    glVertex3f(maxX, minY, zBottom);
    glVertex3f(maxX, maxY, zBottom);

    glVertex3f(maxX, maxY, zBottom);
    glVertex3f(minX, maxY, zBottom);

    glVertex3f(minX, maxY, zBottom);
    glVertex3f(minX, minY, zBottom);

    glVertex3f(minX, minY, zTop);
    glVertex3f(maxX, minY, zTop);

    glVertex3f(maxX, minY, zTop);
    glVertex3f(maxX, maxY, zTop);

    glVertex3f(maxX, maxY, zTop);
    glVertex3f(minX, maxY, zTop);

    glVertex3f(minX, maxY, zTop);
    glVertex3f(minX, minY, zTop);

    glVertex3f(minX, minY, zBottom);
    glVertex3f(minX, minY, zTop);

    glVertex3f(maxX, minY, zBottom);
    glVertex3f(maxX, minY, zTop);

    glVertex3f(maxX, maxY, zBottom);
    glVertex3f(maxX, maxY, zTop);

    glVertex3f(minX, maxY, zBottom);
    glVertex3f(minX, maxY, zTop);

    glEnd();
}

