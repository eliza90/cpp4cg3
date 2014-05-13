#pragma once
#include "../stdafx.h"
#include <exception>
#include <memory>

namespace view{

	class Window{
	public:
		Window(size_t width, size_t height, const std::string& name);
		~Window(){}
		unsigned int width() const{ return _width; }
		unsigned int height() const{ return _height; }
		// request window redisplay
		void invalidate();
	protected:
		virtual bool display();
		virtual void reshape(int width, int height);
		virtual void keyboard(unsigned char glut_key, int mouse_x, int mouse_y);
	private:
		// make sure this Window is the current GLUT Window
		void ensureCurrent() const;
		static void glutDisplay();
		static void glutReshape(int width, int height);
		static void glutKeyboard(unsigned char glut_key, int mouse_x, int mouse_y);
		std::string _name;
		size_t _width;
		size_t _height;
		int _glut_win_id;		
	}; // Window
} // view::






