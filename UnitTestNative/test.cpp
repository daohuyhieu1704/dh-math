#include "pch.h"
#include "APIPointNative.h"
#include "APITopColumn.h"
#include <iostream>


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

class CFxTestMatrix3d
{
public:
	/**
	Returns non-localized version of the command name.
	*/
	virtual const OdString globalName() const;
	/**
	Returns localized version of the command name.
	*/
	virtual const OdString localName() const;
	/**
	Entry point for command execution.
	@return result code (\c RTNORM if command ended successfully)
	*/
	virtual int Execute(CFxCommandContext* pCmdCtx);
	/**
	Destruction of command.
	*/
	~CFxTestMatrix3d(void);
protected:
	/**
	Protected constructor to disallow instantiation.
	*/
	CFxTestMatrix3d(void);
	//// Unit test functions for OdGeMatrix3d ////
	bool testTranslation(CFxString& ExceptionMessage);
	bool testRotation(CFxString& ExceptionMessage);
	bool testScaling(CFxString& ExceptionMessage);
	bool testCompositeTransformation(CFxString& ExceptionMessage);
};
CFxTestMatrix3d::CFxTestMatrix3d(void) {}
CFxTestMatrix3d::~CFxTestMatrix3d(void) {}
const OdString CFxTestMatrix3d::globalName() const {
	return OD_T("TestMatrix3d");
}
const OdString CFxTestMatrix3d::localName() const {
	return OD_T("TestMatrix3d");
}
int CFxTestMatrix3d::Execute(CFxCommandContext* pCmdCtx) {
	OdArray<TestResult> results;
	CFxString exceptionMessage;
	// Execute individual tests
	if (!testTranslation(exceptionMessage)) {
		results.append(TestResult(false, OD_T("Translation Test Failed: ") +
			exceptionMessage));
	}
	if (!testRotation(exceptionMessage)) {
		results.append(TestResult(false, OD_T("Rotation Test Failed: ") +
			exceptionMessage));
	}
	if (!testScaling(exceptionMessage)) {
		results.append(TestResult(false, OD_T("Scaling Test Failed: ") +
			exceptionMessage));
	}
	if (!testCompositeTransformation(exceptionMessage)) {
		results.append(TestResult(false, OD_T("Composite Transformation Test Failed: ")
			+ exceptionMessage));
	}
	// Report results (this can be customized to fit your framework)
	for (auto& result : results) {
		pCmdCtx->userIO()->putString(result.message());
	}
	return results.isEmpty() ? RTNORM : RTERROR;
}
bool CFxTestMatrix3d::testTranslation(CFxString& ExceptionMessage) {
	OdGeMatrix3d translationMatrix = OdGeMatrix3d::translation(OdGeVector3d(10, 20,
		30));
	OdGePoint3d point(1, 1, 1);
	point.transformBy(translationMatrix);
	// Expected result is point(11, 21, 31)
	if (point.isEqualTo(OdGePoint3d(11, 21, 31))) {
		return true;
	}
	else {
		ExceptionMessage = OD_T("Expected point (11, 21, 31), got ") +
			OdString().format(OD_T("(%f, %f, %f)"), point.x, point.y, point.z);
		return false;
	}
}
bool CFxTestMatrix3d::testRotation(CFxString& ExceptionMessage) {
	OdGeMatrix3d rotationMatrix = OdGeMatrix3d::rotation(OdaPI / 2,
		OdGeVector3d::kZAxis, OdGePoint3d(0, 0, 0));
	OdGePoint3d point(1, 0, 0);
	point.transformBy(rotationMatrix);
	// Expected result is point(0, 1, 0) (90 degree rotation around Z-axis)
	if (point.isEqualTo(OdGePoint3d(0, 1, 0), 1e-6)) { // With a small tolerance
		return true;
	}
	else {
		ExceptionMessage = OD_T("Expected point (0, 1, 0), got ") +
			OdString().format(OD_T("(%f, %f, %f)"), point.x, point.y, point.z);
		return false;
	}
}
bool CFxTestMatrix3d::testScaling(CFxString& ExceptionMessage) {
	OdGeMatrix3d scalingMatrix = OdGeMatrix3d::scaling(2.0, OdGePoint3d(0, 0, 0));
	OdGePoint3d point(1, 1, 1);
	point.transformBy(scalingMatrix);
	// Expected result is point(2, 2, 2)
	if (point.isEqualTo(OdGePoint3d(2, 2, 2))) {
		return true;
	}
	else {
		ExceptionMessage = OD_T("Expected point (2, 2, 2), got ") +
			OdString().format(OD_T("(%f, %f, %f)"), point.x, point.y, point.z);
		return false;
	}
}
bool CFxTestMatrix3d::testCompositeTransformation(CFxString& ExceptionMessage) {
	OdGeMatrix3d translationMatrix = OdGeMatrix3d::translation(OdGeVector3d(10, 20,
		30));
	OdGeMatrix3d scalingMatrix = OdGeMatrix3d::scaling(2.0, OdGePoint3d(0, 0, 0));
	OdGeMatrix3d compositeMatrix = translationMatrix * scalingMatrix;
	OdGePoint3d point(1, 1, 1);
	point.transformBy(compositeMatrix);
	if (point.isEqualTo(OdGePoint3d(12, 22, 32))) {
		return true;
	}
	else {
		ExceptionMessage = OD_T("Expected point (12, 22, 32), got ") +
			OdString().format(OD_T("(%f, %f, %f)"), point.x, point.y, point.z);
		return false;
	}
}
B?o c?o TTTN ??i h?c CH??NG 3. TH?C NGHI?M
??o Huy Hi?u ? D20CQCNPM02 - N
void OvalCmd::serialize(const std::vector<std::string>&strData) {
	if (strData.size() >= 5) {
		std::istringstream(strData[0]) >> center.x;
		std::istringstream(strData[1]) >> center.y;
		std::istringstream(strData[2]) >> radiusX;
		std::istringstream(strData[3]) >> radiusY;
		std::istringstream(strData[4]) >> height;
	}
}
bool OvalCmd::execute() {
	MathOval oval;
	oval.setCenter(center);
	oval.setRadiusX(radiusX);
	oval.setRadiusY(radiusY);
	oval.setHeight(height);
	GLEngineNative::GetInstance()->m_entities.push_back(oval->m_renderMethod);
	return true;
}

