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
#include "KeyInputs.h"
#include "Game.hpp"
#include "Components/Physics.hpp"


#include <iostream>
#include <random>

//FOR TESTING PURPOSES
#include <cstdlib> // for srand()
#include <memory>
#include "Components/Physics.hpp"


namespace Game {
	//TESTS
	static unsigned int const game_objects_to_create{ 2500 };
	static float const min_pos[3]{ -960.0f,-540.0f,0.0f }, max_pos[3]{ 1920.0f,1080.0f,0.0f };
	static float const min_rot[3]{ 0.0f,0.0f,0.0f }, max_rot[3]{ 360.0f,360.0f,0.0f };
	static float const min_scale[3]{ 1.0f,1.0f,0.0f }, max_scale[3]{ 10.0f,10.0f,0.0f };
	static float const min_col[3]{ 0.0f,0.0f,0.0f }, max_col[3]{ 100.0f,100.0f,100.0f };

	static std::unordered_map<std::string, GameObject*> game_objects;
	static std::unordered_map<std::string, Transform*> transform_cache;
	static std::unordered_map<std::string, BoxCollider2D*> collider_cache;

	static SageCamera camera;
	static SageViewport vp;

	/*!*****************************************************************************
	  \brief
		Loads data the scene may need
	*******************************************************************************/
	void Load()
	{
		game_objects.clear();
		transform_cache.clear();
		GameObject* obj = Game_Objects::Get_Game_Object("Player");
		//caches the player's transforms
		transform_cache["Player"] = dynamic_cast<Transform*>(Game_Objects::Get_Game_Object("Player")->Get_Component(TRANSFORM));
		collider_cache["Player"] = dynamic_cast<BoxCollider2D*>(Game_Objects::Get_Game_Object("Player")->Get_Component(BOXCOLLIDER2D));
		collider_cache["Wall"] = dynamic_cast<BoxCollider2D*>(Game_Objects::Get_Game_Object("Wall")->Get_Component(BOXCOLLIDER2D));
		//Creates 2.5k instantiated "WHITE" prefab to test
		for (unsigned int i{}; i < game_objects_to_create; ++i)
		{
			game_objects[std::to_string(i)] = Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab("WHITE"), "White_" + std::to_string(i));
			transform_cache[std::to_string(i)] = dynamic_cast<Transform*>(game_objects[std::to_string(i)]->Get_Component(TRANSFORM));

			//randomize properties
			float pos[3]{ (float)(std::rand() % (int)max_pos[0] + (int)min_pos[0]), (float)(std::rand() % (int)max_pos[1] + (int)min_pos[1]),0.0f };
			float rot[3]{ (float)(std::rand() % (int)max_rot[0] + (int)min_rot[0]), (float)(std::rand() % (int)max_rot[1] + (int)min_rot[1]),0.0f };
			float scale[3]{ (float)(std::rand() % (int)max_scale[0] + (int)min_scale[0]), (float)(std::rand() % (int)max_scale[1] + (int)min_scale[1]),0.0f };
			float col[3]{ (float)(std::rand() % (int)max_col[0] + (int)min_col[0]) / 100.0f, (float)(std::rand() % (int)max_col[1] + (int)min_col[1]) / 100.0f,(float)(std::rand() % (int)max_col[2] + (int)min_col[2])/100.0f };

			transform_cache[std::to_string(i)]->Set_Positions({ pos[0],pos[1],pos[2]});
			transform_cache[std::to_string(i)]->Set_Rotations({ rot[0],rot[1],rot[2]});
			transform_cache[std::to_string(i)]->Set_Scale({ scale[0],scale[1],scale[2]});

			Sprite2D* s = dynamic_cast<Sprite2D*>(game_objects[std::to_string(i)]->Get_Component(SPRITE2D));
			s->Set_Colour({col[0],col[1],col[2]});

			game_objects[std::to_string(i)]->Disable();	
		}
		//Game_Objects::Get_Game_Object("Player")->Add_Component(std::make_unique<BoxCollider2D>());
		
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

		SageRenderer::SetCurrentView(&camera);
		SageRenderer::SetCurrentView(vp);


		vp.setViewport();


		

