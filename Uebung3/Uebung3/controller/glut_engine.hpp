#pragma once
#include "stdafx.h"
#include "engine.hpp"
#include "../view/window.hpp"
#include "../view/demoWindow.hpp"
#include <exception>
#include <memory>

namespace controller {
	
	class GlutEngine : public Engine{
		
	public:
		GlutEngine() : Engine(){}

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
			std::shared_ptr< view::Window > window;
			std::shared_ptr< view::Window > window2;
			try{
				window = std::make_shared<view::Window>(500, 500, "cpp4cg3-window");
				window2 = std::make_shared<view::DemoWindow>(500, 500, "cpp4cg3-window2");
			}
			catch (std::logic_error){
				std::cerr << "Caught: logic error in run()" << "\n";
			}
			std::cout << "GlutEngine::run checkpoint" << "\n";
			glutMainLoop();
		}
	};// GlutEngine::
}// controller::



