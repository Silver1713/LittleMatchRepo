#include "SageProject.hpp"

namespace Sage_Project
{
	std::string root_directory;

	void Initialize(const std::string& _root_dir)
	{
		root_directory = _root_dir;
	}

	void Show()
	{
		ImGui::Begin("Project");
		Display_Directory(root_directory);
		ImGui::End();
	}

	void Display_Directory(const std::string& _full_directory)
	{
		// Iterate over the _full_directory via filesystem directory iterator
		for (const auto& sub_dir : std::filesystem::directory_iterator(_full_directory))
		{
			// Assets/Prefabs/Scripts
			const auto& sub_dir_path = sub_dir.path();
			if (sub_dir.is_directory())
			{
				if (ImGui::TreeNode(sub_dir_path.filename().string().c_str()))
				{
					// Dummy files within each folder
					for (const auto& sub_dir_path_file : std::filesystem::directory_iterator(sub_dir_path))
					{
						// If it is a file within the sub directory
						if (!sub_dir_path_file.is_directory())
						{
							if (ImGui::Selectable(sub_dir_path_file.path().filename().string().c_str()))
							{
								std::string command = "start " + sub_dir_path_file.path().string();
								std::system(command.c_str());
							}
							//ImGui::BulletText("%s", sub_dir_path_file.path().filename().string().c_str());
						}
					}
					Display_Directory(sub_dir_path.string());
					ImGui::TreePop();
				}
				
			}
		}
	}

}