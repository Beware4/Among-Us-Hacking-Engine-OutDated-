#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <stdlib.h>

using namespace std;

DWORD GetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID) {
    DWORD dwModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID); // make snapshot of all modules within process
    MODULEENTRY32 ModuleEntry32 = { 0 };
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshot, &ModuleEntry32)) //store first Module in ModuleEntry32
    {
        do {
            if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0) // if Found Module matches Module we look for -> done!
            {
                dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &ModuleEntry32)); // go through Module entries in Snapshot and store in ModuleEntry32


    }
    CloseHandle(hSnapshot);
    return dwModuleBaseAddress;
}

DWORD GetPointerAddress(HWND hwnd, DWORD gameBaseAddr, DWORD address, vector<DWORD> offsets)
{
    DWORD pID = NULL; // Game process ID
    GetWindowThreadProcessId(hwnd, &pID);
    HANDLE phandle = NULL;
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    if (phandle == INVALID_HANDLE_VALUE || phandle == NULL);

    DWORD offset_null = NULL;
    ReadProcessMemory(phandle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
    DWORD pointeraddress = offset_null; // the address we need
    for (int i = 0; i < offsets.size() - 1; i++) // we dont want to change the last offset value so we do -1
    {
        ReadProcessMemory(phandle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
    }
    return pointeraddress += offsets.at(offsets.size() - 1); // adding the last offset
}

int weirdhacklol()
{
    HWND hwnd = FindWindowA(NULL, "Among Us");
    if (hwnd == NULL)
    {
        MessageBox(NULL, "ERROR! Unable to find Among Us! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
        system("restart");
    }
    else
    {
        DWORD procID;
        GetWindowThreadProcessId(hwnd, &procID);
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
        if (procID == NULL)
        {
            MessageBox(NULL, "ERROR! Unable to find process! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
            system("restart");
        }
        else
        {
            char gamemodule1[] = "GameAssembly.dll";
            DWORD gamebaseaddr1 = GetModuleBaseAddress(_T(gamemodule1), procID);
            DWORD weirdaddr = 0x0001B6BE3C;
            vector<DWORD> weirdOffsets{ 0x408, 0x5c, 0x0, 0x68, 0x4c };
            DWORD weirdPtrAddr = GetPointerAddress(hwnd, gamebaseaddr1, weirdaddr, weirdOffsets);
            float weirdoriginalvalue = ReadProcessMemory(handle, (LPVOID*)(weirdPtrAddr), 0, 0, 0);
            float weird = 0;
            WriteProcessMemory(handle, (LPVOID*)(weirdPtrAddr), &weird, sizeof(weird), 0);
            MessageBox(NULL, "Press OK to turn off the weird hack.", "Question", MB_ICONINFORMATION | MB_OK);
            WriteProcessMemory(handle, (LPVOID*)(weirdPtrAddr), &weirdoriginalvalue, sizeof(weirdoriginalvalue), 0);
            system("restart");
        }
    }
    return 0;
}

int speedhack()
{
    HWND hwnd = FindWindowA(NULL, "Among Us");
    if (hwnd == NULL)
    {
        MessageBox(NULL, "ERROR! Unable to find Among Us! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
        system("restart");
    }
    else
    {
        DWORD procID;
        GetWindowThreadProcessId(hwnd, &procID);
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
        if (procID == NULL)
        {
            MessageBox(NULL, "ERROR! Unable to find process! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
            system("restart");
        }
        else
        {
            char gamemodule1[] = "GameAssembly.dll";
            DWORD gamebaseaddr1 = GetModuleBaseAddress(_T(gamemodule1), procID);
            DWORD speedaddr = 0x0001C57494;
            vector<DWORD> speedOffsets{ 0x770, 0x20, 0x0, 0x644, 0x14 };
            DWORD speedPtrAddr = GetPointerAddress(hwnd, gamebaseaddr1, speedaddr, speedOffsets);
            float speed;
            cout << "Speed>> ";
            cin >> speed;
            WriteProcessMemory(handle, (LPVOID*)(speedPtrAddr), &speed, sizeof(speed), 0);
            system("restart");
        }
    }

    return 0;
}

int cooldownhack()
{
    HWND hwnd = FindWindowA(NULL, "Among Us");
    if (hwnd == NULL)
    {
        MessageBox(NULL, "ERROR! Unable to find Among Us! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
        system("restart");
    }
    else
    {
        DWORD procID;
        GetWindowThreadProcessId(hwnd, &procID);
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
        if (procID == NULL)
        {
            MessageBox(NULL, "ERROR! Unable to find process! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
            system("restart");
        }
        else
        {
            char gamemodule1[] = "GameAssembly.dll";
            DWORD gamebaseaddr1 = GetModuleBaseAddress(_T(gamemodule1), procID);
            DWORD killcooldownaddr = 0x0001C57494;
            vector<DWORD> cooldownOffsets{ 0x790, 0x0, 0x0, 0x644, 0x20 };
            DWORD killcooldownPtrAddr = GetPointerAddress(hwnd, gamebaseaddr1, killcooldownaddr, cooldownOffsets);
            float killcooldown;
            cout << "Kill Cooldown>> ";
            cin >> killcooldown;
            WriteProcessMemory(handle, (LPVOID*)(killcooldownPtrAddr), &killcooldown, sizeof(killcooldown), 0);
            system("restart");
        }
    }
    return 0;
}

int fakeimposterhack()
{
    HWND hwnd = FindWindowA(NULL, "Among Us");
    if (hwnd == NULL)
    {
        MessageBox(NULL, "ERROR! Unable to find Among Us! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
        system("restart");
    }
    else
    {
        DWORD procID;
        GetWindowThreadProcessId(hwnd, &procID);
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
        if (procID == NULL)
        {
            MessageBox(NULL, "ERROR! Unable to find process! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
            system("restart");
        }
        else
        {
            char gamemodule1[] = "GameAssembly.dll";
            DWORD gamebaseaddr1 = GetModuleBaseAddress(_T(gamemodule1), procID);
            DWORD impaddr = 0x0001B5DF50;
            vector<DWORD> imposterOffsets{ 0x5c, 0x0, 0x34, 0x2c };
            DWORD impPtrAddr = GetPointerAddress(hwnd, gamebaseaddr1, impaddr, imposterOffsets);
            int imp = 1;
            WriteProcessMemory(handle, (LPVOID*)(impPtrAddr), &imp, sizeof(imp), 0);
            system("restart");
        }
    }
    return 0;
}

int fakecrewmatehack()
{
    HWND hwnd = FindWindowA(NULL, "Among Us");
    if (hwnd == NULL)
    {
        MessageBox(NULL, "ERROR! Unable to find Among Us! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
        system("restart");
    }
    else
    {
        DWORD procID;
        GetWindowThreadProcessId(hwnd, &procID);
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
        if (procID == NULL)
        {
            MessageBox(NULL, "ERROR! Unable to find process! Restarting engine.", "ERROR!", MB_ICONERROR | MB_OK);
            system("restart");
        }
        else
        {
            char gamemodule1[] = "GameAssembly.dll";
            DWORD gamebaseaddr1 = GetModuleBaseAddress(_T(gamemodule1), procID);
            DWORD impaddr = 0x0001B5DF50;
            vector<DWORD> imposterOffsets{ 0x5c, 0x0, 0x34, 0x2c };
            DWORD impPtrAddr = GetPointerAddress(hwnd, gamebaseaddr1, impaddr, imposterOffsets);
            int imp = 0;
            WriteProcessMemory(handle, (LPVOID*)(impPtrAddr), &imp, sizeof(imp), 0);
            system("restart");
        }
    }
    return 0;
}

int run()
{
    int i = 1;
    while (i < 10)
    {
        int opt1 = MessageBox(NULL, "Would you like to change your characters speed?", "Option.1", MB_ICONQUESTION | MB_YESNO);
        switch (opt1)
        {
        case IDYES:
            speedhack();
        case IDNO:
            int opt2 = MessageBox(NULL, "Would you like to change the kill cooldown?", "Option.2", MB_ICONQUESTION | MB_YESNO);
            switch (opt2)
            {
            case IDYES:
                cooldownhack();
            case IDNO:
                int opt3 = MessageBox(NULL, "Do you want to be an imposter?", "Option.3", MB_ICONQUESTION | MB_YESNO);
                switch (opt3)
                {
                case IDYES:
                    fakeimposterhack();
                case IDNO:
                    int opt4 = MessageBox(NULL, "Do you want to be a crewmate?", "Option.4", MB_ICONQUESTION | MB_YESNO);
                    switch (opt4)
                    {
                    case IDYES:
                        fakecrewmatehack();
                    case IDNO:
                        int opt5GOLOLLLLLLL = MessageBox(NULL, "😂 IDK WHY I EVEN ADDED THIS HACK LOL!!!!! (NO LONGER WORKING)🤣", "😂(PATCHED)🤣", MB_ICONQUESTION | MB_ICONINFORMATION | MB_ICONWARNING | MB_ICONSTOP | MB_ICONASTERISK | MB_ICONEXCLAMATION | MB_ICONERROR | MB_ICONHAND | MB_YESNO);
                        switch (opt5GOLOLLLLLLL)
                        {
                        case IDYES:
                            weirdhacklol();
                        case IDNO:
                            run();
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    system("color 0A");
    run();

    return 0;
}
