#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include "QTimer"
#include "QtMath"
#include "iostream"
#include <QVector>
#include <QImage>
#include <QColor>


typedef struct point {
  float x;
  float y;
  float z;
  float r;
  float g;
  float b;
} point;

class SolidCubeWidget: public QGLWidget { 
	Q_OBJECT
	public:
		SolidCubeWidget(QWidget *parent);
		void change_super(float, float, float, float);

	protected:
		int angle;
		int globe_angle;
		int super_angle;
		float planet1_angle;
		float planet2_angle;
		float planet3_angle;
		float planet1_y;
		float planet1_y_goal;
		float planet2_y;
		float planet2_y_goal;
		float planet2_x;
		float planet2_x_goal;
		float planet3_y;
		float planet3_y_goal;
		QImage *earth;
		GLubyte earth_tex[2048][1024][3];
		void initializeGL();
		void resizeGL(int w, int h);
		void paintGL();
		double m;
		double n1;
		double n2;
		double n3;	

	private:
		QVector< QVector<point> > globe;
		QVector< QVector<point> > super_shape;
		void house();
		void sphere(float);
		double super_formula(float);
		void drawShape(QVector< QVector<point> >);
		void polygon(int, int, int, int);
		void super_sphere(float radios = 8.0);
		void system();
		void gen_texture();

	public slots:
		void angleChange(int);
};
	
#endif
