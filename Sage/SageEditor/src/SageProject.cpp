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

	//void Display_Directory(const std::string& _full_directory)
	//{
	//	// Iterate over the _full_directory via filesystem directory iterator
	//	for (const auto& sub_dir : std::filesystem::directory_iterator(_full_directory))
	//	{
	//		// Assets/Prefabs/Scripts
	//		const auto& sub_dir_path = sub_dir.path();
	//		if (sub_dir.is_directory())
	//		{
	//			if (ImGui::TreeNode(sub_dir_path.filename().string().c_str()))
	//			{
	//				// Dummy files within each folder
	//				for (const auto& sub_dir_path_file : std::filesystem::directory_iterator(sub_dir_path))
	//				{
	//					// If it is a file within the sub directory
	//					if (!sub_dir_path_file.is_directory())
	//					{
	//						if (ImGui::Selectable(sub_dir_path_file.path().filename().string().c_str()))
	//						{
	//							std::string command = "start " + sub_dir_path_file.path().string();
	//							std::system(command.c_str());
	//						}
	//					}
	//				}
	//				Display_Directory(sub_dir_path.string());
	//				ImGui::TreePop();
	//			}
	//			
	//		}
	//	}
	//}

	void Display_Directory(const std::string& _full_directory)
	{
		if (_full_directory.find("Prefabs") != std::string::npos)
		{
			// Display prefabs instead of physical directory content
			const auto& prefabs = Assets::Prefabs::Get_Prefabs();
			for (const auto& [id, prefab] : prefabs)
			{
				ImGui::Selectable(id.c_str()); // Display as selectable

				// Make the prefab a drag source
				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
				{
					// Set the prefab ID as the drag payload
					ImGui::SetDragDropPayload("DND_PREFAB", id.c_str(), id.size() + 1);
					ImGui::Text("Dragging %s", id.c_str()); // Optional visual feedback
					ImGui::EndDragDropSource();
				}
			}
		}
		else
		{
			// Existing directory iteration code for non-prefab folders
			for (const auto& sub_dir : std::filesystem::directory_iterator(_full_directory))
			{
				const auto& sub_dir_path = sub_dir.path();
				if (sub_dir.is_directory())
				{
					if (ImGui::TreeNode(sub_dir_path.filename().string().c_str()))
					{
						Display_Directory(sub_dir_path.string());
						ImGui::TreePop();
					}
				}
				else if (ImGui::Selectable(sub_dir_path.filename().string().c_str()))
				{
					std::string command = "start " + sub_dir_path.string();
					std::system(command.c_str());
				}
			}
		}
	}



}