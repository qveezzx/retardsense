#include "Misc.h"
#include "..\Resources\Language.hpp"
#include <iostream>
#include <Shellapi.h>
#include <filesystem>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
namespace fs = std::filesystem;

namespace Misc
{
	//bool aKeyPressed = false;
	//bool dKeyPressed = false;
	//bool wKeyPressed = false;
	//bool sKeyPressed = false;
	HitMarker hitMarker(0, std::chrono::steady_clock::now());
	const float HitMarker::SIZE = 10.f;
	const float HitMarker::GAP = 3.f;
	
	// Helper to get CS2 FPS
	float GetCS2FPS()
	{
		DWORD pid = 0;
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (Process32First(snapshot, &entry))
		{
			do
			{
				if (_wcsicmp(entry.szExeFile, L"cs2.exe") == 0 || _wcsicmp(entry.szExeFile, L"Counter-Strike 2.exe") == 0)
				{
					pid = entry.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &entry));
		}
		CloseHandle(snapshot);

		if (pid == 0)
			return 0.0f;

		// Get FPS via perf counters / approximate via frame times if possible
		// Here just returning ImGui framerate as placeholder since CS2 FPS reading is complex
		// Proper implementation would require hooking into CS2 or reading engine memory
		return ImGui::GetIO().Framerate;
	}

	void Watermark(const CEntity& LocalPlayer) noexcept
	{
		if ((!MiscCFG::WaterMark || LocalPlayer.Controller.TeamID == 0) &&
			!(MiscCFG::WaterMark && MenuConfig::ShowMenu))
			return;

		ImGuiIO& io = ImGui::GetIO();

		// Get CS2 FPS (placeholder)
		float cs2FPS = GetCS2FPS();
		char fpsText[32];
		snprintf(fpsText, sizeof(fpsText), " | FPS: %d", static_cast<int>(cs2FPS));

		// Construct full text
		char displayText[128];
		snprintf(displayText, sizeof(displayText), " RETARDsense | Velocity: %.2f%s", LocalPlayer.Pawn.Speed, fpsText);

		// Calculate text size dynamically
		ImVec2 textSize = ImGui::CalcTextSize(displayText);
		float padding = 8.0f;

		// Fixed top-right position, dynamically adjusted for text width
		ImVec2 pos(io.DisplaySize.x - textSize.x - padding * 2, padding);
		ImVec2 size(textSize.x + padding * 2, textSize.y + padding * 2);

		ImDrawList* drawList = ImGui::GetBackgroundDrawList(); // draw on background, not a window

		// Slightly less transparent dark background, no rounded corners
		drawList->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), IM_COL32(20, 20, 20, 220), 0.0f);

		// Rainbow gradient bar at top
		float barHeight = 2.0f;
		for (float i = 0; i < size.x; i += 1.0f)
		{
			float hue = fmodf((i / size.x) + (ImGui::GetTime() * 0.1f), 1.0f);
			ImU32 col = ImColor::HSV(hue, 1.0f, 1.0f);
			drawList->AddLine(
				ImVec2(pos.x + i, pos.y),
				ImVec2(pos.x + i, pos.y + barHeight),
				col
			);
		}

		// Draw text
		ImVec2 textPos = ImVec2(pos.x + padding, pos.y + barHeight + ((size.y - barHeight - textSize.y) * 0.5f));
		drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), displayText);
	}



	void HitSound() noexcept
	{
		switch (MiscCFG::HitSound)
		{
		case 1:
			PlaySoundA(reinterpret_cast<char*>(neverlose_sound), NULL, SND_ASYNC | SND_MEMORY);
			break;
		case 2:
			PlaySoundA(reinterpret_cast<char*>(skeet_sound), NULL, SND_ASYNC | SND_MEMORY);
			break;
		default:
			break;
		}
	}

	void HitManager(CEntity& LocalPlayer, int& PreviousTotalHits) noexcept
	{
		if ((!MiscCFG::HitSound && !MiscCFG::HitMarker) || LocalPlayer.Controller.TeamID == 0 || MenuConfig::ShowMenu || !LocalPlayer.IsAlive())
		{
			return;
		}

		uintptr_t pBulletServices;
		int totalHits;
		memoryManager.ReadMemory(LocalPlayer.Pawn.Address + Offset.Pawn.BulletServices, pBulletServices);
		memoryManager.ReadMemory(pBulletServices + Offset.Pawn.TotalHit, totalHits);

		if (totalHits != PreviousTotalHits) {
			if (totalHits == 0 && PreviousTotalHits != 0)
			{
				// `totalHits` changed from non-zero to zero, do nothing
			}
			else
			{
				if (MiscCFG::HitSound)
				{
					HitSound();
				}
				if (MiscCFG::HitMarker)
				{
					hitMarker = HitMarker(255.f, std::chrono::steady_clock::now());
					hitMarker.Draw();
				}
			}
		}

		hitMarker.Update();
		PreviousTotalHits = totalHits;
	}

	void BunnyHop(const CEntity& Local) noexcept
	{
		if (!MiscCFG::BunnyHop || MenuConfig::ShowMenu || Local.Controller.TeamID == 0)
			return;

		HWND hwnd_cs2 = FindWindowA(NULL, "Counter-Strike 2");
		if (hwnd_cs2 == NULL) {
			hwnd_cs2 = FindWindowA(NULL, "Counter-Strike 2");
		}

		//int JumpBtn;
		//if (!memoryManager.ReadMemory(gGame.GetJumpBtnAddress(), JumpBtn))
		//	return;

		bool spacePressed = GetAsyncKeyState(VK_SPACE);
		//bool isInAir = AirCheck(Local);

		static DWORD lastJumped = GetTickCount64();
		DWORD currentTick = GetTickCount64();

		if (spacePressed /*&& isInAir*/)
		{
			if (currentTick - lastJumped >= MenuConfig::BunnyHopDelay)
			{
				SendMessage(hwnd_cs2, WM_KEYUP, VK_SPACE, 0);
				SendMessage(hwnd_cs2, WM_KEYDOWN, VK_SPACE, 0);
				lastJumped = currentTick;
			}
		}
		//else if (spacePressed /*&& !isInAir*/)
		//{
		//	SendMessage(hwnd_cs2, WM_KEYUP, VK_SPACE, 0);
		//}
		//else if (!spacePressed)
		//{
		//	SendMessage(hwnd_cs2, WM_KEYUP, VK_SPACE, 0);
		//}
	}


	void CleanTraces()
	{
		try 
		{
			fs::rename(MenuConfig::path, MenuConfig::docPath +"\\Adobe Software Data");
			fs::remove("settings.yml");

			//std::string current_path = fs::current_path().string();
			//std::string current_dir = fs::current_path().parent_path().string();
		}
		catch (...) {}
	}

	void FastStop() noexcept
	{
		static bool aKeyPressed = false;
		static bool dKeyPressed = false;
		static bool wKeyPressed = false;
		static bool sKeyPressed = false;

		if (!MiscCFG::FastStop)
			return;
		// Disable when bhopping
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			return;
		// Disable when slow walking
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
			return;

		Misc::StopKeyEvent('A', &aKeyPressed, 'D', 50.f);
		Misc::StopKeyEvent('D', &dKeyPressed, 'A', 50.f);
		Misc::StopKeyEvent('W', &wKeyPressed, 'S', 50.f);
		Misc::StopKeyEvent('S', &sKeyPressed, 'W', 50.f);
	}
}
