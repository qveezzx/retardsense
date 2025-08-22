//many parts are from original author - ByteCorum      


#include "Core/Cheats.h"
#include "Offsets/Offsets.h"
#include "Resources/Language.hpp"
#include "Core/Init.h"
#include "Config/ConfigSaver.h"
#include "Helpers/Logger.h"
#include "Helpers/UIAccess.h"
#include <filesystem>
#include <KnownFolders.h>
#include <ShlObj.h>
#include <format>
#include <vector>
#include <random>
#include <windows.h>
#include <string>


std::vector<std::string> processNames = { "update", "loader", "helper", "service" };


std::vector<std::string> exeNames = {
	"ASUSupdateSvc.exe",
	"RuntineBrokerSvc.exe",
	"FaceITAC.exe",
	"TorBrowserSvc.exe"
};


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(0, exeNames.size() - 1);
std::string newName = exeNames[dist(gen)];


using namespace std;

namespace fs = filesystem;
string fileName;

void Cheat();

int main()
{
	// Make sure not to use UIAccess for debugging/profiling (UIAccess restarts the cheat)
#ifndef DBDEBUG
	DWORD err = PrepareForUIAccess();
	if (err != ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "Failed to elevate to UIAccess.", "Error", MB_OK);
		return -1;
	}
#endif

	Cheat(); // run your cheat

	// Array of possible executable names
	std::vector<std::string> exeNames = { "update.exe", "loader.exe", "helper.exe", "service.exe" };

	// Pick a random name
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, exeNames.size() - 1);
	std::string newExeName = exeNames[dist(gen)];

	// Schedule renaming after exit
	RenameSelf(newExeName);

	return 0;
}

void RandomizeProcessName()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, processNames.size() - 1);
	std::string name = processNames[dist(gen)];

	SetConsoleTitleA(name.c_str());
}

void RenameSelf(const std::string& newName)
{
	char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH); // current exe path
	std::string currentPath = path;

	std::string cmd = "cmd /C ping 127.0.0.1 -n 2 > NUL & rename \"" + currentPath + "\" \"" + newName + "\"";

	// Run cmd in a hidden process
	STARTUPINFOA si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void Cheat()
{
	ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
	SetConsoleTitle(L"RETARDsense | Loader - Driver");
	//Init::Verify::RandTitle();

	Log::Custom(R"LOGO(_____________________________________ __________________                                      
\______   \_   _____/\__    ___/  _  \\______   \______ \   ______ ____   ____   ______ ____  
 |       _/|    __)_   |    | /  /_\  \|       _/|    |  \ /  ___// __ \ /    \ /  ___// __ \ 
 |    |   \|        \  |    |/    |    \    |   \|    `   \\___ \\  ___/|   |  \\___ \\  ___/ 
 |____|_  /_______  /  |____|\____|__  /____|_  /_______  /____  >\___  >___|  /____  >\___  >
        \/        \/                 \/       \/        \/     \/     \/     \/     \/     \/   v2.0.1

https://github.com/qveezzx/retardsense



)LOGO", 13);

	if (!Init::Verify::CheckWindowVersion())
	{
		Log::Warning("Your OS is not Oficially supported, bugs may occur..", true);
	}

#ifndef DBDEBUG
	Log::Info("Checking cheat version");
	try
	{
		bool result = Init::Verify::CheckCheatVersion();
		Log::PreviousLine();
		if (result)
			Log::Fine("Your cheat version is up to date and supported.");
		else
			Log::Error("Your cheat version is out of support, Please update ASAP.");
	}
	catch (const std::exception& error)
	{
		Log::PreviousLine();
		Log::Error(format("Error: {}", error.what()));
	}

#endif

	Log::Info("Updating offsets");
	try
	{
		Offset.UpdateOffsets();
		Log::PreviousLine();
		Log::Fine("Offsets updated");
	}
	catch (const std::exception& error)
	{
		Log::PreviousLine();
		Log::Error(format("Error: {}", error.what()));
	}

	Log::Info("Connecting to kernel mode driver");
	if (memoryManager.ConnectDriver(L"\\\\.\\DragonBurn-kmd"))
	{
		Log::PreviousLine();
		Log::Fine("Successfully write to kernel-level driver");
	}
	else
	{
		Log::PreviousLine();
		Log::Error("Failed to write to kernel-level driver");
	}

	std::cout << '\n';
	bool preStart = false;
	while (memoryManager.GetProcessID(L"cs2.exe") == 0)
	{
		Log::PreviousLine();
		Log::Info("Waiting for CS2 process");
		preStart = true;
	}

	if (preStart)
	{
		Log::PreviousLine();
		Log::Info("Connecting to CS2 process (it may take some time)");
		Sleep(23000);
	}

	Log::PreviousLine();
	Log::Fine("Connected to CS2 proces..");
	Log::Info("Linking to CS2..");

#ifndef DBDEBUG
	try
	{
		if (!Init::Client::CheckCS2Version())
		{
			Log::PreviousLine();
			Log::Warning("Offsets are outdated, we'll update them ASAP. With current offsets, cheat may work unstable, or even get you VAC Banned eventually, USE AT YOUR OWN RISK.", true);
		}
	}
	catch (const std::exception& error)
	{
		Log::PreviousLine();
		Log::Error(format("Error: {}", error.what()));
	}
#endif

	if (!memoryManager.Attach(memoryManager.GetProcessID(L"cs2.exe")))
	{
		Log::PreviousLine();
		Log::Error("Failed to attach to the process.");
	}

	if (!gGame.InitAddress())
	{
		Log::PreviousLine();
		Log::Error("Failed to Init Address");
	}

	Log::PreviousLine();
	Log::Fine("Linked to CS2 process.");

	char documentsPath[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath) != S_OK)
		Log::Error("Failed to get the Documents folder path");

	MenuConfig::path = documentsPath;
	MenuConfig::docPath = documentsPath;
	MenuConfig::path += "\\retard";

	if (fs::exists(MenuConfig::docPath + "\\Adobe Software Data"))
	{
		fs::rename(MenuConfig::docPath + "\\Adobe Software Data", MenuConfig::path);
	}

	if (fs::exists(MenuConfig::path))
	{
		Log::Fine("Config folder connected: " + MenuConfig::path);
	}
	else
	{
		if (fs::create_directory(MenuConfig::path))
		{
			Log::Fine("Config folder connected: " + MenuConfig::path);
		}
		else
		{
			Log::Error("Failed to create the config directory");
		}
	}

	if (fs::exists(MenuConfig::path + "\\default.cfg"))
		MenuConfig::defaultConfig = true;

	Log::Fine("RETARDsense loaded - Enjoy.");

#ifndef DBDEBUG
	Sleep(3000);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	}
	catch (std::exception& error)
	{
		Log::Error(error.what());
	}
}