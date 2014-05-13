#include "stdafx.h"
#include "window.hpp"
#include <chrono>

using namespace view;

Window::Window(size_t width, size_t height, const std::string& name){
	_width = width;
	_height = height;
	_name = name;
	
	glutInitDisplayMode(GLUT_DOUBLE |  // DoubleBuffer verwenden
						GLUT_RGB |     //Tiefenpuffer
						GLUT_DEPTH);    // RGB-Farben verwendent
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//Set the window size
	glutInitWindowSize(_width, _height);
	//Create the window	
	_glut_win_id = glutCreateWindow(name.c_str());
	glutSetWindow(_glut_win_id);	
	glutSetWindowData(this);//Zeiger auf die Window - Instanz

	//Funktionszeiger 
	glutDisplayFunc(glutDisplay);
	glutReshapeFunc(glutReshape);
	glutKeyboardFunc(glutKeyboard);	
}

void Window::ensureCurrent() const{		
	printf("glutGetWindow(): %d, glut_win_id: %d\n", glutGetWindow(), this->_glut_win_id);
	if (this->_glut_win_id == 0 || glutGetWindow() != this->_glut_win_id){
		//std::cerr << "id error in window:ensureCurrent()\n";
	}	
}

void Window::glutDisplay(void){		
	Window *that = static_cast<Window*>(::glutGetWindowData());
	if (that != nullptr){
		that->ensureCurrent();
		that->display();
	}
	else{
		std::cerr << "nullptr glutGetWindowData in glutDisplay()\n";
	}
		
}

bool Window::display(){
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
	return true;
}

void Window::glutReshape(int width, int height){
	Window *that = static_cast<Window*>(::glutGetWindowData());
	if (that != nullptr){
		that->ensureCurrent();
		that->_width = width; 
		that->_height = height;
		that->reshape(width, height);
	}
	else{
		std::cerr << "nullptr glutGetWindowData in glutReshape()\n";
	}
}

void Window::reshape(int width, int height){
	glViewport(0, 0, width, height);
}

void Window::glutKeyboard(unsigned char glut_key, int mouse_x, int mouse_y){
	Window *that = static_cast<Window*>(::glutGetWindowData());
	if (that != nullptr){
		that->ensureCurrent();
		that->keyboard(glut_key, mouse_x, mouse_y);
	}
	else{
		std::cerr << "nullptr glutGetWindowData in glutKeyboard()\n";
	}
}

void Window::keyboard(unsigned char glut_key, int mouse_x, int mouse_y){
	switch (glut_key){
	case 'q':
		glutDestroyWindow(glutGetWindow());
		break;
	}
}

void Window::invalidate() {
	glutSwapBuffers();
	glutPostRedisplay();
}