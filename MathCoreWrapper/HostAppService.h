#pragma once
#include <OdHostAppService.h>

public ref class HostAppService
{
public:
    static property HostAppService^ Instance
    {
        HostAppService^ get()
        {
            if (instance == nullptr)
            {
                instance = gcnew HostAppService();
            }
            return instance;
        }
    }
private:
    HostAppService();
    static HostAppService^ instance = nullptr;
    OdHostAppService* m_pHostAppService;
};