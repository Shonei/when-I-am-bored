#include <QApplication>
#include <QVBoxLayout>
#include "SolidCubeWindow.h"
#include <GL/glu.h>
#include <GL/glut.h>

int main(int argc, char *argv[]) { 
	QApplication app(argc, argv);
	glutInit(&argc, argv);

   SolidCubeWindow *window = new SolidCubeWindow(NULL);

	window->resize(612, 612);

	window->show();

	app.exec();

	delete window;
	
	return 0; 
	} 
