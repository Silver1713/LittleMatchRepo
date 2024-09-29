#ifndef Sage_Window_HPP
#define Sage_Window_HPP
#include <memory>
#include <string>


#endif

// Abstraction through PIMPL

class SageWindow
{
	static SageWindow* active_window;
public:
	SageWindow(int width, int height, const char* title);
	~SageWindow();

	void Update();
	void Draw();
	void Exit();

	bool should_window_close() const;
	SageWindow const& GetWindow() const;
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
	void set_dims(int width, int height);
	void set_title(const char* title);
	void toggle_fullscreen();
	void set_resizable(bool resizable);
	void set_maximize(bool maximize);
	void set_pos_x(int pos_x);
	void set_pos_y(int pos_y);

	void set_framebuffer_callback();

	void swap_buffers();


	bool get_fullscreen() const;
	bool get_resizable() const;
	bool get_maximize() const;
	bool check_active() const;


	int get_pos_x() const;
	int get_pos_y() const;
	int get_size_x() const;
	int get_size_y() const;
	std::string get_title() const;


	static SageWindow* Get_Active_Window();


};