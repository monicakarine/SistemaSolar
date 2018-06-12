#include "include.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define MUS_PATH "Life.mp3"

// Our music file
Mix_Music *music = NULL;

#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0

GLuint texture[6];
int width = 10;
int height = 10;
int length = 10;

int x = 0;
int y = 0;
int z = 0;

static float p = 1.0;

GLfloat angulo, fAspect;
GLfloat rotX, rotY, rotZ, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot,ativo = 1,orbita = 1;
GLMmodel* asteroide;
GLuint asteroideList;

void Desenha(void);
void mostraOrbitas();
void Sistema_Solar_com_orbitas();

//carregando os obj
void inicializaObj(){

  asteroide= glmReadOBJ("./obj/asteroid.obj");
  asteroideList = glmList(asteroide, GLM_SMOOTH);
}

void Inicializa (void)
{
  if (SDL_Init(SDL_INIT_AUDIO) < 0)
  return -1;

  //Initialize SDL_mixer
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
  return -1;

  // Load our music
  music = Mix_LoadMUS(MUS_PATH);
  if (music == NULL)
  return -1;

  if ( Mix_PlayMusic( music, -1) == -1 )
  return -1;
  // Inicializa a variável que especifica o ângulo da projeção
  // perspectiva
  angulo=10;
  // Inicializa as variáveis usadas para alterar a posição do
  // observador virtual
  rotX = 0;
  rotY = 0;
  rotZ = 0;
  obsX = obsY = 0;
  obsZ = 150;

  loadTexture(); //Inicializa as texturas

  //Inicializa obj
  inicializaObj();

  // Não mostrar faces do lado de dentro
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}
void mostraOrbitas()
{
  /*        MERCÚRIO        */ // Diametro: 4.879,4 km
  Desenha_Orbita(7,7);

  /*        VÊNUS                 */ //Diametro: 12.103,6 km
  Desenha_Orbita(17,17);

  /*        TERRA                    */ //Diametro: 12.756,2 km
  Desenha_Orbita(27,27);

  /*        MARTE                   */ //Diametro: 6.792,4 km
  Desenha_Orbita(41,41);

  /*        JÚPITER                */ //Diametro: 142.984 km
  Desenha_Orbita(80,80);

  /*        SATURNO              */ //Diametro: 120.536 km
  Desenha_Orbita(97,97);

  /*        URANO            */ //Diametro: 51.118 km
  Desenha_Orbita(107,107);

  /*        NETUNO            */  //Diametro: 49.528 km
  Desenha_Orbita(127,127);

  /*        PLUTÃO            */  //Diametro: 2.377 km
  Desenha_Orbita(140,140);

}

void desenhaAsteroide(float x,float y){
  glPushMatrix();
  int i;
  float rad;
  float afasta=1;
  glTranslated(0, -y*5, 0);
  //glColor3f(0.3, 0.3, 0.9);
  glEnable(GL_LIGHTING);
  for(i=0; i<360; i++) {
    rad = i*3.14/180;
    glTranslatef(cos(rad)*x/10,sin(rad)*y/10,0);
    glCallList(asteroideList);
  }
  glDisable(GL_LIGHTING);
  glPopMatrix();
}
/*Os próximos dois procedimentos foram modificados a partir do exemplo do site http://www.inf.pucrs.br/~manssour/OpenGL/TeaPot3D.c
da professora Isabel Harb Manssour da PUC-RS*/

void PosicionaObservador(void)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //

  // Posiciona e orienta o observador
  glTranslatef(-obsX*0.5,-obsY*0.5,-obsZ*0.5);
  glRotatef(rotX,1,0,0);
  glRotatef(rotY,0,1,0);
  glRotatef(rotZ,0,0,1);
}

