#include "stdafx.h"
#include <thread>
#include "GL/freeglut.h"
#include "glut_engine.hpp"



using namespace view;

Window *instance = NULL;

auto val = 0.0;

float rquad= 0.0f;// Angle For The Quad  

void rotateInterval(){
	if (rquad==360){
		rquad=0;
	}
	else{
		rquad = rquad + 0.72;
	}
}

Window::Window(size_t width, size_t height, const std::string& name){
	_width = width;
	_height = height;
	_name = name;
	instance = this;

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
	//glutSetWindowData((void*)_glut_win_id);

	printf("Window id: %d, data: %p, this: %p\n", _glut_win_id, glutGetWindowData(), this);//p = pointeradress

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
	//glutGetWindow();	
	//printf("Window : %d\n", glutGetWindow());
	//instance = static_cast<Window*>(glutGetWindowData());// cast from void* to Window*	
	//printf("Window id: %d, data: %p, this: %p\n", instance->id(), glutGetWindowData(), instance);//p = pointeradress
	//printf("Window id: %d, witdh: %d, heigth: %d\n", instance->id(), instance->width(), instance->height());

	//int *id = static_cast<int*>(glutGetWindowData());
	//printf("Window id: %d, initialid: %d,\n",id, _glut_win_id);

}

void Window::glutDisplay(void){		
	//instance->ensureCurrent();
	//instance->display();		
	//std::cerr << "wrong window in glutDisplay" << "\n";

	/*glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();*/
		
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Projektionsmatrix einstellen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(30.0, 1.0, 2.0, 200.0);//angle, w/h ,near clipping, far clipping

	gluLookAt(0.0, -7.0, 0.0, /* hier stehe ich */
		0.0, 0.0, 0.0,  /* hier schaue ich hin */
		0.0, 0.0, 0.1);  /* dieser Vektor zeigt senkrecht nach oben */
	 

	//Zeit seit Programmstart
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    auto tempVal = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	tempVal = tempVal - val;;
	if (tempVal > 1){
		std::cout << "difference:" << tempVal << "\n";
		rotateInterval();
	}	
	val =  std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	//std::cout << "miliseconds since epoch:"	<< std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count()<< "us.\n";
		
	glRotatef(rquad, 0.0f, 0.0f, 1.0f);//(angle,x,y,z)

	glBegin(GL_LINES);                                  // Draw A Quad 
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();

	glutSwapBuffers();
	glutPostRedisplay();//später and display anpassen?!
}

bool Window::display(){
	glutSwapBuffers();
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