bool comparePoint(OdGePoint3d p1, OdGePoint3d p2)
{
	return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}

bool compareVector(OdGeVector3d p1, OdGeVector3d p2)
{
	return p1 == p2;
}


std::string GetStrListPoint(std::vector<OdGePoint2d> listpoint)
{
	std::string ret = "";
	for (int i = 0; i < listpoint.size(); i++)
	{
		ret += std::to_string(listpoint[i].x);
		ret += ", ";
		ret += std::to_string(listpoint[i].y);
		ret += "\n";
	}
	return ret;
}
TEST(TestPlus, TestPlus1) {
	OdGePoint3d p1 = OdGePoint3d(1, 2, 3);
	OdGePoint3d p2 = OdGePoint3d(4, 2, 3);
	OdGePoint3d expect = OdGePoint3d(5, 4, 6);
	OdGePoint3d result = APIPointNative::plus(p1, p2);
	EXPECT_TRUE(comparePoint(expect,result));
}

TEST(TestSubtrac, TestSubtrac1) {
	OdGePoint3d p1 = OdGePoint3d(1, 2, 3);
	OdGePoint3d p2 = OdGePoint3d(4, 2, 3);

	OdGeVector3d expect = OdGeVector3d(-3, 0, 0);
	
	OdGeVector3d result = APIPointNative::subtract(p1, p2);
	
	EXPECT_TRUE(compareVector(expect, result));
	EXPECT_TRUE(true);
}

TEST(TestTopColumnPlate, TestPoints1) {
	//line1/
	OdGePoint3d point0 = OdGePoint3d(204.635807609476, 206.721421392678, 0);
	OdGePoint3d point1 = OdGePoint3d(-353.121999862027, 206.721421392678, 0);
	OdDbLine* line1 = new OdDbLine();
	//OdDbLinePtr line1 = OdDbLine::createObject();
	line1->setStartPoint(point0);
	line1->setEndPoint(point1);

	//line2/
	OdGePoint3d point2 = OdGePoint3d(204.635807609476, 206.721421392678, 0);
	OdGePoint3d point3 = OdGePoint3d(733.324935550048, 508.409085771316, 0);
	OdDbLine* line2 = new OdDbLine();
	//OdDbLinePtr line2 = OdDbLine::createObject();
	line2->setStartPoint(point2);
	line2->setEndPoint(point3);
	
	//listline/
	std::vector<OdDbLine*> listLine;
	//std::vector<OdDbLinePtr> listLine;
	listLine.push_back(line1);
	listLine.push_back(line2);

	//listwidth/
	double line_width = 200;
	std::vector<double> listWidth;
	listWidth.push_back(line_width);
	listWidth.push_back(line_width);

	//list vertex/
	OdGePoint3d pointvertex1 = OdGePoint3d(4.63580760947595, 6.72142139267767, 0);
	OdGePoint3d pointvertex2 = OdGePoint3d(4.63580760947595, 406.721421392678, 0);
	OdGePoint3d pointvertex3 = OdGePoint3d(404.635807609476, 406.721421392678, 0);
	OdGePoint3d pointvertex4 = OdGePoint3d(404.635807609476, 6.72142139267767, 0);
	std::vector<OdGePoint3d> listPoint;
	listPoint.push_back(pointvertex1);
	listPoint.push_back(pointvertex2);
	listPoint.push_back(pointvertex3);
	listPoint.push_back(pointvertex4);

	//expected/
	OdGePoint2d pointexpected0 = OdGePoint2d(379.539403182726, 450.446482650126);
	OdGePoint2d pointexpected1 = OdGePoint2d(501.625224104725, 239.089381894996);
	OdGePoint2d pointexpected2 = OdGePoint2d(404.635807609476, 6.72142139267767);
	OdGePoint2d pointexpected3 = OdGePoint2d(4.63580760947595, 6.72142139267767);
	OdGePoint2d pointexpected4 = OdGePoint2d(4.63580760947595, 406.721421392678);
	std::vector<OdGePoint2d> listexpectedPoint;
	listexpectedPoint.push_back(pointexpected0);
	listexpectedPoint.push_back(pointexpected1);
	listexpectedPoint.push_back(pointexpected2);
	listexpectedPoint.push_back(pointexpected3);
	listexpectedPoint.push_back(pointexpected4);
	OdGePoint3d centerpoint = OdGePoint3d(4.63580760947595, 6.72142139267767, 0);
	//std::vector<OdGePoint2d>test_result = APITopColumn::GetConnectPlatePoints(listLine, listWidth, listPoint, centerpoint, 25);
	//bool result = true;

	//for (int i = 0; i < listexpectedPoint.size(); i++)
	//{
	//	if (test_result[i].x != listexpectedPoint[i].x || test_result[i].y != listexpectedPoint[i].y)
	//	{
	//		result = false;
	//		break;
	//	}
	//}
	////EXPECT_TRUE(compareVector(listexpectedPoint, test_result));
	//EXPECT_TRUE(result) << "\nExpected:\n" << GetStrListPoint(listexpectedPoint)
	//	<< "\nActual: \n" << GetStrListPoint(test_result);
}

