#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QSpinBox>
#include "Scene.h"
#include <QHBoxLayout>
#include "iostream"
#include <QCheckBox>

class SolidCubeWindow: public QWidget { 
	Q_OBJECT
	public:
		SolidCubeWindow(QWidget *parent);
		~SolidCubeWindow();
		QBoxLayout *windowLayout;
		QHBoxLayout *H_layout;
		Scene *cubeWidget;
		QSlider *nVerticesSlider;
		QDoubleSpinBox *m;
		QDoubleSpinBox *n1;
		QDoubleSpinBox *n2;
		QDoubleSpinBox *n3;
		QCheckBox *checkbox;
	private slots:
		void updateSuper();
}; 
	
#endif
