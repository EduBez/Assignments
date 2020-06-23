#include "stdafx.h"
#include "Instrumentation.h"

using namespace std;
using namespace wmi;

//
//  WMI
//
wstring WMI::Memory()
{
    wstring result;

    MEMORYSTATUSEX memory;
    memory.dwLength = sizeof(MEMORYSTATUSEX);

    GlobalMemoryStatusEx(&memory);

    // Total physical memory (RAM)
    long double totalPhysMem = long double(memory.ullTotalPhys);

    // Physical memory currently used
    long double physMemUsed = long double(memory.ullTotalPhys)
                            - long double(memory.ullAvailPhys);

    // Percent of total used memory
    long double totalUsedMem = (physMemUsed / totalPhysMem) * 100;

    // Round value
    auto round = boost::math::lround(totalUsedMem);

    // Convert result to percent string
    result = boost::lexical_cast<std::wstring>(round) + L"%";

    return result;
}

wstring WMI::CPU()
{
    wstring result;

    PDH_HQUERY    cpuQuery;
    PDH_HCOUNTER  cpuTotal;

    PdhOpenQuery(NULL, NULL, &cpuQuery);

    const wchar_t* path = L"\\Processor(_Total)\\% Processor Time";
    PdhAddCounter(cpuQuery, path, NULL, &cpuTotal);

    PdhCollectQueryData(cpuQuery);

    PDH_FMT_COUNTERVALUE counterVal;

    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);

    // Round value
    auto round = boost::math::lround(counterVal.doubleValue);

    // Convert result to percent string
    result = boost::lexical_cast<std::wstring>(round) + L"%";

    return result;
}

wstring WMI::Processes()
{
    wstring result;

    // Counter for number of machine processes
    int count = 0;
    
    // Take a snapshot of all system processes
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        // Retrieve information for the first process
        if (Process32First(snap, &entry))
        {
            // Walk the snapshot of processes
            do {
                count += 1;
            }
            while (Process32Next(snap, &entry));
        }
    }
    // Clean the snapshot object
    CloseHandle(snap);

    // Convert result to percent string
    result = boost::lexical_cast<std::wstring>(count);

    return result;
}
