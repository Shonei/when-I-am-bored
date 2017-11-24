#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include "SolidCubeWidget.h"


// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8 
};

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0 
};


// constructor
SolidCubeWidget::SolidCubeWidget(QWidget *parent)
	: QGLWidget(parent)
	{ // constructor
       

	} // constructor

// called when OpenGL context is set up
void SolidCubeWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);
	angle = 0;
  this->sphere();
  this->super_sphere();
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(100);

 
	} // initializeGL()


// called every time the widget is resized
void SolidCubeWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
   
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = {0., 0., 100., 1.};	
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);


                                                                                                                                                               
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

	} // resizeGL()

void SolidCubeWidget::house() {
  GLfloat normals[][3] = { {0.333, 1., 0.333 }, {0.333, 1., 0.333}, {0.333, 1., 0.333}, {0.3333, 0.3333, 0.333}};
  materialStruct *p_front = &brassMaterials;
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,   p_front->shininess);

  // back wall
  glNormal3fv(normals[4]); 
  glBegin(GL_POLYGON);
    glVertex3f( -20.0,  0.0,  15.0);
    glVertex3f( -20.0,  0.0, -15.0);
    glVertex3f( -20.0, 15.0, -15.0);
    glVertex3f( -20.0, 15.0,  15.0);
  glEnd();

  // front wall right
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -10.0, 15.0, -10.0);
    glVertex3f( -10.0, 15.0, -15.0);
    glVertex3f( -10.0,  0.0, -15.0);
    glVertex3f( -10.0,  0.0, -10.0);
  glEnd();

  // front wall top
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -10.0, 15.0, -10.0);
    glVertex3f( -10.0, 15.0,  -5.0);
    glVertex3f( -10.0, 12.0,  -5.0);
    glVertex3f( -10.0, 12.0, -10.0);
  glEnd();

  // front wall botom
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -10.0,  5.0, -10.0);
    glVertex3f( -10.0,  5.0,  -5.0);
    glVertex3f( -10.0,  0.0,  -5.0);
    glVertex3f( -10.0,  0.0, -10.0);
  glEnd();

  // front wall left
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -10.0, 15.0,  -5.0);
    glVertex3f( -10.0, 15.0,  15.0);
    glVertex3f( -10.0,  0.0,  15.0);
    glVertex3f( -10.0,  0.0,  -5.0);
  glEnd();

  // left wall
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -20.0, 15.0, -15.0);
    glVertex3f( -20.0,  0.0, -15.0);
    glVertex3f( -10.0,  0.0, -15.0);
    glVertex3f( -10.0, 15.0, -15.0);
  glEnd();

  // right wall
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -20.0, 15.0,  15.0);
    glVertex3f( -20.0,  0.0,  15.0);
    glVertex3f( -10.0,  0.0,  15.0);
    glVertex3f( -10.0, 15.0,  15.0);
  glEnd();

  // right under roof
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -20.0, 15.0, -15.0);
    glVertex3f( -10.0, 15.0, -15.0);
    glVertex3f( -15.0, 22.0, -15.0);
  glEnd();

  // left under roof
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -20.0, 15.0,  15.0);
    glVertex3f( -10.0, 15.0,  15.0);
    glVertex3f( -15.0, 22.0,  15.0);
  glEnd();

  glPushMatrix();
  GLfloat brown[4] = {0.627, 0.322, 0.176, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
  glMaterialfv(GL_FRONT, GL_SPECULAR, brown);

  // door
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -9.99,  0.0,  5.0);
    glVertex3f( -9.99,  0.0,  10.0);
    glVertex3f( -9.99,  7.0,  10.0);
    glVertex3f( -9.99,  7.0,  5.0);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  GLfloat brown_trans[4] = {0.627, 0.322, 0.176, 0.5};
  glMaterialfv(GL_FRONT, GL_AMBIENT, brown_trans);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, brown_trans);
  glMaterialfv(GL_FRONT, GL_SPECULAR, brown_trans);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // window
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -10.0,  5.0, -5.0);
    glVertex3f( -10.0,  5.0, -10.0);
    glVertex3f( -10.0, 12.0, -10.0);
    glVertex3f( -10.0, 12.0, -5.0);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  GLfloat red[4] = {0.698, 0.133, 0.133, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, red);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glMaterialfv(GL_FRONT, GL_SPECULAR, red);
  // front roof
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -15.0, 22.0, -15.5);
    glVertex3f( -15.0, 22.0,  15.5);
    glVertex3f(  -9.0, 14.0,  15.5);
    glVertex3f(  -9.0, 14.0, -15.5);
  glEnd();

  // back roof
  glNormal3fv(normals[1]); 
  glBegin(GL_POLYGON);
    glVertex3f( -15.0, 22.0, -15.5);
    glVertex3f( -15.0, 22.0,  15.5);
    glVertex3f( -21.0, 14.0,  15.5);
    glVertex3f( -21.0, 14.0, -15.5);
  glEnd();
    glPopMatrix();
}

