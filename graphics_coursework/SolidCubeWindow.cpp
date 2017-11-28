#include "SolidCubeWindow.h"

SolidCubeWindow::SolidCubeWindow(QWidget *parent) : QWidget(parent) { 
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	H_layout = new QHBoxLayout();

	cubeWidget = new SolidCubeWidget(this);
	windowLayout->addWidget(cubeWidget);

	nVerticesSlider = new QSlider(Qt::Horizontal);
	windowLayout->addWidget(nVerticesSlider);

	nVerticesSlider->setMinimum(0);
	nVerticesSlider->setMaximum(360);

	m = new QDoubleSpinBox();
	m->setSuffix("m");
	m->setMaximum(20.0);
	m->setMinimum(0.0);
	m->setSingleStep(0.5);
	m->setValue(12.0);
	H_layout->addWidget(m);

	n1 = new QDoubleSpinBox();
	n1->setSuffix("n1");
	n1->setMaximum(100.0);
	n1->setMinimum(0.0);
	n1->setSingleStep(1.0);
	n1->setValue(33.0);
	H_layout->addWidget(n1);

	n2 = new QDoubleSpinBox();
	n2->setSuffix("n2");
	n2->setMaximum(100.0);
	n2->setMinimum(-50.0);
	n2->setSingleStep(1.5);
	n2->setValue(-10.0);
	H_layout->addWidget(n2);

	n3 = new QDoubleSpinBox();
	n3->setSuffix("n3");
	n3->setMaximum(100.0);
	n3->setMinimum(-50.0);
	n3->setSingleStep(1.5);
	n3->setValue(1.35);
	H_layout->addWidget(n3);

	windowLayout->addLayout(H_layout);

	connect(nVerticesSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(angleChange(int)));
	connect(m, SIGNAL(valueChanged(double)), this, SLOT(updateSuper()));
	connect(n1, SIGNAL(valueChanged(double)), this, SLOT(updateSuper()));
	connect(n2, SIGNAL(valueChanged(double)), this, SLOT(updateSuper()));
	connect(n3, SIGNAL(valueChanged(double)), this, SLOT(updateSuper()));
} 

SolidCubeWindow::~SolidCubeWindow() { 
	delete nVerticesSlider;
	delete cubeWidget;
	delete windowLayout;
} 

void SolidCubeWindow::updateSuper() {
	cubeWidget->change_super(m->value(), n1->value(), n2->value(), n3->value());
}