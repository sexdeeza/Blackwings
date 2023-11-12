#include "pch.h"

VOID Game::OnGameInit() 
{
#ifdef _DEBUG
    BOOL bAlloc = AllocConsole();

    if (bAlloc) {
        FILE* file = nullptr;

        freopen_s(&file, "CONIN$", "r", stdin);
        freopen_s(&file, "CONOUT$", "w", stdout);
        freopen_s(&file, "CONOUT$", "w", stderr);
    }
#endif

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    Patches::PatchWinAPI();
    Patches::PatchWinSock();

    DetourTransactionCommit();

    SPDLOG_INFO("Game initialized");
}

VOID Game::OnGameStart()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    if (Config::GameLogoSkip)
        Patches::PatchGameLogoSkip();
    if (Config::GameWindowSizing)
        Patches::PatchGameWindowSizing();

    DetourTransactionCommit();

    SPDLOG_INFO("Game started");
}
