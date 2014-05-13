#include "stdafx.h"
#include "cpp4cg3Functions.h"
#include "controller/glut_engine.hpp"

//void test1(int argc, char* argv[]){
//	//Initialise GLUT with command-line parameters. 
//	glutInit(&argc, argv);
//
//	//Set Display Mode
//	glutInitDisplayMode(GLUT_DOUBLE |  // DoubleBuffer verwenden
//						   GLUT_RGB |     //Tiefenpuffer
//						   GLUT_DEPTH);    // RGB-Farben verwenden
//
//	// Note: glutSetOption is only available with freeglut
//	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
//		GLUT_ACTION_GLUTMAINLOOP_RETURNS);
//
//	//Set the window size
//	glutInitWindowSize(640, 480);
//
//	//Create the window
//	glutCreateWindow("cpp4cg3-Window");
//
//	//Call "display" function
//	glutDisplayFunc(display1);
//
//	glutReshapeFunc(reshape1);
//	glutKeyboardFunc(keyboardFunc1);
//
//	//Enter the GLUT event loop
//	glutMainLoop();
//}

int main(int argc, char* argv[]) {	
	////test1(argc, argv);
	std::shared_ptr<controller::Engine> game_engine(new controller::GlutEngine);
	game_engine->init(argc, argv);
	//game_engine->init(argc, argv);	
	game_engine->run();		
	return 0;
}

//void display1(void){
//	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glutSwapBuffers();
//}
//
//void reshape1(int w, int h){
//	glViewport(0,0,w,h);	
//}
//
//void keyboardFunc1(unsigned char key, int xmouse, int ymouse){
//	switch (key){
//	case 'q':
//		glutDestroyWindow(glutGetWindow());
//		break;
//	}
//}