#ifndef SISTEMA_H
#define SISTEMA_H
void Desenha_planeta(char *planeta, GLuint textura[], float pos_y, float pos_x, float escala,float diametro,float raio);
void Desenha_Orbita(float pos_y,float pos_x);
void desenha_planetas_com_Satelites(char *planeta, GLuint textura1[], GLuint textura2[],float pos_y, float pos_x, float escala,float diametro1,float diametro2,float raio,float raio_lua);
void Desenha_planetas_com_Satelites_e_Aneis(char *planeta, GLuint textura1[], GLuint textura2[],GLuint textura3[],float pos_y, float pos_x, float escala,float diametro1,float diametro2,float raio,float raio_lua);
void desenhaAnel(float x, float y);
#endif
