#include "pch.h"
#include "OdGePoint3d.h"
#include "OdGeVector3d.h"
#include "OdGePoint2d.h"

namespace Geometry
{
    class OdGePoint3dTest : public ::testing::Test
    {
    protected:
        OdGePoint3d point1;
        OdGePoint3d point2;

        virtual void SetUp() override
        {
            point1 = OdGePoint3d(1.0f, 2.0f, 3.0f);
            point2 = OdGePoint3d(4.0f, 5.0f, 6.0f);
        }
    };

    TEST_F(OdGePoint3dTest, DefaultConstructor)
    {
        OdGePoint3d point;
        EXPECT_FLOAT_EQ(point.x, 0.0f);
        EXPECT_FLOAT_EQ(point.y, 0.0f);
        EXPECT_FLOAT_EQ(point.z, 0.0f);
    }

    TEST_F(OdGePoint3dTest, ParameterizedConstructor)
    {
        OdGePoint3d point(1.0f, 2.0f, 3.0f);
        EXPECT_FLOAT_EQ(point.x, 1.0f);
        EXPECT_FLOAT_EQ(point.y, 2.0f);
        EXPECT_FLOAT_EQ(point.z, 3.0f);
    }

    TEST_F(OdGePoint3dTest, DistanceTo)
    {
        float distance = point1.DistanceTo(point2);
        EXPECT_FLOAT_EQ(distance, sqrt(27.0f));
    }

    TEST_F(OdGePoint3dTest, ConvertTo2d)
    {
        OdGePoint2d point2d = point1.ConvertTo2d();
        EXPECT_FLOAT_EQ(point2d.x, point1.x);
        EXPECT_FLOAT_EQ(point2d.y, point1.y);
    }

    TEST_F(OdGePoint3dTest, OperatorPlusEqualsPoint3d)
    {
        point1 += point2;
        EXPECT_FLOAT_EQ(point1.x, 5.0f);
        EXPECT_FLOAT_EQ(point1.y, 7.0f);
        EXPECT_FLOAT_EQ(point1.z, 9.0f);
    }

    TEST_F(OdGePoint3dTest, OperatorPlusEqualsVector3d)
    {
        OdGeVector3d vec(1.0f, 1.0f, 1.0f);
        point1 += vec;
        EXPECT_FLOAT_EQ(point1.x, 2.0f);
        EXPECT_FLOAT_EQ(point1.y, 3.0f);
        EXPECT_FLOAT_EQ(point1.z, 4.0f);
    }

    TEST_F(OdGePoint3dTest, OperatorEqualEqual)
    {
        OdGePoint3d point3(1.0f, 2.0f, 3.0f);
        EXPECT_TRUE(point1 == point3);
        EXPECT_FALSE(point1 == point2);
    }

    TEST_F(OdGePoint3dTest, OperatorMultiplyScalar)
    {
        OdGePoint3d point = point1 * 2.0f;
        EXPECT_FLOAT_EQ(point.x, 2.0f);
        EXPECT_FLOAT_EQ(point.y, 4.0f);
        EXPECT_FLOAT_EQ(point.z, 6.0f);
    }

    TEST_F(OdGePoint3dTest, OperatorPlusPoint3d)
    {
        OdGePoint3d point = point1 + point2;
        EXPECT_FLOAT_EQ(point.x, 5.0f);
        EXPECT_FLOAT_EQ(point.y, 7.0f);
        EXPECT_FLOAT_EQ(point.z, 9.0f);
    }

    TEST_F(OdGePoint3dTest, OperatorMinusPoint3d)
    {
        OdGeVector3d vec = point2 - point1;
        EXPECT_FLOAT_EQ(vec.x, 3.0f);
        EXPECT_FLOAT_EQ(vec.y, 3.0f);
        EXPECT_FLOAT_EQ(vec.z, 3.0f);
    }

    TEST_F(OdGePoint3dTest, IsEqual)
    {
        OdGePoint3d point11(1.000001f, 2.000001f, 3.000001f);
		OdGePoint3d point12(1.0f, 2.0f, 3.0f);
        EXPECT_TRUE(point11.IsEqual(point12));
        EXPECT_FALSE(point11.IsEqual(point2));
    }
}

