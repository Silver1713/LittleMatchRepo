#pragma once
/* Start Header ************************************************************************/
/*!
\file		KeyInputs.h
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contains the declaration of functions for the public interface for the input system.
			Also contain the definition of key and mouse supported by sage input system.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

/* Printable keys */
#define SAGE_KEY_SPACE              32
#define SAGE_KEY_APOSTROPHE         39  /* ' */
#define SAGE_KEY_COMMA              44  /* , */
#define SAGE_KEY_MINUS              45  /* - */
#define SAGE_KEY_PERIOD             46  /* . */
#define SAGE_KEY_SLASH              47  /* / */
#define SAGE_KEY_0                  48
#define SAGE_KEY_1                  49
#define SAGE_KEY_2                  50
#define SAGE_KEY_3                  51
#define SAGE_KEY_4                  52
#define SAGE_KEY_5                  53
#define SAGE_KEY_6                  54
#define SAGE_KEY_7                  55
#define SAGE_KEY_8                  56
#define SAGE_KEY_9                  57
#define SAGE_KEY_SEMICOLON          59  /* ; */
#define SAGE_KEY_EQUAL              61  /* = */
#define SAGE_KEY_A                  65
#define SAGE_KEY_B                  66
#define SAGE_KEY_C                  67
#define SAGE_KEY_D                  68
#define SAGE_KEY_E                  69
#define SAGE_KEY_F                  70
#define SAGE_KEY_G                  71
#define SAGE_KEY_H                  72
#define SAGE_KEY_I                  73
#define SAGE_KEY_J                  74
#define SAGE_KEY_K                  75
#define SAGE_KEY_L                  76
#define SAGE_KEY_M                  77
#define SAGE_KEY_N                  78
#define SAGE_KEY_O                  79
#define SAGE_KEY_P                  80
#define SAGE_KEY_Q                  81
#define SAGE_KEY_R                  82
#define SAGE_KEY_S                  83
#define SAGE_KEY_T                  84
#define SAGE_KEY_U                  85
#define SAGE_KEY_V                  86
#define SAGE_KEY_W                  87
#define SAGE_KEY_X                  88
#define SAGE_KEY_Y                  89
#define SAGE_KEY_Z                  90
#define SAGE_KEY_LEFT_BRACKET       91  /* [ */
#define SAGE_KEY_BACKSLASH          92  /* \ */
#define SAGE_KEY_RIGHT_BRACKET      93  /* ] */
#define SAGE_KEY_GRAVE_ACCENT       96  /* ` */
#define SAGE_KEY_WORLD_1            161 /* non-US #1 */
#define SAGE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define SAGE_KEY_ESCAPE             256
#define SAGE_KEY_ENTER              257
#define SAGE_KEY_TAB                258
#define SAGE_KEY_BACKSPACE          259
#define SAGE_KEY_INSERT             260
#define SAGE_KEY_DELETE             261
#define SAGE_KEY_RIGHT              262
#define SAGE_KEY_LEFT               263
#define SAGE_KEY_DOWN               264
#define SAGE_KEY_UP                 265
#define SAGE_KEY_PAGE_UP            266
#define SAGE_KEY_PAGE_DOWN          267
#define SAGE_KEY_HOME               268
#define SAGE_KEY_END                269
#define SAGE_KEY_CAPS_LOCK          280
#define SAGE_KEY_SCROLL_LOCK        281
#define SAGE_KEY_NUM_LOCK           282
#define SAGE_KEY_PRINT_SCREEN       283
#define SAGE_KEY_PAUSE              284
#define SAGE_KEY_F1                 290
#define SAGE_KEY_F2                 291
#define SAGE_KEY_F3                 292
#define SAGE_KEY_F4                 293
#define SAGE_KEY_F5                 294
#define SAGE_KEY_F6                 295
#define SAGE_KEY_F7                 296
#define SAGE_KEY_F8                 297
#define SAGE_KEY_F9                 298
#define SAGE_KEY_F10                299
#define SAGE_KEY_F11                300
#define SAGE_KEY_F12                301
#define SAGE_KEY_F13                302
#define SAGE_KEY_F14                303
#define SAGE_KEY_F15                304
#define SAGE_KEY_F16                305
#define SAGE_KEY_F17                306
#define SAGE_KEY_F18                307
#define SAGE_KEY_F19                308
#define SAGE_KEY_F20                309
#define SAGE_KEY_F21                310
#define SAGE_KEY_F22                311
#define SAGE_KEY_F23                312
#define SAGE_KEY_F24                313
#define SAGE_KEY_F25                314
#define SAGE_KEY_KP_0               320
#define SAGE_KEY_KP_1               321
#define SAGE_KEY_KP_2               322
#define SAGE_KEY_KP_3               323
#define SAGE_KEY_KP_4               324
#define SAGE_KEY_KP_5               325
#define SAGE_KEY_KP_6               326
#define SAGE_KEY_KP_7               327
#define SAGE_KEY_KP_8               328
#define SAGE_KEY_KP_9               329
#define SAGE_KEY_KP_DECIMAL         330
#define SAGE_KEY_KP_DIVIDE          331
#define SAGE_KEY_KP_MULTIPLY        332
#define SAGE_KEY_KP_SUBTRACT        333
#define SAGE_KEY_KP_ADD             334
#define SAGE_KEY_KP_ENTER           335
#define SAGE_KEY_KP_EQUAL           336
#define SAGE_KEY_LEFT_SHIFT         340
#define SAGE_KEY_LEFT_CONTROL       341
#define SAGE_KEY_LEFT_ALT           342
#define SAGE_KEY_LEFT_SUPER         343
#define SAGE_KEY_RIGHT_SHIFT        344
#define SAGE_KEY_RIGHT_CONTROL      345
#define SAGE_KEY_RIGHT_ALT          346
#define SAGE_KEY_RIGHT_SUPER        347
#define SAGE_KEY_MENU               348

