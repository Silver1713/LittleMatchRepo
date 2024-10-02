#ifndef Sage_Window_HPP
#define Sage_Window_HPP
#include <memory>
#include <string>




// Abstraction through PIMPL

class SageWindow
{
	static SageWindow* Active_Window;
public:
	SageWindow(int width, int height, const char* title);
	~SageWindow();

	void Update();
	void Draw();
	void Exit();

	bool Should_Window_Close() const;
	SageWindow const& Get_Window() const;
private:
	class SageWindowImpl;
	std::unique_ptr<SageWindowImpl> window_internal_impl;

	//Window positions
	int posx, posy;
	// Window dimensions
	int width,height;

	// Window title
	std::string title;

	// Window properties
	bool should_close; // set to true when window should close
	bool is_fullscreen; // set to true when window is fullscreen
	bool is_resizable; // set to true when window is resizable
	bool enable_maximize; // set to true when window is maximizable


	bool is_active; // set to true when window is active

public:
	void Activate_Context();
	void Deactivate_Context();
	void Set_Dims(int width, int height);
	void Set_Title(const char* title);
	void Toggle_Fullscreen();
	void Set_Resizable(bool resizable);
	void Set_Maximize(bool maximize);
	void Set_Pos_X(int pos_x);
	void Set_Pos_Y(int pos_y);

	void Set_Framebuffer_Callback();

	void Swap_Buffers();


	bool Get_Fullscreen() const;
	bool Get_Resizable() const;
	bool Get_Maximize() const;
	bool check_active() const;


	int Get_Pos_X() const;
	int Get_Pos_Y() const;
	int Get_Size_X() const;
	int Get_Size_Y() const;
	std::string Get_Title() const;


	static SageWindow* Get_Active_Window();


};


#endif