TEST(TestTopColumnPlate, TestPlateThickness)
{
	//pair1/
	OdGePoint3d point1line1pair1 = OdGePoint3d(49.5490831582854, 403.185644680911, 904.138693467337);
	OdGePoint3d point2line1pair1 = OdGePoint3d(-497.184585183423, 403.185644680911, 904.138693467337);
	OdDbLine* line1pair1 = new OdDbLine();
	line1pair1->setStartPoint(point1line1pair1);
	line1pair1->setEndPoint(point2line1pair1);

	OdGePoint3d point1line2pair1 = OdGePoint3d(49.5490831582854, 403.185644680911, 844.138693467337);
	OdGePoint3d point2line2pair1 = OdGePoint3d(-497.184585183423, 403.185644680911, 844.138693467337);
	OdDbLine* line2pair1 = new OdDbLine();
	line2pair1->setStartPoint(point1line2pair1);
	line2pair1->setEndPoint(point2line2pair1);

	//pair2/
	OdGePoint3d point1line1pair2 = OdGePoint3d(-320.427801263825, 403.185644680911, 342.369849246231);
	OdGePoint3d point2line1pair2 = OdGePoint3d(81.9681786356716, 403.185644680911, 482.333668341709);
	OdDbLine* line1pair2 = new OdDbLine();
	line1pair2->setStartPoint(point1line1pair2);
	line1pair2->setEndPoint(point2line1pair2);

	OdGePoint3d point1line2pair2 = OdGePoint3d(-320.427801263825, 403.185644680911, 272.369849246231);
	OdGePoint3d point2line2pair2 = OdGePoint3d(81.9681786356716, 403.185644680911, 412.333668341709);
	OdDbLine* line2pair2 = new OdDbLine();
	line2pair2->setStartPoint(point1line2pair2);
	line2pair2->setEndPoint(point2line2pair2);

	//pair3/
	OdGePoint3d point1line1pair3 = OdGePoint3d(802.178228886928, 403.185644680911, 882.994974874372);
	OdGePoint3d point2line1pair3 = OdGePoint3d(239.042550494969, 403.185644680911, 762.713567839196);
	OdDbLine* line1pair3 = new OdDbLine();
	line1pair3->setStartPoint(point1line1pair3);
	line1pair3->setEndPoint(point2line1pair3);

	OdGePoint3d point1line2pair3 = OdGePoint3d(802.178228886928, 403.185644680911, 832.994974874372);
	OdGePoint3d point2line2pair3 = OdGePoint3d(239.042550494969, 403.185644680911, 712.713567839196);
	OdDbLine* line2pair3 = new OdDbLine();
	line2pair3->setStartPoint(point1line2pair3);
	line2pair3->setEndPoint(point2line2pair3);

	//center point/
	OdGePoint3d centertoppoint = OdGePoint3d(201.7963, 203.1856, 1000);
	OdGePoint3d centerbottompoint = OdGePoint3d(201.7963, 203.1856, 0);

	auto solid3 = OdDb3dSolid::createObject();
	auto vec3 = centertoppoint - centerbottompoint;
	//solid3->createExtrudedSolid(pPolyline3, vec3, sweepOptionsRec);
	//solid3->transformBy(OdGeMatrix3d::translation(-vec3 / 2));
	//solid3->setColorIndex(colorIndex());

	//APITopColumn::GroupContactedPoints(centertoppoint, )
}
