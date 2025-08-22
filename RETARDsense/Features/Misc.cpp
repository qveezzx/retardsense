#include "Misc.h"
#include "..\Resources\Language.hpp"
#include <iostream>
#include <Shellapi.h>
#include <filesystem>
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

	void Watermark(const CEntity& LocalPlayer) noexcept
	{
		if ((!MiscCFG::WaterMark || LocalPlayer.Controller.TeamID == 0) &&
			!(MiscCFG::WaterMark && MenuConfig::ShowMenu))
			return;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoScrollbar;

		// Reduced default position size
		ImVec2 defaultWinPos = MenuConfig::MarkWinPos;

		ImGui::SetNextWindowPos(defaultWinPos, ImGuiCond_Once);

		// Force solid dark background
		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(20, 20, 20, 255));

		// Set smaller font
		ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Ensure you have loaded a smaller font here

		ImGui::Begin("Watermark", nullptr, windowFlags);

		if (MenuConfig::MarkWinChengePos)
		{
			ImGui::SetWindowPos("Watermark", MenuConfig::MarkWinPos);
			MenuConfig::MarkWinChengePos = false;
		}

		Vec3 Pos = LocalPlayer.Pawn.Pos;
		int currentFPS = static_cast<int>(ImGui::GetIO().Framerate);

		char fpsText[32];
		snprintf(fpsText, sizeof(fpsText), " | FPS: %d", currentFPS);

		// ---- Rainbow gradient bar at top ----
		ImVec2 winPos = ImGui::GetWindowPos();
		ImVec2 winSize = ImGui::GetWindowSize();
		ImDrawList* drawList = ImGui::GetWindowDrawList();

		float barHeight = 2.0f; // slightly smaller
		for (float i = 0; i < winSize.x; i += 1.0f)
		{
			float hue = fmodf((i / winSize.x) + (ImGui::GetTime() * 0.1f), 1.0f);
			ImU32 col = ImColor::HSV(hue, 1.0f, 1.0f);
			drawList->AddLine(
				ImVec2(winPos.x + i, winPos.y),
				ImVec2(winPos.x + i, winPos.y + barHeight),
				col
			);
		}

		// ---- Center text vertically (below rainbow bar) ----
		float textHeight = ImGui::GetTextLineHeight();
		float availHeight = winSize.y - barHeight;
		float padding = (availHeight - textHeight) * 0.5f;

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + padding);

		// ---- White text ----
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
		ImGui::Text(" RETARDsense | Velocity: %.2f%s", LocalPlayer.Pawn.Speed, fpsText);
		ImGui::PopStyleColor();

		// ---- Dynamically center resize ----
		ImVec2 textSize = ImGui::CalcTextSize(" RETARDsense | Velocity: 000.00 | FPS: 000");
		ImVec2 newSize = ImVec2(textSize.x + 16.0f, textSize.y + 16.0f); // Add small padding

		// Compute current center
		ImVec2 centerPos;
		centerPos.x = MenuConfig::MarkWinPos.x + winSize.x * 0.5f;
		centerPos.y = MenuConfig::MarkWinPos.y + winSize.y * 0.5f;

		// Set new top-left so window resizes from center
		MenuConfig::MarkWinPos.x = centerPos.x - newSize.x * 0.5f;
		MenuConfig::MarkWinPos.y = centerPos.y - newSize.y * 0.5f;

		ImGui::SetWindowSize(newSize);


		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopFont();
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

		static DWORD lastJump = 0;
		DWORD currentTick = GetTickCount64();

		// Only trigger if space is pressed
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) // high bit = key down
		{
			// Simple cooldown to prevent missed jumps
			if (currentTick - lastJump >= MenuConfig::BunnyHopDelay)
			{
				// Simulate fast key press with SendInput
				INPUT input = {};
				input.type = INPUT_KEYBOARD;
				input.ki.wVk = VK_SPACE;

				// Key down
				input.ki.dwFlags = 0;
				SendInput(1, &input, sizeof(INPUT));

				// Key up immediately
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &input, sizeof(INPUT));

				lastJump = currentTick;
			}
		}
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
