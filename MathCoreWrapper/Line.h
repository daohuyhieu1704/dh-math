#pragma once
#include "ObjectBase.h"
#include "Point3d.h"
#include <OdDbLine.h>
#include <json.hpp>


namespace MathCore
{
    using namespace Geom;
    namespace DatabaseServices
    {
		public ref class Line : public ObjectBase
        {
        public:
			Line(Point3d startPnt, Point3d endPnt) : ObjectBase(System::IntPtr(0), false)
            {
                StartPnt = startPnt;
                EndPnt = endPnt;
            }

            property Point3d StartPnt
            {
                Point3d get()
                {
                    return Point3d(0,0,0);
                    // return Point3d::FromNative(GetImpObj()->GetStartPoint());
                }
                void set(Point3d value)
                {
                    // GetImpObj()->SetStartPoint(value.ToNative());
                }
            }

            property Point3d EndPnt
            {
                Point3d get()
                {
                    // return Point3d::FromNative(GetImpObj()->GetEndPoint());
					return Point3d(0, 0, 0);
                }
                void set(Point3d value)
                {
                    //GetImpObj()->SetEndPoint(value.ToNative());
                }
            }

            ObjectBase^ Clone() override
            {
                //return gcnew ObjectBase(System::IntPtr(GetImpObj()->Clone()), true);
				return nullptr;
            }

            property System::String^ Json
            {
                System::String^ get()
                {
					nlohmann::json json = GetImpObj()->ToJson();
                    std::string jsonString = json.dump();
                    return gcnew System::String(jsonString.c_str());
                }
            }

        private:
            OdDbLine* GetImpObj()
            {
                void* obj = DisposableWrapper::GetImpObj();
                OdDbLine* line = static_cast<OdDbLine*>(obj);
                return line;
            }
        };
    }
}

