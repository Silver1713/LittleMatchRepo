#pragma once
#include "imgui.h"
#include <filesystem>
#include <iostream>
#include "AssetLoader.hpp"

namespace Sage_Project
{

	void Initialize(const std::string& _root_dir);

	void Show();

	void Display_Directory(const std::string& path);
}
