/* Start Header ************************************************************************/
/*!
\file		Game.cpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		15 September 2024
\brief		Contains the definitions of functions handling the game scene. Currently
			used as testbed for core engine features like user input, instantiation 
			and stress tests.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "AssetLoader.hpp"
#include "Prefabs.hpp"
#include "SageRenderer.hpp"
#include "SageHelper.hpp"
#include "SageAudio.hpp"
#include "KeyInputs.h"
#include "Game.hpp"
#include "Components/Physics.hpp"


#include <iostream>
#include <random>

//FOR TESTING PURPOSES
#include <cstdlib> // for srand()
#include <memory>	


namespace Game {
	//TESTS
	static unsigned int const game_objects_to_create{ 2500 };
	static ToastBox::Vec3 const min_pos{ -960.0f,-540.0f,0.0f }, max_pos{ 1920.0f,1080.0f,0.0f };
	static ToastBox::Vec3 const min_rot{ 0.0f,0.0f,0.0f }, max_rot{ 360.0f,360.0f,0.0f };
	static ToastBox::Vec3 const min_scale{ 1.0f,1.0f,0.0f }, max_scale{ 10.0f,10.0f,0.0f };
	static ToastBox::Vec3 const min_col{ 0.0f,0.0f,0.0f }, max_col{ 100.0f,100.0f,100.0f };

	static std::unordered_map<std::string, GameObject*> game_objects;
	static std::unordered_map<std::string, Transform*> transform_cache;
	static std::unordered_map<std::string, BoxCollider2D*> collider_cache;

	static SageCamera camera;
	static SageViewport vp;


	static bool enable_collider_view{ false };

	/*!*****************************************************************************
	  \brief
		Loads data the scene may need
	*******************************************************************************/
	void Load()
	{
		game_objects.clear();
		transform_cache.clear();

		transform_cache["Player"] = dynamic_cast<Transform*>(Game_Objects::Get_Game_Object("Player")->Get_Component(TRANSFORM));

		auto& objects = Game_Objects::Get_Game_Objects();
		for (auto& object : objects)
		{
			BoxCollider2D* collider = dynamic_cast<BoxCollider2D*>(object.second->Get_Component(BOXCOLLIDER2D));
			if (collider)
			{
				collider_cache[object.first] = collider;
			}
		}

		//Creates 2.5k instantiated "WHITE" prefab to test
		for (unsigned int i{}; i < game_objects_to_create; ++i)
		{
			game_objects[std::to_string(i)] = Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab("WHITE"), "White_" + std::to_string(i));
			transform_cache[std::to_string(i)] = dynamic_cast<Transform*>(game_objects[std::to_string(i)]->Get_Component(TRANSFORM));

			//randomize properties
			ToastBox::Vec3 pos{ (float)(std::rand() % (int)max_pos.x + (int)min_pos.x), (float)(std::rand() % (int)max_pos.y + (int)min_pos.y),0.0f };
			ToastBox::Vec3 rot{ (float)(std::rand() % (int)max_rot.x + (int)min_rot.x), (float)(std::rand() % (int)max_rot.y + (int)min_rot.y),0.0f };
			ToastBox::Vec3 scale{ (float)(std::rand() % (int)max_scale.x + (int)min_scale.x), (float)(std::rand() % (int)max_scale.y + (int)min_scale.y),0.0f };
			ToastBox::Vec3 col{ (float)(std::rand() % (int)max_col.x + (int)min_col.x) / 100.0f, (float)(std::rand() % (int)max_col.y + (int)min_col.y) / 100.0f,(float)(std::rand() % (int)max_col.z + (int)min_col.z) / 100.0f };

			transform_cache[std::to_string(i)]->Set_Position(pos);
			transform_cache[std::to_string(i)]->Set_Rotation(rot);
			transform_cache[std::to_string(i)]->Set_Scale(scale);

			Sprite2D* s = dynamic_cast<Sprite2D*>(game_objects[std::to_string(i)]->Get_Component(SPRITE2D));
			s->Set_Colour({ col[0],col[1],col[2] });

			game_objects[std::to_string(i)]->Disable();
		}
	}

	/*!*****************************************************************************
	  \brief
		Initializes the scene
	*******************************************************************************/
	void Init()
	{
		camera.init({ 50,0 }, { static_cast<float>(SageHelper::WINDOW_WIDTH),  static_cast<float>(SageHelper::WINDOW_HEIGHT) }, 0.f, SageCamera::SageCameraType::SAGE_ORTHO);
		vp.set_dims({ static_cast<float>(SageHelper::WINDOW_WIDTH),  static_cast<float>(SageHelper::WINDOW_HEIGHT) });
		vp.calculate_viewport_xform();

		SageRenderer::Set_Current_View(&camera);
		SageRenderer::Set_Current_View(vp);

		vp.setViewport();

		SageAudio::Play_Sound("bgm_main_menu", LOOP);
		SageAudio::Play_Sound("ambient_rain", LOOP);
		

		Physics* plrphy = dynamic_cast<Physics*>(Game_Objects::Get_Game_Object("Player")->Get_Component(PHYSICS));
		plrphy->Set_Gravity_Disable(false);
		
		SageAudio::Play_Sound("bgm_main_menu", LOOP);
		SageAudio::Play_Sound("ambient_rain", LOOP);

	}

	/*!*****************************************************************************
	  \brief
		Handles input checks in the scene
	*******************************************************************************/
	void Input()
	{
		bool movement = false;
		float move_speed = 250.f;
		Physics* plrphy = dynamic_cast<Physics*>(Game_Objects::Get_Game_Object("Player")->Get_Component(PHYSICS));
		//tests
		if (SAGEInputHandler::Get_Key(SAGE_KEY_W))
		{
			plrphy->Get_Velocity().y = (float)SageHelper::delta_time * move_speed;
			movement = true;
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_A))
		{
			plrphy->Get_Velocity().x = (float)SageHelper::delta_time * -move_speed;
			movement = true;
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_S))
		{
			plrphy->Get_Velocity().y = (float)SageHelper::delta_time * -move_speed;
			movement = true;
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_D))
		{
			plrphy->Get_Velocity().x = (float)SageHelper::delta_time * move_speed;
			movement = true;
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_Q))
		{
			transform_cache["Player"]->Rotate({ (float)SageHelper::delta_time * 10.0f,0.0f,0.f });
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_E))
		{
			transform_cache["Player"]->Rotate({ (float)SageHelper::delta_time * (-10.0f),0.0f,0.f });
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_Z))
		{
			transform_cache["Player"]->Scale({ (float)SageHelper::delta_time * 100.0f,(float)SageHelper::delta_time * 100.0f,0.f });
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_X))
		{
			transform_cache["Player"]->Scale({ (float)SageHelper::delta_time * (-100.0f),(float)SageHelper::delta_time * (-100.0f),0.f });
		}

		if (SAGEInputHandler::Get_Key(SAGE_KEY_I))
		{
			SageRenderer::camera->Move_Camera({ 0.f,1.f }, 100.f);
		}
		else if (SAGEInputHandler::Get_Key(SAGE_KEY_K))
		{
			SageRenderer::camera->Move_Camera({ 0.f,-1.f }, 100.f);
		}
		else if (SAGEInputHandler::Get_Key(SAGE_KEY_J))
		{
			SageRenderer::camera->Move_Camera({ -1.f,0.f }, 100.f);
		}
		else if (SAGEInputHandler::Get_Key(SAGE_KEY_L))
		{
			SageRenderer::camera->Move_Camera({ 1.f,0.f }, 100.f);
		}
		else if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_V))
		{
			for (auto& collider : collider_cache)
			{
				collider.second->Set_Debug(!collider.second->Get_Debug());
			}

			enable_collider_view = !enable_collider_view;


		}
		else if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_G))
		{
			static bool g = true;
			g = !g;
			plrphy->Set_Gravity_Disable(g);
		}



		if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_1))
		{
			if (game_objects["0"]->Is_Enabled())
			{
				return;
			}

			for (unsigned int i{}; i < game_objects_to_create; ++i)
			{
				game_objects[std::to_string(i)]->Enable();
			}
		}
		if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_2))
		{
			if (!game_objects["0"]->Is_Enabled())
			{
				return;
			}

			for (unsigned int i{}; i < game_objects_to_create; ++i)
			{
				game_objects[std::to_string(i)]->Disable();
			}
		}
		if (SAGEInputHandler::Get_Mouse_Clicked(SAGE_MOUSE_BUTTON_LEFT))
		{
			double x, y;
			SAGEInputHandler::Get_Mouse_Position(x, y);
			ToastBox::Vec2 mouse_pos{ static_cast<float>(x), static_cast<float>(y) };

			ToastBox::Vec2 world = SageRenderer::camera->Screen_To_World(mouse_pos);


			std::cout << "World: " << world.x << " " << world.y << std::endl;

			GameObject* random = Game_Objects::Instantiate(Prefabs::Get_Prefab("SPAWN"), "White_1");
			transform_cache["White_1"] = dynamic_cast<Transform*>(random->Get_Component(TRANSFORM));
			collider_cache["White_1"] = random->Get_Component<BoxCollider2D>();

			random->Get_Component<BoxCollider2D>()->Set_Debug(enable_collider_view);

			float m_min_scale[3] = { 10.0f,10.0f,0.0f }, m_max_scale[3] = { 100.0f,100.0f,0.0f };

			ToastBox::Vec3 pos{ (float)(std::rand() % (int)max_pos.x + (int)min_pos.x), (float)(std::rand() % (int)max_pos.y + (int)min_pos.y),0.0f };
			ToastBox::Vec3 rot{ (float)(std::rand() % (int)max_rot.x + (int)min_rot.x), (float)(std::rand() % (int)max_rot.y + (int)min_rot.y),0.0f };
			ToastBox::Vec3 scale{ (float)(std::rand() % (int)m_max_scale[0] + (int)m_min_scale[0]), (float)(std::rand() % (int)m_max_scale[1] + (int)m_min_scale[1]),0.0f};

			transform_cache["White_1"]->Set_Position(pos);
			transform_cache["White_1"]->Set_Rotation(rot);
			transform_cache["White_1"]->Set_Scale(scale);

		}
		if (SAGEInputHandler::Get_Mouse_Clicked(SAGE_MOUSE_BUTTON_RIGHT))
		{

			transform_cache["Player"]->Translate({ 0.f,-100.0f,0.f });
		}
		if (SAGEInputHandler::Get_Mouse_Clicked(SAGE_MOUSE_BUTTON_MIDDLE))
		{
			transform_cache["Player"]->Translate({ -100.0f,0.f,0.f });
		}

		if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_3))
		{
			if (!game_objects["Green0"])
			{
				for (unsigned int i{}; i < 3; i++)
				{
					ToastBox::Vec3 pos{ (float)(std::rand() % (int)max_pos.x + (int)min_pos.x), (float)(std::rand() % (int)max_pos.y + (int)min_pos.y),0.0f };
					ToastBox::Vec3 rot{ (float)(std::rand() % (int)max_rot.x + (int)min_rot.x), (float)(std::rand() % (int)max_rot.y + (int)min_rot.y),0.0f };

					game_objects["Green" + std::to_string(i)] = Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab("GREEN"), "Green" + std::to_string(i));
					transform_cache["Green" + std::to_string(i)] = dynamic_cast<Transform*>(game_objects["Green" + std::to_string(i)]->Get_Component(TRANSFORM));

					transform_cache["Green" + std::to_string(i)]->Set_Position(pos);
					transform_cache["Green" + std::to_string(i)]->Set_Rotation(rot);
				}
			}
		}

		if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_4))
		{
			if (game_objects["Green0"])
			{
				for (unsigned int i{}; i < 3; i++)
				{
					game_objects["Green" + std::to_string(i)]->Disable();
					game_objects.erase("Green" + std::to_string(i));
				}
			}
		}

		if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_7))
		{
			SageAudio::Play_Sound("sfx_sword", NO_LOOP);
		}

		if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_8))
		{
			SageAudio::Play_Sound("sfx_spear", NO_LOOP);
		}

		if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_9))
		{
			SageAudio::Play_Sound("sfx_crossbow", NO_LOOP);
		}


		plrphy->Get_Velocity() *= 0.99f;

	}

	/*!*****************************************************************************
	  \brief
		Updates the game scene
	*******************************************************************************/
	void Update()
	{
		// AABB checks here
		std::unordered_map<std::string, std::unique_ptr<GameObject>>& objects = Game_Objects::Get_Game_Objects();

		std::vector<BoxCollider2D*> colliders{};
		for (auto& obj : objects)
		{
			if (!obj.second)
				continue;
			BoxCollider2D* collider = dynamic_cast<BoxCollider2D*>(obj.second->Get_Component(BOXCOLLIDER2D));
			if (collider)
			{
				collider->Register_Collision_Callback([collider](GameObject* _obj) {
					if (!_obj) {
						return;
					}
					Physics* phy = dynamic_cast<Physics*>(collider->Get_Parent()->Get_Component(PHYSICS));
					if (phy) {
						phy->Get_Velocity() = { 0,0 };
						std::cout << _obj->Get_ID() << "collided with " << collider->Get_Parent()->Get_ID() << '\n';
					}
				});
				colliders.push_back(collider);
			}
		}


		// AABB Here
		for (auto& collider : colliders)
		{
			Physics* phys = dynamic_cast<Physics*>(collider->Get_Parent()->Get_Component(PHYSICS));
			if (!phys)
				continue;
			for (auto& other : colliders)
			{
				if (collider == other)
				{
					continue;
				}
				float time = 0.f;
				//
					bool collide_cond = collider->Collision_Intersection_Rect_Rect(collider->Get_AABB(), phys->Get_Velocity(), other->Get_AABB(), {}, time);
					if (collide_cond)
					{
						// Retrieve necessary components
						GameObject* parent = collider->Get_Parent();
						Transform* transform = parent->Get_Component<Transform>();
						ToastBox::Vec3 prevPos = transform->Get_Prev_Position();

						// Get the current velocity
						ToastBox::Vec2 curr_vel = phys->Get_Velocity();
						ToastBox::Vec3 pos = { transform->Get_Position()[0], transform->Get_Position()[1], transform->Get_Position()[2] };

						ToastBox::Vec3 dir = pos - prevPos; // Direction of movement

						// Get reference to the velocity for easier access
						ToastBox::Vec2& vel = phys->Get_Velocity();


						auto& aabb1 = collider->Get_AABB();
						auto& aabb2 = other->Get_AABB();

						float overlapX = std::min(aabb1.max.x, aabb2.max.x) - std::max(aabb1.min.x, aabb2.min.x);
						float overlapY = std::min(aabb1.max.y, aabb2.max.y) - std::max(aabb1.min.y, aabb2.min.y);

						bool horizontal = overlapX < overlapY;

						if (horizontal) {
							if (dir.x > 0 && !(vel.x < 0))
							{
								std::cout << "Enter left;\n";
								vel.x = 0;

							}
							else if (dir.x < 0 && !(vel.x > 0))
							{
								std::cout << "Enter right;\n";
								vel.x = 0;
							}

							transform->Set_Position({ curr_vel.x * time + prevPos.x,pos.y, 1.f });
						}
						else
						{
							if (dir.y > 0 && !(vel.y < 0))
							{
								std::cout << "Enter bottom;\n";
								vel.y = 0; // Stop upward movement
							}
							else if (dir.y < 0 && !(vel.y > 0))
							{
								std::cout << "Enter top;\n";
								vel.y = 0;
							}

							transform->Set_Position({ pos.x, curr_vel.y * time + prevPos.y, 1.f });
						}


						
					}

			}
		}
		//rotates greens
		if (game_objects["Green0"])
		{
			for (unsigned int i{}; i < 3; ++i)
			{
				transform_cache["Green" + std::to_string(i)]->Rotate({ (float)SageHelper::delta_time * 5.0f,0.f,0.0f });
			}
		}

		//rotates the 2.5k objects
		for (unsigned int i{}; i < game_objects_to_create; ++i)
		{
			transform_cache[std::to_string(i)]->Rotate({ (float)SageHelper::delta_time * 5.0f,0.f,0.0f });
		}

		camera.update();




	}

	/*!*****************************************************************************
	  \brief
		Draws the game scene
	*******************************************************************************/
	void Draw()
	{
	}

	/*!*****************************************************************************
	  \brief
		Frees the game scene
	*******************************************************************************/
	void Free()
	{
	}

	/*!*****************************************************************************
	  \brief
		Unloads the game scene
	*******************************************************************************/
	void Unload()
	{
	}
}
