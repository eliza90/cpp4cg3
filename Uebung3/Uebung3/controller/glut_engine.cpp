#include "stdafx.h"
#include "GL/freeglut.h"
#include "glut_engine.hpp"

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
	//glutSetWindowData(this);//Zeiger auf die zugehörige Window - Instanz
	////printf("Window id: %d, data: %p, this: %p\n", _glut_win_id, glutGetWindowData(), this);//p = pointeradress

	//Funktionszeiger Display
	void(*funcDisplay_ptr)(void);
	funcDisplay_ptr = &glutDisplay;
	glutDisplayFunc(glutDisplay);

	//Funktionszeiger Reshape
	void(*funcReshape_ptr)(int w, int h);
	funcReshape_ptr = &glutReshape;
	glutReshapeFunc(glutReshape);
	//Funktionszeiger Keyboard
	void(*funcKeyboard_ptr)(unsigned char key, int xmouse, int ymouse);
	funcKeyboard_ptr = &glutKeyboard;
	glutKeyboardFunc(glutKeyboard);
}

Window::~Window(){}

void Window::ensureCurrent() const{
	glutGetWindow();	
	glutSetWindowData((void *)this);
	Window *myWindow = static_cast<Window*>(glutGetWindowData());// cast from void* to Window*	
	printf("Window id: %d, data: %p, this: %p\n", myWindow->id(), glutGetWindowData(), myWindow);//p = pointeradress
	printf("Window id: %d, witdh: %d, heigth: %d\n", myWindow->id(), myWindow->width(), myWindow->height());

	/*if (myWindow->id() < 0){
		return false;
	}
	if (myWindow->id() != glutGetWindow()){
		return false;
	}*/
}

void Window::glutDisplay(void){		
	//glutGetWindow();//determine which window should be updated
	
	//ensureCurrent();
	//Window* myWindow = static_cast<Window *>(glutGetWindowData());
	//printf("Window id: %d, data: %p, this: %p\n", myWindow->id(), glutGetWindowData(), myWindow);//p = pointeradress
	//printf("Window id: %d, witdh: %d, heigth: %d\n", myWindow->id(), myWindow->width(), myWindow->height());
	/*if (myWindow->ensureCurrent()){
		myWindow->display();		
	}
	else{
		std::cerr << "wrong window in glutDisplay" << "\n";
	}*/
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

bool Window::display(){
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	return true;
}

void Window::glutReshape(int width, int height){
	/*Window *myWindow = static_cast<Window *>(glutGetWindowData());
	if (myWindow->ensureCurrent()){
		myWindow->_width = width;
		myWindow->_height = height;
		myWindow->reshape(width, height);
	}
	else{
		std::cerr << "wrong window in glutReshape"<< "\n";
	}	*/
	glViewport(0, 0, width, height);
}

void Window::reshape(int width, int height){
	glViewport(0, 0, width, height);
}

void Window::glutKeyboard(unsigned char glut_key, int mouse_x, int mouse_y){
	//Window *myWindow = static_cast<Window *>(glutGetWindowData());
	//if (myWindow->ensureCurrent()){
	//	myWindow->keyboard(glut_key, mouse_x, mouse_y);
	//}	
	//else{
	//	std::cerr << "wrong window in glutKeyboard" << "\n";
	//}
	switch (glut_key){
	case 'q':
		glutDestroyWindow(glutGetWindow());
		break;
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
	glutSetWindow(_glut_win_id);
	glutPostRedisplay();
}

bool DemoWindow::display(){
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Projektionsmatrix einstellen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 200.0);
		
	return true;
}