#define SAGE_KEY_LAST               SAGE_KEY_MENU

#define SAGE_MOUSE_BUTTON_LEFT         0
#define SAGE_MOUSE_BUTTON_RIGHT         1
#define SAGE_MOUSE_BUTTON_MIDDLE         2
#include <memory>
class SageInputPIML;

class SAGEInputHandler
{
public:

	/*!*****************************************************************************
	\brief
		Function to access SageInput pointer to implementation to check if a specific
		key is pressed once

	\param _keycode
		The key that is pressed

	\return
		Return a boolean
	*******************************************************************************/
	static bool Get_Key_Pressed(int _keycode);

	/*!*****************************************************************************
	\brief
		Function to access SageInput pointer to implementation to check if a specific
		key is held down

	\param _keycode
		The key that is pressed

	\return
		Return a boolean
	*******************************************************************************/
	static bool Get_Key(int _keycode);

	/*!*****************************************************************************
	\brief
		Function to access SageInput pointer to implementation to check if the mouse
		input is clicked once

	\param _mouse
		The mouse that is pressed

	\return
		Return a boolean
	*******************************************************************************/
	static bool Get_Mouse_Clicked(int _mouse);

	/*!*****************************************************************************
	\brief
		Function to access SageInput pointer to implementation to check if the mouse
		input is held down

	\param _mouse
		The mouse that is pressed

	\return
		Return a boolean
	*******************************************************************************/
	static bool Get_Mouse(int _mouse);

	/*!*****************************************************************************
	\brief
		Function to get the mouse x position using SageInput pointer to implementation

	\param
		Return a double
	*******************************************************************************/
	static double Get_Mouse_X();

	/*!*****************************************************************************
	\brief
		Function to get the mouse y position using SageInput pointer to implementation

	\param
		Return a double
	*******************************************************************************/
	static double Get_Mouse_Y();

	/*!*****************************************************************************
	\brief
		Function to get the mouse coordinates using SageInput pointer to implementation

	\param _x
		The x coordinate of mouse

	\param _y
		The y coordinate of mouse
	*******************************************************************************/
	static void Get_Mouse_Position(double& _x, double& _y);

	/*!*****************************************************************************
	\brief
		Function to initialize the sage input system
	*******************************************************************************/
	static void init();

	/*!*****************************************************************************
	\brief
		Function to update the sage input system
	*******************************************************************************/
	static void update();

	/*!*****************************************************************************
	\brief
		Function to terminate the sage input system
	*******************************************************************************/
	static void terminate();


private:

	/*!*****************************************************************************
	\brief
		Function to delete the pointer to implementation for sage input

	\param _p
		A pointer to PIML implementation of the SageInput class
	*******************************************************************************/
	static void Custom_Sage_Input_PIMPL_Delete(void*& _p);

	static std::unique_ptr<void, decltype(&Custom_Sage_Input_PIMPL_Delete)> impl_pointer;
};

