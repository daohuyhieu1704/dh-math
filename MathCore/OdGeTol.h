#pragma once
class OdGeTol
{
public:
    OdGeTol(double t = 1.e-10)
        : m_vectorTol(t), m_pointTol(t)
    {
    }

    OdGeTol(double t1, double t2)
        : m_vectorTol(t2), m_pointTol(t1)
    {
    }

    double equalPoint() const
    {
        return m_pointTol;
    }

    double equalVector() const
    {
        return m_vectorTol;
    }

    void setEqualPoint(double val)
    {
        m_pointTol = val;
    }

    void setEqualVector(double val)
    {
        m_vectorTol = val;
    }

private:
    double m_vectorTol;
    double m_pointTol;
};

