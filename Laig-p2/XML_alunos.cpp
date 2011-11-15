// G1_Ilum.cpp : Defines the entry point for the console application.
//


#ifdef __APPLE__
#include <GLUI/GLUI.h>
#else
#include <gl/glui.h>
#endif
#include <math.h>
#include <iostream>
#include "SceneParser.h"
#include "Texture.h"
#include "Primitive.h"
#include "Illumination.h"
#include "Lights.h"
#include "Material.h"
#include "Views.h"

using namespace std;

// dimensoes e localizacao da janela
#define DIMX 500
#define DIMY 500
#define INITIALPOS_X 200
#define INITIALPOS_Y 200


float xy_aspect;

// matriz de transf. geometrica utilizada pelo botao esferico
float view_rotate[16] =	{ 1,0,0,0,
						  0,1,0,0,
						  0,0,1,0,
						  0,0,0,1 };

// vector de posicao utilizado pelo botao de afastamento
float obj_pos[] = { 0.0, 0.0, 0.0 };

// declarações para os tres eixos (cilindros)
double axis_radius_begin =  0.2;
double axis_radius_end   =  0.0;
double axis_lenght       = 16.0;
int axis_nslices = 8;
int axis_nstacks = 1;

// declaracoes para a esfera de origem de coordenadas
double orig_radius = 0.5;
int orig_slices = 8;
int orig_stacks =16;
	
// declaracoes para o plano e caixa
float mat1_shininess[] = {128.0}; 

//float mat1_specular[] = {1.0,1.0,1.0};	/* specular reflection. */
float mat1_specular[] = {0.4, 0.4, 0.4, 1.0};	/* specular reflection. */
//float mat1_diffuse[] =  {0.0, 0.0, 0.0, 1.0};	/* diffuse reflection. */
float mat1_diffuse[] =  {0.6, 0.6, 0.6, 1.0};	/* diffuse reflection. */
float mat1_ambient[] =  {0.6, 0.6, 0.6, 1.0};	/* ambient reflection. */
double dimx= 6.0;
double dimy= 2.0;
double dimz=10.0;

float light0_kc=0.0;
float light0_kl=0.0;
float light0_kq=0.1;

// declarações para as stripes que formam o plano
double i,j;
double di, limi=dimx, divisoes_i = 60;	//60
double dj, limj=dimz, divisoes_j = 100;	//100

// declarações para a fonte de luz LIGHT0;
float light0_position[]  = {0.0, 3.0, 4.0, 1.0}; // nao necessaria...
float light0_ambient[] =   {0.0, 0.0, 0.0, 1.0}; // sem componente ambiente
//float light0_diffuse[] =   {1.0, 1.0, 0.0, 0.0};
float light0_diffuse[] =   {0.8, 0.8, 0.8, 1.0};
//float light0_specular[] =  {0.0, 0.0, 0.0, 0.0};
float light0_specular[] =  {0.8, 0.8, 0.8, 1.0};
double light0x = dimx/2.0;
double light0y = 1;
double light0z = dimz/4.0;
double symb_light0_radius = 0.2;	// esfera que
int symb_light0_slices = 8;			// simboliza a
int symb_light0_stacks =16;			// fonte de luz light0

// fonte (global) de luz ambiente 
//float light_ambient[] = {0.0, 0.0, 0.0, 1.0}; /* Set the background ambient lighting. */
float light_ambient[] = {0.2, 0.2, 0.2, 1.0}; /* Set the background ambient lighting. */

// variaveis para a janela
int main_window;
GLUI  *glui2;

//SceneLoader *scene;

//Utiliza as estruturas de dados com a informação do xml para construir o plano



void display(void)
{
	// ****** declaracoes internas 'a funcao display() ******

	GLUquadric* glQ;	// nec. p/ criar sup. quadraticas (cilindros, esferas...)

	// ****** fim de todas as declaracoes da funcao display() ******



	glQ = gluNewQuadric();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	// inicializacoes da matriz de visualizacao
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .1, 50.0 );

	//inicializacoes da matriz de transformacoes geometricas
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	// afasta a cena de 25 unidades mais a distância...
	glTranslated(0.0,0.0,-25.0);
	// ...decorrente da utilizacao do botao de afastamento
    glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );    

	// roda a cena para ficar em perspectiva
	glRotated(20.0, 1.0,0.0,0.0 );		// 20 graus em torno de X
	glRotated(-45.0, 0.0,1.0,0.0 );		//-45 graus em torno de Y

	// aplica efeito do botao de rotacao
	glMultMatrixf( view_rotate );

	// permissao de atribuicao directa de cores
	// para objectos ue nao tem material atribuido
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Actualizacao da posicao da fonte de luz
	light0_position[0] = light0x;	// por razoes de eficiencia, os restantes 
	light0_position[1] = light0y;	// parametros _invariaveis_ da LIGHT0 estao
	light0_position[2] = light0z;	// definidos na rotina inicializacao
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	// esfera que simboliza a LIGHT0
	glColor3f(1.0,1.0,0.0);		// cor amarela
	gluQuadricOrientation( glQ, GLU_INSIDE);
	glPushMatrix();
	glTranslated(light0x,light0y,light0z);
	gluSphere(glQ, symb_light0_radius, symb_light0_slices, symb_light0_stacks);
    glPopMatrix();

	gluQuadricOrientation(glQ, GLU_OUTSIDE);


//	//desenhar a esfera no centro
	glColor3f(1.0,1.0,1.0);		
	gluSphere(glQ, orig_radius, orig_slices, orig_stacks);