		Physics* plrphy = dynamic_cast<Physics*>(Game_Objects::Get_Game_Object("Player")->Get_Component(PHYSICS));
		plrphy->set_static(true);
		
	}

	/*!*****************************************************************************
	  \brief
		Handles input checks in the scene
	*******************************************************************************/
	void Input()
	{
		//tests
		if (SAGEInputHandler::Get_Key(SAGE_KEY_W))
		{
			transform_cache["Player"]->Translate({ 0.f,(float)SageHelper::delta_time * 100.0f,0.f });
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_A))
		{
			transform_cache["Player"]->Translate({ (float)SageHelper::delta_time * (-100.0f),0.f,0.f });
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_S))
		{
			transform_cache["Player"]->Translate({ 0.f,(float)SageHelper::delta_time * (-100.0f),0.f });
		}
		if (SAGEInputHandler::Get_Key(SAGE_KEY_D))
		{
			transform_cache["Player"]->Translate({ (float)SageHelper::delta_time * 100.0f,0.f,0.f });
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
			SageRenderer::camera->MoveCamera({ 0.f,1.f }, 100.f);
		} else if (SAGEInputHandler::Get_Key(SAGE_KEY_K))
		{
			SageRenderer::camera->MoveCamera({ 0.f,-1.f }, 100.f);
		}
		else if (SAGEInputHandler::Get_Key(SAGE_KEY_J))
		{
			SageRenderer::camera->MoveCamera({ -1.f,0.f }, 100.f);
		}
		else if (SAGEInputHandler::Get_Key(SAGE_KEY_L))
		{
			SageRenderer::camera->MoveCamera({ 1.f,0.f }, 100.f);
		} else if (SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_G))
		{
			for (auto& collider : collider_cache)
			{
				collider.second->Set_Debug(!collider.second->Get_Debug());
			}
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
			
			//GameObject* random;
			double x, y;
			SAGEInputHandler::Get_Mouse_Position(x, y);
			ToastBox::Vec2 mouse_pos{static_cast<float>(x), static_cast<float>(y)};

			ToastBox::Vec2 world = SageRenderer::camera->Screen_To_World({960.f, 540.f});;

			std::cout << "Mouse Pos: " << world.x << " " << world.y << std::endl;
			
			
			GameObject* random = Game_Objects::Instantiate(Prefabs::Get_Prefab("White"), "White_1");
			transform_cache["White_1"] = dynamic_cast<Transform*>(random->Get_Component(TRANSFORM));

			float min_scale[3] = { 10.0f,10.0f,0.0f }, max_scale[3] = { 100.0f,100.0f,0.0f };


			float pos[3]{ world.x,world.y,0.f };
			float rot[3]{ (float)(std::rand() % (int)max_rot[0] + (int)min_rot[0]), (float)(std::rand() % (int)max_rot[1] + (int)min_rot[1]),0.0f };
			float scale[3]{ (float)(std::rand() % (int)max_scale[0] + (int)min_scale[0]), (float)(std::rand() % (int)max_scale[1] + (int)min_scale[1]),0.0f };
			float col[3]{ (float)(std::rand() % (int)max_col[0] + (int)min_col[0]) / 100.0f, (float)(std::rand() % (int)max_col[1] + (int)min_col[1]) / 100.0f,(float)(std::rand() % (int)max_col[2] + (int)min_col[2]) / 100.0f };

			transform_cache["White_1"]->Set_Positions({ pos[0],pos[1],pos[2] });
			transform_cache["White_1"]->Set_Rotations({ rot[0],rot[1],rot[2] });
			transform_cache["White_1"]->Set_Scale({ scale[0],scale[1],scale[2] });
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
					float pos[3]{ (float)(std::rand() % (int)max_pos[0] + (int)min_pos[0]), (float)(std::rand() % (int)max_pos[1] + (int)min_pos[1]),0.0f };
					float rot[3]{ (float)(std::rand() % (int)max_rot[0] + (int)min_rot[0]), (float)(std::rand() % (int)max_rot[1] + (int)min_rot[1]),0.0f };

					game_objects["Green" + std::to_string(i)] = Game_Objects::Instantiate(Assets::Prefabs::Get_Prefab("GREEN"), "Green" + std::to_string(i));
					transform_cache["Green" + std::to_string(i)] = dynamic_cast<Transform*>(game_objects["Green" + std::to_string(i)]->Get_Component(TRANSFORM));

					transform_cache["Green" + std::to_string(i)]->Set_Positions({ pos[0],pos[1],pos[2] });
					transform_cache["Green" + std::to_string(i)]->Set_Rotations({ rot[0],rot[1],rot[2] });
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
	}

	/*!*****************************************************************************
	  \brief
		Updates the game scene
	*******************************************************************************/
	void Update()
	{
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


		// AABB checks here
		std::unordered_map<std::string,std::unique_ptr<GameObject>>& objects = Game_Objects::Get_Game_Objects();

		std::vector<BoxCollider2D*> colliders{};
		
		for (auto& obj : objects)
		{
			if (!obj.second)
				continue;
			BoxCollider2D* collider = dynamic_cast<BoxCollider2D*>(obj.second->Get_Component(BOXCOLLIDER2D));
			if (collider)
			{
				collider->Register_Collision_Callback([collider](GameObject* _obj) {
					std::cout << collider->Get_Parent()->Get_ID() << " Collided with " << _obj->Get_ID() << std::endl;
				});
				colliders.push_back(collider);
			}
		}


		// AABB Here
		for (auto& collider : colliders)
		{
			for (auto& other : colliders)
			{
				if (collider == other)
				{
					continue;
				}
				bool collide_cond = collider->CheckSweptCollision(collider->GetAABB(), *other);
				if (collide_cond)
				{
					collider->onCollide(other);
					GameObject* parent = collider->Get_Parent();
					if (parent)
					{
						Physics* phy = dynamic_cast<Physics*>(parent->Get_Component(PHYSICS));
						if (phy)
						{
							collider->onCollide(other);
						}
					}
				}
			}
		}
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
