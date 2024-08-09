#include "pch.h"
#include "EntitySelection.h"
namespace MathGL
{
    EntitySelection::~EntitySelection()
    {
    }

    EntitySelection::EntitySelection() : DisposableWrapper(System::IntPtr(new PromptEntitySelection()), true)
    {
    }

    Task<List<Entity^>^>^ EntitySelection::getEntities()
    {
        GLEngineNative::GetInstance()->isSelectMode = true;
        _tcs = gcnew TaskCompletionSource<List<Entity^>^>();

        _entityPickedDelegate = gcnew EntityPickedDelegate(&EntitySelection::OnEntityPicked);

        IntPtr ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_entityPickedDelegate);
        GLEngineNative::GetInstance()->SetEntityPickedCallback(static_cast<EntityPickedCallback>(ptr.ToPointer()));
        return _tcs->Task;
    }

    PromptEntitySelection* EntitySelection::GetImpObj()
    {
        void* obj = DisposableWrapper::GetImpObj();
        return static_cast<PromptEntitySelection*>(obj);
    }
}