void SolidCubeWidget::world_marker() {
  // glPushMatrix();

  GLfloat normal[][1] = {0.333, 1., 0.333 };
  materialStruct* p_front = &whiteShinyMaterials;
	
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  // glNormal3fv(normal[0]);
  // glBegin(GL_POLYGON);
  //   glVertex3f(  10.0,  0.0,   10.0);
  //   glVertex3f(  10.0,  0.0,  -10.0);
  //   glVertex3f( -10.0,  0.0,  -10.0);
  //   glVertex3f( -10.0,  0.0,   10.0);
  // glEnd();  

  glPushMatrix();
  glTranslatef(15.0,0.0,0.0);
  glutSolidTeapot(2.0);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-15.0,7.0,-7.0);
  glutSolidTeapot(2.0);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.0,15.0);
  glutSolidTeapot(2.0);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.0,-15.0);
  glutSolidTeapot(2.0);
  // glutSolidTorus(3.0, 5.0, 4,4);
  glPopMatrix();

  // glPopMatrix();
}
	
void SolidCubeWidget::sphere() {
  double loop = M_PI / 36;
  // std::cout << loop << std::endl;
  for (double theta = 0; theta <= M_PI; theta += loop) {
    QVector<point> temp;
    for (double phi = 0; phi <= 2*M_PI; phi += loop*2) {
    // std::cout << theta << " " << phi <<std::endl;
      point t;
      t.x = qSin(theta)*qCos(phi)*10;
      t.y = qSin(theta)*qSin(phi)*10;
      t.z = qCos(theta)*10;
      // glVertex3f( x, y, z);
      temp.prepend(t);
    }
    globe.prepend(temp);
    // glEnd();
  }
}

void SolidCubeWidget::super_sphere() {
  double loop = M_PI / 36;
  // std::cout << loop << std::endl;
  for (double theta = -M_PI/2; theta <= M_PI/2; theta += loop) {
    QVector<point> temp;
    double r1 = super_formula(theta);
    for (double phi = -M_PI; phi <= M_PI; phi += loop*2) {
      point t;
      double r2 = super_formula(phi);
    std::cout << r2 <<std::endl;
      t.x = r1 * qCos(theta) * r2 * qCos(phi) * 10;
      t.y = r1 * qCos(theta) * r2 * qSin(phi) * 10;
      t.z = r1 * qSin(theta) * 10;
      temp.prepend(t);
    }
    super_shape.prepend(temp);
  }
}

double  SolidCubeWidget::super_formula(double angle) {
  double a = 1.0;
  double b = 1.0;
  double m = 0.3;
  double n1 = 0.2;
  double n2 = 1.7;
  double n3 = 1.7;

  double part1 = qFabs(qCos(( m * angle ) / 4 ) / a );
  part1 = qPow(part1, n2);

  double part2 = qFabs(qCos(( m * angle ) / 4 ) / b );
  part2 = qPow(part2, n3);

  return qPow((part1 + part2), -1/n1);
}

void SolidCubeWidget::drawShape(QVector< QVector<point> > vec) {
  GLfloat normals[][3] = { {0.333, 1., 0.333 }, {0.333, 1., 0.333}, {0.333, 1., 0.333}, {0.3333, 0.3333, 0.333}};
  materialStruct *p_front = &brassMaterials;
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,   p_front->shininess);

  glNormal3fv(normals[4]); 
  // std::cout << vec[0][37].x <<std::endl;
  for (int i = 0; i < vec.size()-1; ++i) {
    // glBegin(GL_POINTS);
    // glBegin(GL_LINE_LOOP);
    glBegin(GL_TRIANGLE_STRIP);
    for (int j = 0; j < vec[i].size(); ++j) {
      point t1 = vec[i][j];
      glVertex3f( t1.x, t1.y, t1.z);

      point t2 = vec[i+1][j];
      glVertex3f( t2.x, t2.y, t2.z);
    }
    glEnd();
  }
}

// called every time the widget needs painting
void SolidCubeWidget::paintGL() { // paintGL()
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);                                                                                             
  glShadeModel(GL_SMOOTH);
	glPushMatrix();
	glLoadIdentity();
    GLfloat light_pos[] = {0.0, 0.0, 100.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);
	glPopMatrix();

  angle += 3;
  if(angle > 360){
    angle -= 360;
  }
  glRotatef(angle, 0.0, 1.0, 0.0);

	// this->world_marker();
 //  this->house();
  // this->drawShape(globe);
  this->drawShape(super_shape);

  glScalef(0.5, 0.5, 0.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  gluLookAt(10.0,4.0,0.0, 0.0,0.0,0.0, 0.0,1.0,0.0);     
	
	// flush to screen
	glFlush();	

	} // paintGL()
