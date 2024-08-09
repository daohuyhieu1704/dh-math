#pragma once
#include <PromptEntitySelection.h>
#include "DisposableWrapper.h"
#include <Entity.h>
#include <GLEngineNative.h>

using namespace MathCore;
using namespace MathCore::Geom;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

namespace MathGL
{
    public delegate void EntityPickedDelegate();
    public delegate void EntitiesSelectedCallback();

    public ref class EntitySelection : MathCore::DisposableWrapper
    {
    public:
        ~EntitySelection();
        EntitySelection();
        Task<List<Entity^>^>^ getEntities();
    private:
        PromptEntitySelection* GetImpObj();
        static void OnEntityPicked()
        {
            auto& entities = GLEngineNative::GetInstance()->m_entities;
            int totalSelected = 0;
			for (int i = 0; i < entities.size(); i++)
			{
				if (entities[i]->getIsSelected())
				{
					totalSelected++;
				}
			}
            List<Entity^>^ entityReturn = gcnew List<Entity^>(totalSelected);
            for (int i = 0; i < entities.size(); i++)
            {
				if (entities[i]->getIsSelected())
				{
                    entityReturn->Add(gcnew Entity(IntPtr(entities[i]), false));
				}
            }

            _tcs->SetResult(entityReturn);
        }

        static EntityPickedDelegate^ _entityPickedDelegate;
        static TaskCompletionSource<List<Entity^>^>^ _tcs;
    };
}