//  aumentar e diminuir a atenuação
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  light0_kc);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    light0_kl);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light0_kq);

	// esfera representativa da origem das coordenadas
	// falta declarar a cor
	// desenhar o objecto

	// cilindro representativo do eixo X
	glColor3f(1.0,0.0,0.0);		// vermelho
	glPushMatrix();
	glRotated(90.0, 0.0,1.0,0.0 );
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();

	// cilindro representativo do eixo Y
	glColor3f(0.0,1.0,0.0);		// verde
	glPushMatrix();
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();
	
	// cilindro representativo do eixo Z
	glColor3f(0.0,0.0,1.0);		// azul
	glPushMatrix();
	// nao necessita rotacao... glRotated(...);
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();

	// inibicao de atribuicao directa de cores
	glDisable(GL_COLOR_MATERIAL);


	// define caracteristicas de cor do material do plano e da caixa
	glMaterialfv(GL_FRONT, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat1_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat1_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat1_ambient);

	
glCallList(1);

	
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
   
	glFlush();
}


/* Mouse handling */
void processMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{	 
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{	
	}
	
	glutPostRedisplay();
	
}

void processMouseMoved(int x, int y)
{
	
	// pedido de refrescamento da janela
	glutPostRedisplay();				

}

void processPassiveMouseMoved(int x, int y)
{

	// pedido de refrescamento da janela
	glutPostRedisplay();				
}

void reshape(int w, int h)
{
	int tx, ty, tw, th;

	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	xy_aspect = (float)tw / (float)th;

	glutPostRedisplay();

}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
	  case 'q':
		light0y+= 0.1;
		cout << "light0y: " << light0y << endl; 
		break;
	  case 'a':
		light0y-= 0.1;
		cout << "light0y: " << light0y << endl; 
		break;
	  case 'i':
		light0_kc+=0.1;
		cout << "light0_kc: " << light0_kc << endl; 
		break;
	  case 'o':
		light0_kc-=0.1;
		cout << "light0_kc: " << light0_kc << endl; 
		break;
	  case 'k':
		light0_kl+=0.1;
		cout << "light0_kl: " << light0_kl << endl; 
		break;
	  case 'l':
		light0_kl-=0.1;
		cout << "light0_kl: " << light0_kl << endl; 
		break;
	  case 'n':
		light0_kq+=0.1;
		cout << "light0_kq: " << light0_kq << endl; 
		break;
	  case 'm':
		light0_kq-=0.1;
		cout << "light0_kq: " << light0_kq << endl; 
		break;
	  case 'z':
		divisoes_i+=3;
		cout << "div_i: " << divisoes_i <<endl;
		break;
	  case 'x':
		divisoes_i-=3;
		cout << "div_i: " << divisoes_i <<endl;
		break;
	  case 'c':
		divisoes_j+=5;
		cout << "div_j: " << divisoes_j <<endl;
		break;
	  case 'v':
		divisoes_j-=5;
		cout << "div_j: " << divisoes_j <<endl;
		break;

      case 27:		// tecla de escape termina o programa
         exit(0);
         break;
   }
}


void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  


  glutPostRedisplay();

  /****************************************************************/
  /*            This demonstrates GLUI::sync_live()               */
  /*   We change the value of a variable that is 'live' to some   */
  /*   control.  We then call sync_live, and the control          */
  /*   associated with that variable is automatically updated     */
  /*   with the new value.  This frees the programmer from having */
  /*   to always remember which variables are used by controls -  */
  /*   simply change whatever variables are necessary, then sync  */
  /*   the live ones all at once with a single call to sync_live  */
  /****************************************************************/

//  glui->sync_live();

}

void inicializacao()
{

	glFrontFace(GL_CCW);		/* Front faces defined using a counterclockwise rotation. */
	glDepthFunc(GL_LEQUAL);		/* Por defeito e GL_LESS */
	glEnable(GL_DEPTH_TEST);	/* Use a depth (z) buffer to draw only visible objects. */
	glEnable(GL_CULL_FACE);		/* Use face culling to improve speed. */
	glCullFace(GL_BACK);		/* Cull only back faces. */

	// por defeito a cor e de fundo e o preto
	//glClearColor(1.0,1.0,1.0,1.0);    // cor de fundo a branco


	glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);  // define luz ambiente
	
	// parametros de iluminacao
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	// a direccao e a posicao estao na rotina display()
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);				// GL_FLAT / GL_SMOOTH

	glPolygonMode(GL_FRONT, GL_FILL);	// preence a face da frente dos poligonos
	//glPolygonMode(GL_FRONT, GL_LINE);	// desenha arestas dos poligonos
	
}



int main(int argc, char* argv[])
{


	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (DIMX, DIMY);
	glutInitWindowPosition (INITIALPOS_X, INITIALPOS_Y);
	main_window = glutCreateWindow (argv[0]);
 
   glutDisplayFunc(display);
   GLUI_Master.set_glutReshapeFunc(reshape);
   GLUI_Master.set_glutKeyboardFunc (keyboard);
   GLUI_Master.set_glutMouseFunc(processMouse);
   glutMotionFunc(processMouseMoved);
   glutPassiveMotionFunc(processPassiveMouseMoved);   
   GLUI_Master.set_glutSpecialFunc( NULL );
   

	/*** Create the bottom subwindow ***/
	glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
	glui2->set_main_gfx_window( main_window );

	GLUI_Rotation *view_rot = glui2->add_rotation( "Rotacao", view_rotate );
	view_rot->set_spin( 1.0 );
	glui2->add_column( false );

	GLUI_Translation *trans_z = 
	glui2->add_translation( "Zoom", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .02 );


	/* We register the idle callback with GLUI, not with GLUT */
	GLUI_Master.set_glutIdleFunc( myGlutIdle );
	 loaddsxfile("greenhill.dsx");
	inicializacao();
	
	glutMainLoop();

	return 0;
}
