#include "include.h"
void Desenha_planeta(char *planeta, GLuint textura[], float pos_y, float pos_x, float escala,float diametro,float raio)
{
  float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  float a = t*2;

  glPushMatrix();
  glRasterPos2f(0,-pos_y);
  glutBitmapString(GLUT_BITMAP_9_BY_15, planeta);
  glTranslated(0, -pos_y, 0);
  // Movimento de Translação
  glTranslatef((pos_x * cos(2.0 * 3.14 * a*raio / 100)),(pos_y +pos_y * sin(2.0 * 3.14 * a*raio/ 100)), 0);
  GLUquadric *obj = gluNewQuadric();
  gluQuadricTexture(obj,GL_TRUE);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textura);
  glScalef(escala,escala,escala);
  glRotated(a*20, 0, 0, 1);
  gluSphere(obj,diametro,25,25);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

}

void desenha_planetas_com_Satelites(char *planeta, GLuint textura1[], GLuint textura2[],float pos_y, float pos_x, float escala,float diametro1,float diametro2,float raio,float raio_lua)
{
  float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  float a = t*2;

  glPushMatrix();
  glRasterPos2f(0,-pos_y);
  glutBitmapString(GLUT_BITMAP_9_BY_15, planeta);
  glTranslated(0, -pos_y, 0);
  // Movimento de Translação
  glTranslatef((pos_x * cos(2.0 * 3.14 * a*raio / 100)),(pos_y +pos_y * sin(2.0 * 3.14 * a*raio/ 100)), 0);
  GLUquadric *obj = gluNewQuadric();
  gluQuadricTexture(obj,GL_TRUE);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textura1);
  glScalef(escala,escala,escala);
  glRotated(a*20, 0, 0, 1);
  gluSphere(obj,diametro1,25,25);

  //Satélite
  //Translacao da Lua
  glTranslatef(pos_x/10*(cos(2.0 * 3.14 * a*raio_lua / 100)),(pos_y/10*sin(2.0 * 3.14 * a*raio_lua / 100)), 0);

  glBindTexture(GL_TEXTURE_2D,textura2);
  glScalef(escala,escala,escala);
  glRotated(a*5, 1, 0, 1);
  gluSphere(obj,diametro2,50,50);
  glDisable(GL_TEXTURE_2D);

  glPopMatrix();

}
void Desenha_planetas_com_Satelites_e_Aneis(char *planeta, GLuint textura1[], GLuint textura2[],GLuint textura3[],float pos_y, float pos_x, float escala,float diametro1,float diametro2,float raio,float raio_lua)
{
  float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  float a = t*2;

  glPushMatrix();
  glRasterPos2f(0,-pos_y);
  glutBitmapString(GLUT_BITMAP_9_BY_15, planeta);
  glTranslated(0, -pos_y, 0);
  // Movimento de Translação
  glTranslatef((pos_x * cos(2.0 * 3.14 * a*raio / 100)),(pos_y +pos_y * sin(2.0 * 3.14 * a*raio/ 100)), 0);
  GLUquadric *obj = gluNewQuadric();
  gluQuadricTexture(obj,GL_TRUE);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textura1);
  glScalef(escala,escala,escala);
  glRotated(a*20, 0, 0, 1);
  gluSphere(obj,diametro1,25,25);
  glScalef(escala,escala,escala);
  //Desenha o anel
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textura3);
  desenhaAnel(pos_x/80,pos_y/80);

  //Satélite
  //Translacao da Lua
  glTranslatef(pos_x/20*(cos(2.0 * 3.14 * a*raio_lua / 100)),(pos_y/20*sin(2.0 * 3.14 * a*raio_lua / 100)), 0);
  glBindTexture(GL_TEXTURE_2D,textura2);
  glScalef(escala,escala,escala);
  glRotated(a*5, 1, 0, 1);
  gluSphere(obj,diametro2,50,50);
  glDisable(GL_TEXTURE_2D);

  glPopMatrix();

}

void desenhaAnel(float x, float y) {
  glPushMatrix();
	glBegin(GL_LINE_LOOP);
	int i;
	float rad;
	for(i=0; i<360; i++) {
		rad = i*3.14/180;
		glVertex2f(cos(rad)*x,sin(rad)*y);
	}
	glEnd();
  glPopMatrix();
}

void Desenha_Orbita(float pos_y,float pos_x)
{
  int i;
  glPushMatrix();
  glTranslated(0, -pos_y, 0);
  glBegin(GL_LINE_LOOP);
  for (i = 0; i < 100; i++) {  /*Desenha a linha da órbita, a variável i vai
    juntando cada linha em uma circunferencia*/
    glVertex2f( pos_x * cos(2.0 * 3.14 * i / 100),
    pos_y + pos_y * sin(2.0 * 3.14 * i / 100) );
  }
  glEnd();
  glPopMatrix();

}
