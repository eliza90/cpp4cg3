#pragma once
#include "engine.hpp"
#include <exception>
#include <iostream>
#include <memory>

namespace view{
	class Window
	{
	public:
		Window(size_t width, size_t height, const std::string& name);
		~Window();
		unsigned int width() const{ return _width; }
		unsigned int height() const{ return _height; }
		const unsigned int id() const{ return _glut_win_id; }
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

	class DemoWindow: public Window
	{
	public:
		DemoWindow(size_t width, size_t height, const std::string& name) : Window(width, height, name){
		}
		bool display();
	};

} // view::

namespace controller {
	
	class GlutEngine : public Engine{
		
	public:
		GlutEngine() : Engine(){
		}

		virtual void init(int argc, char** argv){
			try{
				glutInit(&argc, argv);
			}
			catch (std::exception& e){//exception wird nie abgefangen
				std::cerr << "Caught: logic error in init()" << e.what() << "\n";
			}			

			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
			std::cout << "GlutEngine::init checkpoint" << "\n";
		}

		virtual void run(){
			try{
				std::shared_ptr< view::Window > window(new view::Window(500, 500, "cpp4cg3-window"));	
				std::shared_ptr< view::Window > window2(new view::Window(400, 300, "cpp4cg3-window2"));
			}
			catch(std::logic_error){
				std::cerr << "Caught: logic error in run()" << "\n";
			}		
			std::cout << "GlutEngine::run checkpoint" << "\n";
			glutMainLoop();
		}
	};// GlutEngine::
}// controller::



