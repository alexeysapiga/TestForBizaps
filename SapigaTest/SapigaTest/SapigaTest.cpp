#include <glut.h>
#include <tchar.h>
#include <windows.h>
#include <math.h>
#include "Game.h"
#include "Engine/Engine.h"
#include <algorithm>

void draw() {
    Core::instance()->draw();
    Core::instance()->update();
}

void OnIdle(int i) {
    glutPostRedisplay();
    glutTimerFunc(16, OnIdle, 0);
}

void onMouseClick(int button, int state, int x, int y) {
    TouchInput::instance()->processPress(button, state, x, y);
}

void OnMouseMove(int x, int y) {
    TouchInput::instance()->processMove(x, y);
}


int _tmain(int argc, char **argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    int width = ApplicationSettings::instance()->getInt("screen_width", 100);
    int height = ApplicationSettings::instance()->getInt("screen_height", 100);
    Core::instance()->setResolution(width, height);
    glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sapiga Test");

    Game game;

    glutMouseFunc(onMouseClick);
    glutMotionFunc(OnMouseMove);

	glutDisplayFunc(draw);
    OnIdle(0);
	glutMainLoop();

    delete Core::instance();
	return 0;
}

void showError(const string& message)
{
    MessageBoxA(NULL, message.c_str(), ("Error"), MB_OK | MB_SYSTEMMODAL);
}

