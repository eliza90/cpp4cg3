#pragma once
#include "stdafx.h"
#include "window.hpp"
#include <exception>
#include <memory>

namespace view{

	class DemoWindow: public Window{
	public:
		DemoWindow(size_t width, size_t height, const std::string& name) : Window(width, height, name){}
		~DemoWindow(){}
	protected:
		virtual bool display();
	private:
		void rotateInterval();
		unsigned long long val = 0.0;
		float rquad = 0.0f; 
	};//DemoWindow


} // view::






