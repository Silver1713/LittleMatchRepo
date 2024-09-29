#include <Windows.h>
#include <gtest/gtest.h>
#include "KeyInputs.h"
void SimulateKeyPress00(int key, int action)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = action;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
}

TEST(InputTestPIMPL, KEY_RELEASE_A)
{
	SAGEInputHandler::update();
	bool result = SAGEInputHandler::Get_Key(SAGE_KEY_A);
	EXPECT_FALSE(result);
}

TEST(InputTestPIMPL , KEY_TAP_K)
{
	WORD key = 'K';

	SimulateKeyPress00(key, 0);
	SAGEInputHandler::update();
	
	bool result = SAGEInputHandler::Get_Key(SAGE_KEY_K);
	EXPECT_TRUE(result);
}

TEST(InputTestPIMPL, KEY_RELEASE_K)
{
	WORD key = 'K';

	SimulateKeyPress00(key, KEYEVENTF_KEYUP);
	SAGEInputHandler::update();
	bool res = SAGEInputHandler::Get_Key(SAGE_KEY_K);
	EXPECT_FALSE(res);

}



