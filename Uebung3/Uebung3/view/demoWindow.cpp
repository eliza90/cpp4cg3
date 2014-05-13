#include "stdafx.h"
#include "demoWindow.hpp"
#include <chrono>

using namespace view;

bool DemoWindow::display(){
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Projektionsmatrix einstellen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluPerspective(30.0, width()/height(), 2.0, 200.0);//angle, w/h ,near clipping, far clipping

	gluLookAt(0.0, -7.0, 0.0, /* hier stehe ich */
		0.0, 0.0, 0.0,  /* hier schaue ich hin */
		0.0, 0.0, 0.1);  /* dieser Vektor zeigt senkrecht nach oben */
	 

	//Zeit seit Programmstart
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	   //unsigned long long 
		auto tempVal = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	tempVal = tempVal - val;;
	if (tempVal > 1){
		std::cout << "difference:" << tempVal << "\n";
		rotateInterval();
	}	
	val =  std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
		
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

	invalidate();
		
	return true;
}

void DemoWindow::rotateInterval(){
	if (rquad >= 360){
		rquad = 0;
	}
	else{
		rquad = rquad + 0.72;
	}
}