void EspecificaParametrosVisualizacao(void)
{
  // Especifica sistema de coordenadas de projeção
  glMatrixMode(GL_PROJECTION);
  // Inicializa sistema de coordenadas de projeção
  glLoadIdentity();
  // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
  gluPerspective(angulo,fAspect,0.5,2000);
  PosicionaObservador();
}
void SpecialKeyboard(int tecla, int x, int y)
{
  switch (tecla)
  {
    case GLUT_KEY_RIGHT:
    glRotatef(rotX, 1, 0, 0);
    rotX++;
    break;

    case GLUT_KEY_LEFT:
    glRotatef(rotY, 0, 1, 0);
    rotY++;
    break;

    case GLUT_KEY_DOWN:
    if(angulo<=150) angulo +=5; //diminui zoom
    break;

    case GLUT_KEY_UP:
    if(angulo>=10)  angulo -=5; //aumenta zoom
    break;

  }
  EspecificaParametrosVisualizacao();
  glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y)
{
  switch(key)
  {
    // Tecla ESC
    case 27:
    printf("  Até logo! ^_^ \n");
    exit(0);
    break;

    case 'l': //Ativa/Remove o Sol
    case 'L':
    ativo=!ativo;
    glutDisplayFunc(Sistema_Solar_com_orbitas);
    break;

    case 49://numero 1 - visao de cima
    obsZ =2000;
    break;

    case 'c': //centraliza no Sol
    case 'C':
    obsZ =50;
    break;

    case 'o': //Mostra as orbitas
    case 'O':

    orbita =!orbita;

    if(orbita==1)
    {
      glutDisplayFunc(Sistema_Solar_com_orbitas);
    }
    else{
      //Mostra o sistema solar sem as orbitas
      glutDisplayFunc(Desenha);
    }

    break;
  }
  glLoadIdentity();
  gluLookAt(obsX,obsY,obsZ, 0,0,0, 0,1,0);
  glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{
  if(state==GLUT_DOWN)
  {
    // Salva os parâmetros atuais
    x_ini = x;
    y_ini = y;
    obsX_ini = obsX;
    obsY_ini = obsY;
    obsZ_ini = obsZ;
    rotX_ini = rotX;
    rotY_ini = rotY;
    bot = button;
  }
  else bot = -1;
}

void GerenciaMovim(int x, int y)
{
  // Botão esquerdo do mouse
  if(bot==GLUT_LEFT_BUTTON)
  {
    // Calcula diferenças
    int deltax = x_ini - x;
    int deltay = y_ini - y;
    // E modifica ângulos
    rotY = rotY_ini - deltax/SENS_ROT;
    rotX = rotX_ini - deltay/SENS_ROT;
  }
  // Botão direito do mouse
  else if(bot==GLUT_RIGHT_BUTTON)
  {
    int deltax = x_ini - x;
    int deltay = y_ini - y;
    // Calcula diferença
    int deltaz = deltax - deltay;
    // E modifica distância do observador
    obsZ = obsZ_ini + deltaz/SENS_OBS;
  }
  // Botão do meio
  else if(bot==GLUT_MIDDLE_BUTTON)
  {
    // Calcula diferenças
    int deltax = x_ini - x;
    int deltay = y_ini - y;
    // E modifica posições
    obsX = obsX_ini + deltax/SENS_TRANSL;
    obsY = obsY_ini - deltay/SENS_TRANSL;
  }
  PosicionaObservador();
  glutPostRedisplay();
}

void Redimensiona(GLsizei w, GLsizei h)
{
  // Para previnir uma divisão por zero
  if ( h == 0 ) h = 1;

  // Especifica as dimensões da viewport
  glViewport(0, 0, w, h);

  // Calcula a correção de aspecto
  fAspect = (GLfloat)w/(GLfloat)h;

  EspecificaParametrosVisualizacao();
}

void Sistema_Solar() /*Desenha o sistema solar e as órbitas dos planetas */
{
  float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  float a=t;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*        SOL             */
  if(ativo==1)
  {
    GLfloat light_ambient[] = {x,y,z,1.0};
    GLfloat light_diffuse[] = {x,y,z,1.0};
    GLfloat light_specular[] ={x, y, z, 1.0};
    GLfloat light_position[]={1.0, 0.0, 0.0, 1.0};
    // configura alguns parâmetros do modelo de iluminação: MATERIAL
    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glShadeModel (GL_SMOOTH);

    // Propriedades da fonte de luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glPushMatrix();
    glRasterPos2f(0,1.5);
    glutBitmapString(GLUT_BITMAP_9_BY_15, "Sol");
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj,GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textura[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glRotated(a*7, 0, 0, 1);
    glScalef(3,3,3);
    gluSphere(qobj,1,25,25);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
  }
  else{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

  }

  /*        MERCÚRIO        */ // Diametro: 4.879,4 km
  Desenha_planeta("Mercurio",textura[6], 7, 7, 2,0.48,3.7);

  /*        VÊNUS              */ //Diametro: 12.103,6 km
  Desenha_planeta("Venus", textura[7], 17, 17, 1.2, 1.21 ,2.5);

  /*        TERRA E LUA         */// Diametro Terra: 12.756,2 km
  desenha_planetas_com_Satelites("Terra", textura[1], textura[2],27, 27, 1.2,1.27,0.5,1.9,0.2);

  /*        MARTE                   */ //Diametro: 6.792,4 km
  desenha_planetas_com_Satelites("Marte", textura[3], textura[17],41, 41, 1.2,0.68,0.5,1.9,1);

  /*        JÚPITER                */ //Diametro: 142.984 km
  Desenha_planetas_com_Satelites_e_Aneis("Jupiter", textura[4],textura[13],textura[11],80, 80, 1.5,1.43,0.25,1.9,1);

  /*        SATURNO              */ //Diametro: 120.536 km
  Desenha_planetas_com_Satelites_e_Aneis("Saturno", textura[5],textura[12],textura[11],97,97, 1.5,1.2,0.25,1.5,1);

  /*        URANO            */ //Diametro: 51.118 km
  Desenha_planetas_com_Satelites_e_Aneis("Urano", textura[8],textura[14],textura[11],107, 107, 1.5,0.51,0.25,1.2,1.3);

  /*        NETUNO            */  //Diametro: 49.528 km
  Desenha_planetas_com_Satelites_e_Aneis("Netuno", textura[9],textura[15],textura[11],127, 127, 1.5,0.495,0.20,1,1);

  /*        PLUTÃO          */  //Diametro: 2.377 km
  desenha_planetas_com_Satelites("Plutao", textura[10], textura[16],140, 140,-0.35,2.3,3,0.8,0.6);

  glRasterPos2f(0,-51);
  glutBitmapString(GLUT_BITMAP_9_BY_15, "Cinturao de Asteroides");
  desenhaAsteroide(10,10);


}
void Sistema_Solar_com_orbitas()
{
  glDrawBuffer(GL_BACK);
  // Limpa a janela de visualizao com a cor de fundo especificada
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //desenha todos os objetos na tela
  Sistema_Solar();
  mostraOrbitas();
  glutSwapBuffers();
}

void Desenha()
{
  glDrawBuffer(GL_BACK);
  // Limpa a janela de visualizao com a cor de fundo especificada
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //desenha todos os objetos na tela
  Sistema_Solar();
  glutSwapBuffers();
}

static void atualiza(void)
{
  glutPostRedisplay();
}

void imprimeInstrucoes() {
  printf("Ajuda:\n");
  printf("  Aperte as setas para cima e para baixo para aumentar/diminuir zoom \n");
  printf("  Aperte as setas para esquerda e para direita para rotacionar o sistema solar \n");
  printf("  Aperte O para mostrar/remover as orbitas.\n");
  printf("  Movimente tambem o mouse pressionando o seu botao direito para se aproximar/afastar pelo sistema solar. \n");
  printf("  Aperte L para remover o Sol e toda a luz do sistema.\n");
  printf("  Aperte C para centralizar a visao do sistema (no Sol).\n");
  printf("  Aperte 1 para alternar para visao superior do sistema.\n");
  printf("  Digite ESC para sair.\n");
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitContextVersion(1,1);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
  glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(1800,1200);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Sistema Solar");
  imprimeInstrucoes();
  glutDisplayFunc(Sistema_Solar_com_orbitas);
  glutReshapeFunc(Redimensiona);
  glutSpecialFunc (SpecialKeyboard);
  glutKeyboardFunc(teclado);
  glutMouseFunc(GerenciaMouse);
  glutMotionFunc(GerenciaMovim);
  Inicializa();

  /*Algoritmo para biblioteca SDL retirado de https://gist.github.com/armornick/3497064*/
  // Initialize SDL
  Mix_PlayingMusic();

  glutIdleFunc(atualiza);
  glutMainLoop();

  // clean up our resources
  Mix_FreeMusic(music);

  // quit SDL_mixer
  Mix_CloseAudio();

  return 0;
}
