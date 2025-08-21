# Minimum required CMake version
cmake_minimum_required(VERSION 3.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /MT /D NDEBUG")

# Project name
project(RETARDsense)

#Target dir
set_target_properties(RETARDsense PROPERTIES
    OUTPUT_NAME "RETARDsense"
    RUNTIME_OUTPUT_DIRECTORY "built")

# Include Directories
set(INCLUDE_DIRS
  Config
  Core
  Features
  Game
  Helpers
  Offsets
  OS-ImGui/imgui
  OS-ImGui
  Resources
  Libs/json
)

# Add an executable from source files
add_executable(RETARDsense
    RETARDsense/main.cpp
    RETARDsense/Config/ConfigMenu.cpp
    RETARDsense/Config/ConfigMenu.hpp
    RETARDsense/Config/ConfigSaver.cpp
    RETARDsense/Config/ConfigSaver.hpp
    RETARDsense/Config/MenuConfig.hpp
    RETARDsense/RETARDsense/Core/Cheats.cpp
    RETARDsense/Core/Cheats.h
    RETARDsense/Core/Globals.hpp
    RETARDsense/Core/GlobalVars.cpp
    RETARDsense/Core/GlobalVars.h
    RETARDsense/Core/GUI.h
    RETARDsense/Core/Init.h
    RETARDsense/Core/ProcessManager.hpp
    RETARDsense/Core/Render.hpp
    RETARDsense/Features/Aimbot.cpp
    RETARDsense/Features/Aimbot.h
    RETARDsense/Features/BombTimer.h
    RETARDsense/Features/ESP.h
    RETARDsense/Features/Misc.cpp
    RETARDsense/Features/Misc.h
    RETARDsense/Features/Radar.cpp
    RETARDsense/Features/Radar.h
    RETARDsense/RETARDsense/Features/RCS.h
    RETARDsense/RETARDsense/Features/RCS.cpp
    RETARDsense/Features/SpectatorList.h
    RETARDsense/Features/TriggerBot.cpp
    RETARDsense/Features/TriggerBot.h
    RETARDsense/Game/Bone.cpp
    Game/Bone.h
    RETARDsense/Game/Entity.cpp
    RETARDsense/Game/Entity.h
    RETARDsense/Game/Game.cpp
    RETARDsense/Game/Game.h
    RETARDsense/Game/View.hpp
    RETARDsense/Helpers/Format.h
    RETARDsense/Helpers/GetWeaponIcon.h
    RETARDsense/Helpers/Mouse.cpp
    RETARDsense/Helpers/Mouse.h
    RETARDsense/Helpers/Random.h
    RETARDsense/Libs/json.hpp
    RETARDsense/Offsets/Offsets.h
    RETARDsense/Offsets/Offsets.cpp
    RETARDsense/OS-ImGui/OS-ImGui.cpp
    RETARDsense/OS-ImGui/OS-ImGui.h
    RETARDsense/OS-ImGui/OS-ImGui_Base.cpp
    RETARDsense/OS-ImGui/OS-ImGui_Base.h
    RETARDsense/OS-ImGui/OS-ImGui_Exception.hpp
    RETARDsense/OS-ImGui/OS-ImGui_External.cpp
    RETARDsense/OS-ImGui/OS-ImGui_External.h
    RETARDsense/OS-ImGui/OS-ImGui_Struct.h
    RETARDsense/OS-ImGui/imgui/imconfig.h
    RETARDsense/OS-ImGui/imgui/imgui.cpp
    RETARDsense/OS-ImGui/imgui/imgui.h
    RETARDsense/OS-ImGui/imgui/imgui_demo.cpp
    RETARDsense/OS-ImGui/imgui/imgui_draw.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_dx11.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_dx11.h
    RETARDsense/OS-ImGui/imgui/imgui_impl_win32.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_win32.h
    RETARDsense/OS-ImGui/imgui/imgui_internal.h
    RETARDsense/OS-ImGui/imgui/imgui_tables.cpp
    RETARDsense/OS-ImGui/imgui/imgui_widgets.cpp
    RETARDsense/OS-ImGui/imgui/imstb_rectpack.h
    RETARDsense/OS-ImGui/imgui/imstb_textedit.h
    RETARDsense/OS-ImGui/imgui/imstb_truetype.h
    RETARDsense/OS-ImGui/stb/stb_image.h
    RETARDsense/Resources/font.h
    RETARDsense/Resources/Images.h
    RETARDsense/Resources/Language.h
    RETARDsense/Resources/Sounds.h
    RETARDsense/Resources/WeaponIcon.h
    RETARDsense/main.cpp
    RETARDsense/Config/ConfigMenu.cpp
    RETARDsense/Config/ConfigMenu.hpp
    RETARDsense/Config/ConfigSaver.cpp
    RETARDsense/Config/ConfigSaver.hpp
    RETARDsense/Config/MenuConfig.hpp
    RETARDsense/RETARDsense/Core/Cheats.cpp
    RETARDsense/Core/Cheats.h
    RETARDsense/Core/Globals.hpp
    RETARDsense/Core/GlobalVars.cpp
    RETARDsense/Core/GlobalVars.h
    RETARDsense/Core/GUI.h
    RETARDsense/Core/Init.h
    RETARDsense/Core/ProcessManager.hpp
    RETARDsense/Core/Render.hpp
    RETARDsense/Features/Aimbot.cpp
    RETARDsense/Features/Aimbot.h
    RETARDsense/Features/BombTimer.h
    RETARDsense/Features/ESP.h
    RETARDsense/Features/Misc.cpp
    RETARDsense/Features/Misc.h
    RETARDsense/Features/Radar.cpp
    RETARDsense/Features/Radar.h
    RETARDsense/RETARDsense/Features/RCS.h
    RETARDsense/RETARDsense/Features/RCS.cpp
    RETARDsense/Features/SpectatorList.h
    RETARDsense/Features/TriggerBot.cpp
    RETARDsense/Features/TriggerBot.h
    RETARDsense/Game/Bone.cpp
    Game/Bone.h
    RETARDsense/Game/Entity.cpp
    RETARDsense/Game/Entity.h
    RETARDsense/Game/Game.cpp
    RETARDsense/Game/Game.h
    RETARDsense/Game/View.hpp
    RETARDsense/Helpers/Format.h
    RETARDsense/Helpers/GetWeaponIcon.h
    RETARDsense/Helpers/Mouse.cpp
    RETARDsense/Helpers/Mouse.h
    RETARDsense/Helpers/Random.h
    RETARDsense/Libs/json.hpp
    RETARDsense/Offsets/Offsets.h
    RETARDsense/Offsets/Offsets.cpp
    RETARDsense/OS-ImGui/OS-ImGui.cpp
    RETARDsense/OS-ImGui/OS-ImGui.h
    RETARDsense/OS-ImGui/OS-ImGui_Base.cpp
    RETARDsense/OS-ImGui/OS-ImGui_Base.h
    RETARDsense/OS-ImGui/OS-ImGui_Exception.hpp
    RETARDsense/OS-ImGui/OS-ImGui_External.cpp
    RETARDsense/OS-ImGui/OS-ImGui_External.h
    RETARDsense/OS-ImGui/OS-ImGui_Struct.h
    RETARDsense/OS-ImGui/imgui/imconfig.h
    RETARDsense/OS-ImGui/imgui/imgui.cpp
    RETARDsense/OS-ImGui/imgui/imgui.h
    RETARDsense/OS-ImGui/imgui/imgui_demo.cpp
    RETARDsense/OS-ImGui/imgui/imgui_draw.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_dx11.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_dx11.h
    RETARDsense/OS-ImGui/imgui/imgui_impl_win32.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_win32.h
    RETARDsense/OS-ImGui/imgui/imgui_internal.h
    RETARDsense/OS-ImGui/imgui/imgui_tables.cpp
    RETARDsense/OS-ImGui/imgui/imgui_widgets.cpp
    RETARDsense/OS-ImGui/imgui/imstb_rectpack.h
    RETARDsense/OS-ImGui/imgui/imstb_textedit.h
    RETARDsense/OS-ImGui/imgui/imstb_truetype.h
    RETARDsense/OS-ImGui/stb/stb_image.h
    RETARDsense/Resources/font.h
    RETARDsense/Resources/Images.h
    RETARDsense/Resources/Language.h
    RETARDsense/Resources/Sounds.h
    RETARDsense/Resources/WeaponIcon.h
    RETARDsense/main.cpp
    RETARDsense/Config/ConfigMenu.cpp
    RETARDsense/Config/ConfigMenu.hpp
    RETARDsense/Config/ConfigSaver.cpp
    RETARDsense/Config/ConfigSaver.hpp
    RETARDsense/Config/MenuConfig.hpp
    RETARDsense/RETARDsense/Core/Cheats.cpp
    RETARDsense/Core/Cheats.h
    RETARDsense/Core/Globals.hpp
    RETARDsense/Core/GlobalVars.cpp
    RETARDsense/Core/GlobalVars.h
    RETARDsense/Core/GUI.h
    RETARDsense/Core/Init.h
    RETARDsense/Core/ProcessManager.hpp
    RETARDsense/Core/Render.hpp
    RETARDsense/Features/Aimbot.cpp
    RETARDsense/Features/Aimbot.h
    RETARDsense/Features/BombTimer.h
    RETARDsense/Features/ESP.h
    RETARDsense/Features/Misc.cpp
    RETARDsense/Features/Misc.h
    RETARDsense/Features/Radar.cpp
    RETARDsense/Features/Radar.h
    RETARDsense/RETARDsense/Features/RCS.h
    RETARDsense/RETARDsense/Features/RCS.cpp
    RETARDsense/Features/SpectatorList.h
    RETARDsense/Features/TriggerBot.cpp
    RETARDsense/Features/TriggerBot.h
    RETARDsense/Game/Bone.cpp
    Game/Bone.h
    RETARDsense/Game/Entity.cpp
    RETARDsense/Game/Entity.h
    RETARDsense/Game/Game.cpp
    RETARDsense/Game/Game.h
    RETARDsense/Game/View.hpp
    RETARDsense/Helpers/Format.h
    RETARDsense/Helpers/GetWeaponIcon.h
    RETARDsense/Helpers/Mouse.cpp
    RETARDsense/Helpers/Mouse.h
    RETARDsense/Helpers/Random.h
    RETARDsense/Libs/json.hpp
    RETARDsense/Offsets/Offsets.h
    RETARDsense/Offsets/Offsets.cpp
    RETARDsense/OS-ImGui/OS-ImGui.cpp
    RETARDsense/OS-ImGui/OS-ImGui.h
    RETARDsense/OS-ImGui/OS-ImGui_Base.cpp
    RETARDsense/OS-ImGui/OS-ImGui_Base.h
    RETARDsense/OS-ImGui/OS-ImGui_Exception.hpp
    RETARDsense/OS-ImGui/OS-ImGui_External.cpp
    RETARDsense/OS-ImGui/OS-ImGui_External.h
    RETARDsense/OS-ImGui/OS-ImGui_Struct.h
    RETARDsense/OS-ImGui/imgui/imconfig.h
    RETARDsense/OS-ImGui/imgui/imgui.cpp
    RETARDsense/OS-ImGui/imgui/imgui.h
    RETARDsense/OS-ImGui/imgui/imgui_demo.cpp
    RETARDsense/OS-ImGui/imgui/imgui_draw.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_dx11.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_dx11.h
    RETARDsense/OS-ImGui/imgui/imgui_impl_win32.cpp
    RETARDsense/OS-ImGui/imgui/imgui_impl_win32.h
    RETARDsense/OS-ImGui/imgui/imgui_internal.h
    RETARDsense/OS-ImGui/imgui/imgui_tables.cpp
    RETARDsense/OS-ImGui/imgui/imgui_widgets.cpp
    RETARDsense/OS-ImGui/imgui/imstb_rectpack.h
    RETARDsense/OS-ImGui/imgui/imstb_textedit.h
    RETARDsense/OS-ImGui/imgui/imstb_truetype.h
    RETARDsense/OS-ImGui/stb/stb_image.h
    RETARDsense/Resources/font.h
    RETARDsense/Resources/Images.h
    RETARDsense/Resources/Language.h
    RETARDsense/Resources/Sounds.h
    RETARDsense/Resources/WeaponIcon.h
)

# Include OS-ImGui headers
include_directories(${OS-ImGui_INCLUDE_DIRS})

# Linking with JSON
include_directories(${json_INCLUDE_DIRS})

# Target Executable
add_executable(RETARDsense ${SOURCE_FILES})

target_sources(RETARDsense
    PRIVATE
        RETARDsense/AssemblyInfo.rc)

add_custom_command(
    OUTPUT AssemblyInfo.res
    COMMAND windres RETARDsense/AssemblyInfo.rc
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
link_directories(${CMAKE_CURRENT_BINARY_DIR})