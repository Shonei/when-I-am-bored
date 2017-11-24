#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include "QTimer"
#include "QtMath"
#include "iostream"
#include <QVector>


typedef struct point {
  float x;
  float y;
  float z;
} point;

class SolidCubeWidget: public QGLWidget
	{ // 
	public:
	SolidCubeWidget(QWidget *parent);

		
	protected:
	int angle;
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:
	QVector< QVector<point> > globe;
	QVector< QVector<point> > super_shape;
	void world_marker();
	void house();
	void sphere();
	void super_sphere();
	double super_formula(double);
	void drawShape(QVector< QVector<point> >);
	void polygon(int, int, int, int);

	}; // class GLPolygonWidget
	
#endif
