#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include <mmsystem.h>
//#include <stdafx.h>
#include "BmpLoader.h"
#include <iostream>
GLdouble angle_1 = 0, angle_2 = 0;
static GLdouble sentinel = 0;
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=1000;
GLfloat alpha = 0.0, theta = 0.0, beta = 0.0, axis_x=0.0, axis_y=0.0, axis_z=0.0, nightTheta=0,t=20,t2=22,sunx=0,suny=0,tosterY=0,waterY=0,theta_fan_rotate = 0.0,skyTheta=0.0, humanz = 16.5,theta_circle=0.0, pirateBoatTheta = 0.0,doorDistx1=0,doorDistx2=0,lidTheta = 0,ice=0.0,icex= 0,carz=0,cablex=0;
GLboolean bRotate = false, uRotate = false, tRotate = false,night=false, skyRotate=false, fan_Rotate = false,toPlay = false,toPause = false,waterplay = false,
          waterpause = false,humanMove = false,carMove=false,cableMove=true,moveState = true,lidOpen = false, lidClose=false,iceon = false,iceoff = false, light_0_on = true, light_1_on = true, light_2_on = true, light_3_on = true,pirateBoatFlag = false, pirateBoatCheck = false,doorOpen= false,doorClose=false,


          amb_light = true, dif_light = true, spec_light = true;
GLdouble ttx,tty,ttz=0;
GLfloat eyeX = 0;
GLfloat eyeY = 3;
GLfloat eyeZ = 80;

GLfloat lookX = 0;
GLfloat lookY = 3;
GLfloat lookZ = 50;


GLfloat upx = 0;
GLfloat upy = 1;
GLfloat upz = 0;



GLfloat scale_x = 1;
GLfloat scale_y = 1;
GLfloat scale_z = 1;

double limit = 360;
double roll_value = 5;
GLfloat angleYaw =90.0, anglePitch = 0.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 90.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = -90.0, angleRollLimit2 = -90.0;

int f = 0;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>	//Needed for console output (debugging)
#include <gl/freeglut.h>
#include <vector>
#include <iostream>
#include <thread>

#ifdef WIN32
#include "gltools.h"
#include <windows.h>		// Must have for Windows platform builds
//#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
//#include <gl\glu.h>			// OpenGL Utilities
//#include "glm.h"

#endif

//refernce files
#include "3DExample1\\camera.h"


#include "3DExample1\\vec.h"
#include "3DExample1\\assets.h"
#include <sstream>


#define OBJPATH = "3DExample1\\objects\\";
#define TEXTUREPATH = "3DExample1\\textures\\";


asset sun;

enum Textures
{
    glasswall = 10,
    doortexture,
    carpet,
    rooftop,
    stage,


    countertexture,
    toasterr,
    ruti,
    cup_coffee,
    smile,
};

GLfloat PI = 3.14159265;
static GLfloat cube[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {-1.0, 1.0, -1.0},

};
static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};


//static GLubyte p_Indices[2][3] =
//{
//    {0, 1, 2},
//    {3, 4, 5}
//};

static GLubyte quadIndices[6][4] =
{
    {0,1,2,3},
    {7,6,5,4},
    {2,6,7,3},

    {0,4,5,1},
    {2,1,5,6},
    {7,4,0,3},

};

static GLfloat colors[6][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {0.5,0.5,0.5},
};
int i = 1;
GLuint ID_[100];

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID_[i]);
    glBindTexture(GL_TEXTURE_2D, ID_[i]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID_[i++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

static void DrawCube(GLint R = 255, GLint G = 255, GLint B = 255, GLboolean emission = false)
{
    GLfloat r = R / 255.0f;
    GLfloat g = G / 255.0f;
    GLfloat b = B / 255.0f;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    GLfloat mat_em[] = { r, g, b, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    if (emission) glMaterialfv(GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    for (GLint i = 0; i < 6; i++)
        for (GLint i = 0; i < 6; i++)
        {
            glBegin(GL_QUADS);

            glVertex3fv(&cube[quadIndices[i][0]][0]);
            glTexCoord2f(1, 1);
            glVertex3fv(&cube[quadIndices[i][1]][0]);
            glTexCoord2f(1, 0);
            glVertex3fv(&cube[quadIndices[i][2]][0]);
            glTexCoord2f(0, 0);
            glVertex3fv(&cube[quadIndices[i][3]][0]);
            glTexCoord2f(0, 1);
            glEnd();
        }
}

void drawcube(GLint c1, GLint c2, GLint c3, GLboolean emission = false)
{

    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);




    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);

        glVertex3fv(&cube[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&cube[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
        glEnd();
    }



}

void draw_room()
{

    //floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(20,0.1,20);
    glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(255, 255, 255);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,-0.2,0);
    glScalef(100000,0.2,100000);

    //glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(0, 168, 0);
    glPopMatrix();

    //uperfloor
    glPushMatrix();
    glScalef(20,0.1,20);
    glTranslatef( 0,201.4,-5.55112e-17);
    drawcube(168, 168, 168);
    glPopMatrix();

    //tiles
//    for(GLint hCount=1; hCount<26; hCount+=4)
//    {
//        for(GLint vCount=1; vCount<26; vCount+=4)
//        {
//            if((hCount+vCount)%2==0)
//            {
//                glPushMatrix();
//                glScalef(1.5,0.05,1.5);
//                glTranslatef(-(20-hCount*1.5)/1.5,0.105/0.05,-(20-vCount*1.5)/1.5);
//                drawcube(25,25,25);
//                glPopMatrix();
//            }
//
//        }
//
//    }


    //left wall
    glEnable(GL_TEXTURE_2D);



    glPushMatrix();
    glScalef(.1,10,20);
    glTranslatef(-20/0.1,1,0);
    glBindTexture(GL_TEXTURE_2D, 6);



    drawcube(255, 255, 255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




//
    //right wall
//    glPushMatrix();
//    glScalef(.005,10,20);
//    glTranslatef(20/0.005,1,0);
//    drawcube(35, 89, 92);
//    glPopMatrix();
//


    //back wall left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::glasswall);
    glPushMatrix();
    glScalef(8,10,.1);
    glTranslatef(-1.5,1,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(255, 255, 255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //backwall upper
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::glasswall);
    glPushMatrix();
    glScalef(8,10,.1);
    glTranslatef(1.5,1,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(255, 255, 255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//    //backwall bottom
//    glPushMatrix();
//    glScalef(8,2.5,.1);
//    glTranslatef(0,1,-20/0.1);
//    glRotatef(180,0,1,0);
//    drawcube(104-25,139-25,153-25);
//    glPopMatrix();
    //backwall top
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::glasswall);
    glPushMatrix();
    glScalef(8,2.5,.1);
    glTranslatef(0,7,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(255, 255, 255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//
//    //windowframe
//    glPushMatrix();
//    glScalef(.5,5,.1);
//    glTranslatef(0,2,-20/0.1);
//    glRotatef(180,0,1,0);
//    drawcube(173, 123, 7);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(4,0.5,.1);
//    glTranslatef(0,4*2.5/0.5,-20/0.1);
//    glRotatef(180,0,1,0);
//    drawcube(173, 123, 7);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(.5,5,.3);
//    glTranslatef(-8,2,-20/0.3);
//    glRotatef(180,0,1,0);
//    drawcube(173, 123, 7);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(.5,5,.3);
//    glTranslatef(8,2,-20/0.3);
//    glRotatef(180,0,1,0);
//    drawcube(173, 123, 7);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(4.9,0.5,.3);
//    glTranslatef(0,5*3/0.5,-20/0.3);
//    glRotatef(180,0,1,0);
//    drawcube(173, 123, 7);
//    glPopMatrix();
//    glPushMatrix();
//    glScalef(4.9,0.5,.3);
//    glTranslatef(0,1.5*3/0.5,-20/0.3);
//    glRotatef(180,0,1,0);
//    drawcube(173, 123, 7);
//    glPopMatrix();

}

void draw_room2()
{

    //floor
     glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(20,0.1,20);
    glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(255, 255, 255);
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glScalef(.1,10,20);
    glTranslatef(-201,1,1.38778e-15);
    glBindTexture(GL_TEXTURE_2D, 6);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.1,10,20);
    glTranslatef(201.2,1,0);
    glBindTexture(GL_TEXTURE_2D, 6);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glScalef(20,0.1,20);
    glTranslatef(  0,199.4,0);
    drawcube(168, 168, 168);
    glPopMatrix();





}

void rooftop_room()
{
    //left wall
    //glEnable(GL_TEXTURE_2D);


    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::stage);
    glPushMatrix();
    glScalef(.1,10,20);
    glTranslatef( -198.4,3,-1);
    // glBindTexture(GL_TEXTURE_2D, 2);



    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::carpet);
    glPushMatrix();
    glTranslatef( -11.8,22.6,-20);
    glScalef(8,2.4,20);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::rooftop);
    glPushMatrix();
    glTranslatef( -11.8,40,-20);
    glScalef(8,0.1,20);
    drawcube(255, 255, 255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();

}
void draw_Cone(GLint c1, GLint c2, GLint c3,GLfloat a, GLfloat h)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();


    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);




    glutWireCone(a,h,100,100);
    glPopMatrix();


}
void draw_bulb()
{

    glPushMatrix();
    glTranslatef(-18, 16, -7);
    glScalef(2,.3,.3);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-17, 15, -7);
    glRotatef(-90, 1,0,0);
    draw_Cone(120,120,120,1,1);
    glPopMatrix();
}

void fan_handle_s()
{
    glPushMatrix();
    glTranslatef( 0,18.8,0);
    glScalef(0.2,1.0,0.2);
    drawcube(0.1, 0.2, 0.1);
    glPopMatrix();
}

void fan_s()
{
    glPushMatrix();
    glRotatef(theta_fan_rotate, 0.0, 1.0, 0.0);
    glTranslatef( 0,18,0);
    glScalef(0.4, 0.4, 0.4);

    for(int i = 0; i < 180; i++)
    {
        glPushMatrix();
        glScalef(2.0,0.5,1.0);
        glRotatef(theta_circle+=2, 0.0, 1.0, 0.0);

        drawcube(0.7, 0.2, 0.2);
        glPopMatrix();
    }

    glPushMatrix();
    glScalef(7.0,0.3,2.0);
    drawcube(0.7, 0.4, 0.4);
    glPopMatrix();

    glPushMatrix();
    glRotatef(120, 0.0, 1.0, 0.0);
    glScalef(7.0,0.3,2.0);
    drawcube(0.7, 0.4, 0.4);
    glPopMatrix();

    glPushMatrix();
    glRotatef(240, 0.0, 1.0, 0.0);
    glScalef(7.0,0.3,1.5);
    drawcube(0.7, 0.4, 0.4);
    glPopMatrix();


    glPopMatrix();
}



//void draw_cabinet(){
//    //left cabinet
//    glPushMatrix();
//    glScalef(2,2,4);
//    glTranslatef(-8.99,1,-4);
//    drawcube(161,72,15);
//    glPopMatrix();
//    //middle portion
//    glPushMatrix();
//    glScalef(2,1,4);
//    glTranslatef(-8.99,1,-2);
//    drawcube(40,40,40);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(2,2,4);
//    glTranslatef(-8.99,1,0);
//    drawcube(161,72,15);
//    glPopMatrix();
//
//    //details for left cabinet
//    glPushMatrix();
//    glScalef(.2,1.5,1.9);
//    glTranslatef(-16/.2,1.4,-7.4);
//    drawcube(200, 140, 81);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(.2,1.5,1.3);
//    glTranslatef(-16/.2,1.4,1.5);
//    drawcube(200, 140, 81);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(.2,1.5,1.3);
//    glTranslatef(-16/.2,1.4,-1.5);
//    drawcube(200, 140, 81);
//    glPopMatrix();
//
//    //detail for middle portion
//    glPushMatrix();
//    glScalef(.2,.5,1.4);
//    glTranslatef(-16/.2,2.1,-4.3);
//    drawcube(125, 125, 125);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(.2,.5,1.4);
//    glTranslatef(-16/.2,2.1,-7.2);
//    drawcube(125, 125, 125);
//    glPopMatrix();
//    //handles
//    glPushMatrix();
//    glTranslatef(-15.75,2.5,-12.6);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-15.75,2.5,-1.1);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-15.75,2.5,1.1);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//
//
//
//    //back cabinet
//    glPushMatrix();
//    glRotatef(-90,0,1,0);
//    glScalef(2,2,12);
//    glTranslatef(-8.99,1,0.33);
//    drawcube(161,72,15);
//    glPopMatrix();
//
//    //details for back cabinet
//    glPushMatrix();
//    glScalef(2.5,1.3,.2);
//    glTranslatef(-4.5,1.4,-16/0.2);
//    drawcube(200, 162, 81);
//    glPopMatrix();
//
//
//    //oven
//    glPushMatrix();
//    glScalef(2.5,1.3,.2);
//    glTranslatef(-2,1.4,-16/0.2);
//    drawcube(74, 187, 199);
//    glPopMatrix();
//    //oven switch
//    glPushMatrix();
//    glTranslatef(-3,3.5,-15.6);
//    glScalef(.165,.165,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-6.75,3.5,-15.6);
//    glScalef(.165,.165,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-5.5,3.5,-15.6);
//    glScalef(.165,.165,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-4.25,3.5,-15.6);
//    glScalef(.165,.165,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//
//
//    //handles
//    glPushMatrix();
//    glTranslatef(-3,2.5,-15.6);
//    glScalef(.4,.165,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-.8,2,-15.6);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(5.3,2,-15.6);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-9.3,2,-15.6);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//
//
//
//
//    glPushMatrix();
//    glScalef(2.5,1.3,.2);
//    glTranslatef(.5,1.4,-16/0.2);
//    drawcube(200, 162, 81);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(1.3,1.7,.2);
//    glTranslatef(4.8,1.18,-16/0.2);
//    drawcube(200, 162, 81);
//    glPopMatrix();
//
//    //strips
//    glPushMatrix();
//    glTranslatef(-8.2,2,-16);
//    glScalef(0.1, 2, .1);
//    drawcube(200, 180, 161);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-1.9,2,-16);
//    glScalef(0.1, 2, .1);
//    drawcube(200, 180, 161);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(4.3,2,-16);
//    glScalef(0.1, 2, .1);
//    drawcube(200, 180, 161);
//    glPopMatrix();
//
//}
//

void draw_basin()
{
    glPushMatrix();
    glScalef(2,.1,3);
    glTranslatef(-9,10/.4,-2.65);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.8,.1);
    glTranslatef(-9,3.2/.8,-5/.1);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.8,.1);
    glTranslatef(-9,3.2/.8,-11/.1);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(.1,.8,3);
    glTranslatef(-16/.1,3.2/0.8,-2.65);
    drawcube(170,170,170);
    glPopMatrix();




    //tap
    glPushMatrix();
    glTranslatef(-19.6,6,-9);
    glScalef(.2,.2,.2);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-19.6,6,-7.2);
    glScalef(.2,.2,.2);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-19.1,5.5,-8.1);
    glScalef(.8,.2,.2);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18.7,5.1,-8.1);
    glScalef(.2,.2,.2);
    drawcube(50,50,50);
    glPopMatrix();


}

//void draw_racks(){
//    glPushMatrix();
//    glScalef(2,2,3.5);
//    glTranslatef(-8.99,1,4);
//    drawcube(161,72,15);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glScalef(1.5,6,3.5);
//    glTranslatef(-12.35,1.5,4);
//    drawcube(161,72,15);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glScalef(2,.5,3.7);
//    glTranslatef(-9.0,30,3.77);
//    drawcube(161,72,15);
//    glPopMatrix();
//
//    //details for racks
//    glPushMatrix();
//    glScalef(.2,1.5,1.3);
//    glTranslatef(-16/.2,1.4,12);
//    drawcube(200, 162, 81);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(.2,1.5,1.3);
//    glTranslatef(-16/.2,1.4,9.75);
//    drawcube(200, 162, 81);
//    glPopMatrix();
//
//    //strips for racks
//
//    glPushMatrix();
//    glTranslatef(-17,8,14);
//    glScalef(.1,6,.1);
//    drawcube(200, 180, 161);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glTranslatef(-17,6,14);
//    glRotatef(90,1,0,0);
//    glScalef(.1,3.4,.1);
//    drawcube(200, 180, 161);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-17,8,14);
//    glRotatef(90,1,0,0);
//    glScalef(.1,3.4,.1);
//    drawcube(200, 180, 161);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-17,10,14);
//    glRotatef(90,1,0,0);
//    glScalef(.1,3.4,.1);
//    drawcube(200, 180, 161);
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(-17,12,14);
//    glRotatef(90,1,0,0);
//    glScalef(.1,3.4,.1);
//    drawcube(200, 180, 161);
//    glPopMatrix();
//
//
//    //handles
//    glPushMatrix();
//    glTranslatef(-15.75,2.5,13.5);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-15.75,2.5,14.75);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(200,200,200);
//    glPopMatrix();
//}

//void draw_fridge(){
//
//    glPushMatrix();
//    glTranslatef(15,4,-16.8);
//    glScalef(3,4,3);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(15,8.5,-16.8);
//    glScalef(3.01,.5,3.01);
//    drawcube(20,20,20);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(15,9,-16.8);
//    glScalef(3,4,3);
//    drawcube(200,200,200);
//    glPopMatrix();
//
//
//    //handles
//    glPushMatrix();
//    glTranslatef(12.5,6.25,-13.75);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(22,22,22);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(12.5,10.25,-13.75);
//    glRotatef(90, 0,0,1);
//    glScalef(.8,.15,.25);
//    drawcube(22,22,22);
//    glPopMatrix();
//
//
//}
//void reverse()
//{
//    if (angle_1 < 26 )// ||angle_2>-25)
//    {
//        angle_1 +=.01;
//        angle_2-=.01;
//    }
//    else
//    {
//        angle_1 = .0;
//        angle_2 = .0;
//    }
//
//    glutPostRedisplay();
//}
void WireCube(GLint c1, GLint c2, GLint c3)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);




    glutWireCube(1);
    glPopMatrix();


}

void legs()
{
    glPushMatrix();
    glScalef(3, 2, 1);
    WireCube(0,130,0);

    //////////////////////////////////////////first joint
    glPushMatrix();
    glRotatef(angle_1, 1, 0, 0);
    //glTranslated(0, 0, angle_1);
    glTranslatef(1, 0, 0);
    glScaled(.5, 2, 1);
    WireCube(0,130,0);

    ////////////////leg
    glPushMatrix();
    glTranslatef(0, -1, 0);

    glScalef(.5, 2, 1);
    WireCube(0,130,0);
    glPopMatrix();


    glPopMatrix();



    //////////////////////////////////////////first joint
    glPushMatrix();
    glRotated(angle_2, 1, 0, 0);
    glTranslatef(-1, 0, 0);
    glScaled(.5, 2, 1);
    WireCube(0,130,0);

    ////////////////leg
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(.5, 2, 1);

    WireCube(0,130,0);
    glPopMatrix();

    glPopMatrix();



    glPopMatrix();
}

//void general()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(0, 0.5, 0, 0);
//}

//void reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(65, w / h, 1, 150);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(10, 10, 20, 0, 0, 0, 0, 1, 0);
//}

//void display()
//{
//   // general();
//    glPushMatrix();
//    glRotated(95, 0, 1, 0);
//    legs();
//    glPopMatrix();
//    //glutSwapBuffers();
//}

void draw_switch()
{
    glPushMatrix();
    glTranslatef(10,8,-19.8);
    glScalef(1,1,.1);
    drawcube(222,222,222);
    glPopMatrix();
    //fridge wires
    glPushMatrix();
    glTranslatef(10,4.5,-19.8);
    glScalef(.1,2.5,.1);
    drawcube(22,22,22);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(11,2,-19.8);
    glScalef(1,.1,.1);
    drawcube(22,22,22);
    glPopMatrix();

    //switches
    glPushMatrix();
    glTranslatef(10,8,-19.8);
    glScalef(.15,.4,.12);
    drawcube(122,72,222);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.6,8,-19.8);
    glScalef(.15,.4,.12);
    drawcube(122,72,222);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.4,8,-19.8);
    glScalef(.15,.4,.12);
    drawcube(122,72,222);
    glPopMatrix();
    //redLight
    glPushMatrix();
    glTranslatef(10.7,8.6,-19.8);
    glScalef(.15,.15,.12);
    drawcube(222,0,0);
    glPopMatrix();

    //light
    glPushMatrix();
    glTranslatef(0.0,18,-19.8);
    glScalef(4,.5,.12);
    drawcube(222,222,222);
    glPopMatrix();

    //light wires
    glPushMatrix();
    glTranslatef(7,18,-19.8);
    glScalef(3,.1,.1);
    drawcube(22,22,22);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,13,-19.8);
    glScalef(.1,5,.1);
    drawcube(22,22,22);
    glPopMatrix();
}


void draw_shelf()
{
    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,1);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,-3);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,-7);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-.8);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-8.8);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-4.8);
    drawcube(170,170,170);
    glPopMatrix();

}

void Teapot(GLint c1, GLint c2, GLint c3, GLfloat a)
{

    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidTeapot(a);

}
void door()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::doortexture);

    glPushMatrix();

    glTranslatef( -2.2,6.6,-19.6);
    glScalef(2.3,8.2,0.3);
    drawcube(249,250,251);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void draw_kettle()
{
    glPushMatrix();
    glTranslatef(-18,10.8,-5.8);

    Teapot(125, 66, 32,0.7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-18,10.8,2);

    Teapot(66, 125, 32,0.7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-18,10.8,-13.5);
    Teapot(66, 32, 125,0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,7.3,-17.5);
    Teapot(125, 32, 66,0.7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-18,7.3,-9.5);
    Teapot(32, 125,66,0.7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-18,7.3,-1.5);
    Teapot(32, 66, 125,0.7);
    glPopMatrix();

}


void draw_stove()
{

    glPushMatrix();
    glTranslatef(-5,4.5,-18);
    glScalef(5,.5,1.7);
    drawcube(230,230,230);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5,4.5,-16.2);
    glScalef(5,.5,.1);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.5,4.5,-16.2);
    glScalef(.1,.1,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,4.5,-16.2);
    glScalef(.1,.1,.25);
    drawcube(200,200,200);
    glPopMatrix();

    //details
    glPushMatrix();
    glTranslatef(-7.5,5.0,-17.2);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();





    glPushMatrix();
    glTranslatef(-7.5,5.0,-19);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.5,5.0,-17.2);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.5,5.0,-19);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();





    glPushMatrix();
    glTranslatef(-0.5,5.0,-17.2);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5,5.0,-19);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5,5.0,-17.2);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,5.0,-19);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,6.1,-18);

    glColor3ub(32, 66, 125);
    Teapot(32, 66, 125,1.5);
    glPopMatrix();


}


void draw_circle(void)
{
    float x, y;
    int i;
    GLfloat radius;
    int triangleAmount = 40;
    GLfloat twicePI = 2.0*PI;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(200,200,200);
    x = 0;
    y = 0;
    radius = 20;

    glVertex2f(x,y);
    for (i=0; i<=triangleAmount; i++);
    {
        glVertex3f(
            x+(radius*cos(i*twicePI/triangleAmount)),
            y+(radius*sin(i*twicePI/triangleAmount)),
            1
        );

    }
    glEnd();

}


void draw_fan()
{
    glPushMatrix();
    glTranslatef(-15.5,16,-19.8);
    glScalef(1.5,1.5,.2);
    drawcube(222,222,222);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15.5,16,-19.78);
    glScalef(1.2,1.2,.22);
    drawcube(22,22,22);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.5,16,-19.7);
    glScalef(.2,.2,.3);
    drawcube(222,222,222);
    glPopMatrix();


//
//    //fan wire
//    glPushMatrix();
//    glTranslatef(-3,16.5,-19.8);
//    glScalef(12.2,.1,.1);
//    drawcube(22,22,22);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(9.3,12.75,-19.8);
//    glScalef(.1,3.75,.1);
//    drawcube(22,22,22);
//    glPopMatrix();
}

void fan_blade()
{
    glPushMatrix();

    //fanBlade
    glPushMatrix();
    glTranslatef(-15.5,16,-19.7);
    glRotatef(45,0,0,1);
    glScalef(1.15,.2,.3);
    drawcube(222,222,222);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15.5,16,-19.7);
    glRotatef(45,0,0,1);
    glScalef(.2,1.15,.3);
    drawcube(222,222,222);
    glPopMatrix();
    glPopMatrix();

}

void table()
{

    glPushMatrix();
    glPushMatrix();
    glScalef(0.5,1.4,0.5);
    glTranslatef(-30.6,1,-22.8);
    drawcube(10,10,10);
    glPopMatrix();
    glPushMatrix();
    glScalef(0.5,1.4,0.5);
    glTranslatef( -30.6,1,-12.8);
    drawcube(10,10,10);
    glPopMatrix();
    glPushMatrix();
    glScalef(0.5,1.4,0.5);
    glTranslatef( -15.6,1,-12.8);
    drawcube(10,10,10);
    glPopMatrix();
    glPushMatrix();
    glScalef(0.5,1.4,0.5);
    glTranslatef( -15.6,1,-22.8);
    drawcube(10,10,10);
    glPopMatrix();
    glPushMatrix();
    glScalef(3.9,0.4,3.9);
    glTranslatef( -3,8,-2.2);
    drawcube(244,245,247);
    glPopMatrix();
    glPopMatrix();



}

//
//void draw_Cone(GLint c1, GLint c2, GLint c3,GLfloat a, GLfloat h)
//{
//    GLfloat r = c1/255.0;
//    GLfloat g = c2/255.0;
//    GLfloat b = c3/255.0;
//    glPushMatrix();
//
//
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { r, g, b, 1.0 };
//    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = {60};
//
//    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
//
//
//
//
//    glutWireCone(a,h,100,100);
//    glPopMatrix();
//
//
//}
//void draw_bulb()
//{
//
//    glPushMatrix();
//    glTranslatef(-18, 16, -7);
//    glScalef(2,.3,.3);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glTranslatef(-17, 15, -7);
//    glRotatef(-90, 1,0,0);
//    draw_Cone(120,120,120,1,1);
//    glPopMatrix();
//}




void draw_Sphere(GLint c1, GLint c2, GLint c3,GLboolean emission = false)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glutSolidSphere(2,100,100);
    glPopMatrix();
//22, 22, 128

}
void draw_sphere(GLint c1, GLint c2, GLint c3,GLboolean emission = false)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glutSolidSphere(1,20,20);
    glPopMatrix();
//22, 22, 128

}
void draw_cup(GLint c1, GLint c2, GLint c3,GLboolean emission = false)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glutSolidTeacup(1);
    glPopMatrix();
//22, 22, 128

}
void draw_cupp(GLint c1, GLint c2, GLint c3,GLboolean emission = false)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glutSolidTeacup(6);
    glPopMatrix();
//22, 22, 128

}


void light(double x, double y, double z, GLenum L, bool light_on, bool spot)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(L);

    if(light_on)
    {

        if(amb_light) glLightfv( L, GL_AMBIENT, light_ambient);
        else glLightfv( L, GL_AMBIENT, no_light);

        if(dif_light) glLightfv( L, GL_DIFFUSE, light_diffuse);
        else glLightfv( L, GL_DIFFUSE, no_light);

        if(spec_light) glLightfv( L, GL_SPECULAR, light_specular);
        else glLightfv( L, GL_SPECULAR, no_light);

        glLightfv( L, GL_POSITION, light_position);
    }

    else
    {
        glLightfv( L, GL_AMBIENT, no_light);
        glLightfv( L, GL_DIFFUSE, no_light);
        glLightfv( L, GL_SPECULAR, no_light);
        glLightfv( L, GL_POSITION, no_light);
    }

    if(spot)
    {
        GLfloat spot_direction[] = { -1.0, 0.0, 0.0 };
        glLightfv(L, GL_SPOT_DIRECTION, spot_direction);
        glLightf( L, GL_SPOT_CUTOFF, 55);
    }

}
void light2(double x, double y, double z, GLenum L, bool light_on, bool spot)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.0, 0.6, 0.6, 1.0 };
    GLfloat light_specular[] = { 0.0, 0.6, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(L);

    if(light_on)
    {

        if(amb_light) glLightfv( L, GL_AMBIENT, light_ambient);
        else glLightfv( L, GL_AMBIENT, no_light);

        if(dif_light) glLightfv( L, GL_DIFFUSE, light_diffuse);
        else glLightfv( L, GL_DIFFUSE, no_light);

        if(spec_light) glLightfv( L, GL_SPECULAR, light_specular);
        else glLightfv( L, GL_SPECULAR, no_light);

        glLightfv( L, GL_POSITION, light_position);
    }

    else
    {
        glLightfv( L, GL_AMBIENT, no_light);
        glLightfv( L, GL_DIFFUSE, no_light);
        glLightfv( L, GL_SPECULAR, no_light);
        glLightfv( L, GL_POSITION, no_light);
    }

    if(spot)
    {
        GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
        glLightfv(L, GL_SPOT_DIRECTION, spot_direction);
        glLightf( L, GL_SPOT_CUTOFF, 55);
    }

}

void upper_light()
{

    glPushMatrix();
    glTranslatef(-12,16.2,-12.8);
    glScalef(.4,4,.2);
    drawcube(10,10,10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-12,11.7,-12.8);
    glRotatef(-90, 1,0,0);
    draw_Cone(120,120,120,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12,12,-12.8);
    glScalef(.2,.2,.2);
    draw_Sphere(0,180,180, light_3_on);
    glPopMatrix();

}


void upper_light2()
{

    glPushMatrix();

    glPushMatrix();
    glTranslatef(-12,16.2,-12.8);
    glScalef(.4,4,.2);
    drawcube(10,10,10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-12,11.7,-12.8);
    glRotatef(-90, 1,0,0);
    draw_Cone(120,120,120,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12,12,-12.8);
    glScalef(.2,.2,.2);
    draw_Sphere(0,180,180, light_3_on);
    glPopMatrix();
    glPopMatrix();

}

void upper_light3()
{

    glPushMatrix();

    glPushMatrix();
    glTranslatef(-12,16.2,-12.8);
    glScalef(.4,4,.2);
    drawcube(10,10,10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-12,11.7,-12.8);
    glRotatef(-90, 1,0,0);
    draw_Cone(120,120,120,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12,12,-12.8);
    glScalef(.2,.2,.2);
    draw_Sphere(0,180,180, light_3_on);
    glPopMatrix();
    glPopMatrix();

}

void chair()
{
    glPushMatrix();
    glPushMatrix();
    glScalef(0.5,1.4,0.5);
    glTranslatef(-30.6,1,-22.8);
    drawcube(204,102,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,1.4,0.5);
    glTranslatef( -30.6,1,-12.8);
    drawcube(204,102,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,1.4,0.5);
    glTranslatef( -15.6,1,-12.8);
    drawcube(204,102,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,1.4,0.5);
    glTranslatef( -15.6,1,-22.8);
    drawcube(204,102,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(3.9,0.4,3.9);
    glTranslatef( -3,8,-2.2);
    drawcube(255,178,102);
    glPopMatrix();
    glPopMatrix();



}


//void elevator()
//{
//
//
//    glPushMatrix();
//    glTranslatef(elevatorx1,-19.6);
//    drawcube(244,244,244);
//    glPopMatrix();
//
//}
//void elevator2()
//{
//
//
//    glPushMatrix();
//    glTranslatef(elevatorx2,-19.6);
//    drawcube(244,244,244);
//    glPopMatrix();
//
//}
void tap_water()
{

//    glPushMatrix();
//    glTranslatef(ttx,tty,ttz);
//    glScalef(.2,.6,.1);
//    drawcube(50,80,250);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(ttx,tty,ttz);
//    glScalef(.2,.6,.1);
//    drawcube(50,50,250);
//    glPopMatrix();
}
void sky()
{
    glPushMatrix();
    glTranslatef(0,150,0);
    glScalef(100000,0,100000);
    drawcube(135,206,235);
    glPopMatrix();
}
void fence()
{

    glPushMatrix();
    glTranslatef( -18.4,2,20.2);
    glScalef(0.8,2.2,0.3);
    drawcube(204,102,0);
    glPopMatrix();


}
void desk()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::countertexture);
    glPushMatrix();
    glTranslatef( -11.8,2,33.8);
    glScalef(7,2.2,4);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



}
void dolna()
{
    glPushMatrix();
    glTranslatef(  18.8,3.6,33.4);
    glScalef(0.1,3.5,0.1);
    drawcube(10,8,9);
    glPopMatrix();
}
void shiri()
{
    glPushMatrix();
    glTranslatef(-137.2,30.1,-25.3);
    glRotatef(180,0,1,0);
    glPushMatrix();

    glTranslatef(-69.4,-29.2,-7.2);
    glScalef(6,1,2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glTranslatef(0,2,-2);
    drawcube(244,201,105);
    glPopMatrix();
    glPopMatrix();

}
void firstFloorFence()
{


    //horizontal lines
    glPushMatrix();

    glTranslatef( 0,27,19.2);
    glScalef(20,.4,.4);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef( 19.6,27,-19.4);
    glScalef(.4,.4,40);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();

    glTranslatef( 0,27,-59);
    glScalef(20,.4,.4);
    drawcube(50,50,50);
    glPopMatrix();

//    glPushMatrix();
//    glTranslatef(-85,27,27);
//    glScalef(.4,.4,4.5);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glTranslatef(64.6,27,19.8);
//    glScalef(4.5,.4,.4);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//
//
    //vertical lines

    for(GLint i = 0; i<20; i++)
    {
        glPushMatrix();
        glTranslatef(19.6-i*2,23.6,19.2);
        glScalef(.4,3.3,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }
    //fence towards z axis right
    for(GLint i = 1; i<40; i++)
    {
        glPushMatrix();
        glTranslatef(19.6,23.7,21.2-i*2);
        glScalef(.4,3.6,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }
    for(GLint i = 0; i<20; i++)
    {
        glPushMatrix();
        glTranslatef(19.6-i*2,23.6,-59);
        glScalef(.4,3.3,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }
//    //fence towards z axis left
//    for(GLint i = 1; i<7;i++){
//        glPushMatrix();
//        glTranslatef(-84.8,23.6,33.2-i*2);
//        glScalef(.4,3.6,.4);
//        drawcube(255,255,255);
//        glPopMatrix();
//    }
//    for(GLint i = 1; i<5;i++){
//        glPushMatrix();
//        glTranslatef(69-i*2,23,19.8);
//        glScalef(.4,3.6,.4);
//        drawcube(255,255,255);
//        glPopMatrix();
//    }





}
void drawTorus(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidTorus(innerRadius, outerRadius, nsides, rings);

    //glutSolidTorus(0.5, 10.0, 16, 12);
}
void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere (1.0, 16, 16);
}

//void drawTorus(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, GLfloat shine=90)
//{
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
//    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = {shine};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
//
//    glutSolidTorus(innerRadius, outerRadius, nsides, rings);
//
//    //glutSolidTorus(0.5, 10.0, 16, 12);
//}
static void Cylinder(GLint c1, GLint c2, GLint c3, GLboolean emission = false)
{
    GLfloat r = c1 / 255.0;
    GLfloat g = c2 / 255.0;
    GLfloat b = c3 / 255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    GLfloat mat_em[] = { r,g,b,1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    if (emission) glMaterialfv(GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    const double PI = 3.14159;

    /* top triangle */
    double i, resolution = 0.1;
    double height = 1;
    double radius = 0.5;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    //top Circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, height, 0);  /* center */
    for (i = 2 * PI; i >= 0; i -= resolution)
    {
        glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to 0 degrees */
    glTexCoord2f(0.5, 0.5);
    glVertex3f(radius, height, 0);
    glEnd();

    //bottom Circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 0, 0);  /* center */
    for (i = 0; i <= 2 * PI; i += resolution)
    {
        glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
        glVertex3f(radius * cos(i), 0, radius * sin(i));
    }
    glEnd();

    //cylinder side
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= 2 * PI; i += resolution)
    {
        const float tc = (i / (float)(2 * PI));
        glTexCoord2f(tc, 0.0);
        glVertex3f(radius * cos(i), 0, radius * sin(i));
        glTexCoord2f(tc, 1.0);
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to zero degrees */
    glTexCoord2f(0.0, 0.0);
    glVertex3f(radius, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(radius, height, 0);
    glEnd();

    glPopMatrix();
}
void drawCylinder(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 1.5, 1.5, 19, 32, 32);

}

static GLfloat v_box[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {3.0, 0.0, 0.0}, //1
    {0.0, 0.0, 3.0}, //2
    {3.0, 0.0, 3.0}, //3
    {0.0, 3.0, 0.0}, //4
    {3.0, 3.0, 0.0}, //5
    {0.0, 3.0, 3.0}, //6
    {3.0, 3.0, 3.0}, //7

};

static GLubyte BoxquadIndices[6][4] =
{
    {0,2,3,1},
    {0,2,6,4},
    {2,3,7,6},
    {1,3,7,5},
    {1,5,4,0},
    {6,7,5,4}
};

void materialProperty()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void drawBox()
{
    materialProperty();
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box[BoxquadIndices[i][0]][0], v_box[BoxquadIndices[i][0]][1], v_box[BoxquadIndices[i][0]][2],
                    v_box[BoxquadIndices[i][1]][0], v_box[BoxquadIndices[i][1]][1], v_box[BoxquadIndices[i][1]][2],
                    v_box[BoxquadIndices[i][2]][0], v_box[BoxquadIndices[i][2]][1], v_box[BoxquadIndices[i][2]][2]);

        glVertex3fv(&v_box[BoxquadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_box[BoxquadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_box[BoxquadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_box[BoxquadIndices[i][3]][0]);
        glTexCoord2f(0,1);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}
static GLfloat v_trapezoid[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.5, 3.0, 0.5}, //4
    {0.5, 3.0, 2.5}, //5
    {2.5, 3.0, 2.5}, //6
    {2.5, 3.0, 0.5}  //7
};

static GLubyte TquadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {3, 7, 4, 0}, // back
    {2, 3, 7, 6}, //right
    {0, 4, 5, 1}  //left
};

void drawTrapezoid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_trapezoid[TquadIndices[i][0]][0], v_trapezoid[TquadIndices[i][0]][1], v_trapezoid[TquadIndices[i][0]][2],
                    v_trapezoid[TquadIndices[i][1]][0], v_trapezoid[TquadIndices[i][1]][1], v_trapezoid[TquadIndices[i][1]][2],
                    v_trapezoid[TquadIndices[i][2]][0], v_trapezoid[TquadIndices[i][2]][1], v_trapezoid[TquadIndices[i][2]][2]);

        glVertex3fv(&v_trapezoid[TquadIndices[i][0]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][1]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][2]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][3]][0]);
    }
    glEnd();
}

void materialProperty_car(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void car(double pri_x, double pri_y, double pri_z, double sec_x, double sec_y, double sec_z)
{
    glPushMatrix();
    glRotatef(0, 1.0f, 0.0f, 0.0f);
    glRotatef(0, 0.0f, 1.0f, 0.0f);

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glEnd();


    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
//    glColor3f(1, 1.0, 1.0);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( sec_x, sec_y, sec_z, sec_x, sec_y, sec_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-30.0f,-15.0f,15.0f);
    glVertex3f(-30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,15.0f);
    glEnd();


    glBegin(GL_3D);
//    glColor3f(1, 0, 0);
    glTranslated(-20.0f,-15.0f,15.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);


//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,-30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(45.0f,0.0f,0.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
    glEnd();




    glPushMatrix();
    glColor3f(3.0,4.0,5.0);
    //glRotatef(45,0,0,1);
    glScalef(10,0.3,3);

//    glutWireCube(-20);


    glPopMatrix();


    glPopMatrix();
}
void sitmen()
{
    glPushMatrix();
    glRotatef(90,0,1,0);
    glScalef(0.1,0.1,0.1);
    // Left Leg
    glPushMatrix();
    glTranslatef( -5.8,1,-4.5);
    glRotatef(30,1,0,0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glTranslatef( 5.8,0.6,-3.6);
    glRotatef(30,1,0,0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(0, 22.5, 0);
    glScalef(6, 15, 0.1);
    DrawCube(255, 0, 255);
    glPopMatrix();

    // Neck
    glPushMatrix();
    glTranslatef(0, 40, 0);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(0, 45, 0);
    glScalef(5, 5, 5);
    draw_sphere(20, 20, 240);
    glPopMatrix();

    // Left Arm
    glPushMatrix();
    glTranslatef(-7.5, 32.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 25, 0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glTranslatef(7.5, 32.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 32.5, -7.5);
    glRotatef(90,1,0,0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();


//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, Textures::smile);
//    glPushMatrix();
//    glTranslatef( 10.3,34,-12.2);
//    draw_cupp(255,255,255);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

    // Ball in right hand
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_shininess[] = { 0 };
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//
//    glPushMatrix();
//    glTranslatef(ballX, ballY, ballZ);
//    glScalef(2.5, 2.5, 2.5);
//    glutSolidSphere(1, 20, 20);
//    glPopMatrix();
    glPopMatrix();
}
void ground()
{
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture( GL_TEXTURE_2D, ID2[14]);

    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(150,-20,150);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(150,-20,-150);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(-100,-20,-100);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(-100,-20,100);
    glEnd();
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);
}

void ground2()
{
    //glEnable(GL_TEXTURE_2D);
    // glBindTexture( GL_TEXTURE_2D, ID2[2]); //2

    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(10,-19.8,10);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(10,-19.8,-10);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-10,-19.8,-10);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-10,-19.8,10);
    glEnd();
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);
}
void boatBody()
{
    glPushMatrix();
    glTranslatef(-1.3, 0, 0);
    glScalef(1.5, 0.1, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.9, 0.9, 0.9,  0.0,0.0,0.0);
    glPopMatrix();


//    glPushMatrix();
//    glTranslatef(0, 1.5, 1.5);
//    glScalef(1.5, 1, 0.1);
//    glRotatef(180, 0, 0, 1);
//    glTranslatef(-1.25, -1.5, -1.25);
//    drawTrapezoid(0.412, 0.412, 0.412,  0.0,0.0,0.0);
//    //drawTrapezoid(0.4,0.4,0.4, 0.0,0.0,0.0);
//    glPopMatrix();

//    glPushMatrix();
//    glTranslatef(0, 1.5, -1.5);
//    glScalef(5.5, 1, 0.1);
//    glRotatef(180, 0, 0, 1);
//    glTranslatef(-1.25, -1.5, -1.25);
//    drawTrapezoid(0.412, 0.412, 0.412,  0.0,0.0,0.0);
//    glPopMatrix();

//    glPushMatrix();
//    glTranslatef(5.5, 1.5, 0);
//    glRotatef(-42, 0, 0, 1);
//    glScalef(0.1, 1.3, 1);
//    glTranslatef(-1.5, -1.5, -1.5);
//    drawCube1(0.412, 0.412, 0.412,  0.0,0.0,0.0);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-8.1, 1.5, 0);
//    glRotatef(42, 0, 0, 1);
//    glScalef(0.1, 1.3, 1);
//    glTranslatef(-1.5, -1.5, -1.5);
//    drawCube1(0.412, 0.412, 0.412,  0.0,0.0,0.0);
//    glPopMatrix();
//
//    for(float i=-6; i<=2; i+=2)
//    {
//        glPushMatrix();
//        glTranslatef(i, 0, -1.5);
//        glScalef(0.1, 1, 1);
//        drawCube1(0.412, 0.412, 0.412,  0.0,0.0,0.0);
//        glPopMatrix();
//    }

    // glEnable(GL_TEXTURE_2D);
    //glBindTexture( GL_TEXTURE_2D, ID2[3] );

//    glPushMatrix();
//    glTranslatef(-6.9, 0, 1.7);
//    glScalef(3.7, 1, 0.01);
//    drawBox();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-6.9, 0, -1.7);
//    glScalef(3.7, 1, 0.01);
//    drawBox();
//    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
}
void pirateBoat()
{
    glPushMatrix();
    glTranslatef(1, 0, 0);
    glScalef(1.3, 1, 1.3);
    ground2();
    glPopMatrix();
    //base
    //base stand
//    glPushMatrix();
//    glTranslatef(0.5, -19.5, 0);
//    //glRotatef(-105, 0, 0, 1);
//    glScalef(6,0.5,4);
//    glTranslatef(-1.5, -1.5, -1.5);
//    drawCube1(0.545,0.271,0.075,  0.2725,0.1355,0.0375);
//    glPopMatrix();

    //translate down
    glPushMatrix();
    glTranslatef(0, -5.5, 0);

    glPushMatrix();
    glTranslatef(0, 0, -4);
    glScalef(0.2, 0.2, 0.5);
    drawCylinder(1,0,0, 0.5,0,0.5);
    glPopMatrix();

    //boat body
    glPushMatrix();
    glRotatef(pirateBoatTheta, 0, 0, 1);
    glTranslatef( 1.8,-12,0);
    boatBody();
    glPopMatrix();

    glPushMatrix();
    glRotatef(pirateBoatTheta, 0, 0, 1);
    glTranslatef(-1.8,-12.4,0);
    sitmen();
    glPopMatrix();

    //stand on the front
    glPushMatrix();
    glTranslatef(0, 0, 1.4);
    glRotatef(pirateBoatTheta, 0, 0, 1);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-90, 0, 0, 1);
    glScalef(4,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //right stand
//    glPushMatrix();
//    glRotatef(-125, 0, 0, 1);
//    glScalef(4,0.28,0.1);
//    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
//    glPopMatrix();
    glPopMatrix();

    //stand on the back
    glPushMatrix();
    glTranslatef(0, 0, -1.6);
    glRotatef(pirateBoatTheta, 0, 0, 1);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-90, 0, 0, 1);
    glScalef(4,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //right stand
//    glPushMatrix();
//    glRotatef(-125, 0, 0, 1);
//    glScalef(4,0.28,0.1);
//    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
//    glPopMatrix();
    glPopMatrix();

    //base stand at the front
    glPushMatrix();
    glTranslatef(0, 0, 5);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-90, 0, 0, 1);
    glScalef(6,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //right stand
//    glPushMatrix();
//    glRotatef(-120, 0, 0, 1);
//    glScalef(6,0.28,0.1);
//    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.055);
//    glPopMatrix();
    glPopMatrix();

    //base stand at the back
    glPushMatrix();
    glTranslatef(0, 0, -5);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-90, 0, 0, 1);
    glScalef(6,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //right stand
//    glPushMatrix();
//    glRotatef(-120, 0, 0, 1);
//    glScalef(6,0.28,0.1);
//    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
//    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}


void quad1()
{
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(10,4,3);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,4,3);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,3);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(10,0,3);
    glEnd();
}

void quad2()
{
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0,8,5);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,8,0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0,0,5);
    glEnd();
}

//
//void icecreamParlor()
//{
//    materialProperty();
//    glEnable(GL_TEXTURE_2D);
//
//    glBindTexture(GL_TEXTURE_2D,ID2[16]);
//    glPushMatrix();
//    quad1();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(0, 11, -2);
//    glRotatef(90, 1, 0, 0);
//    glScalef(1, 1.5, 1);
//    quad1();
//    glPopMatrix();
//
//    //glBindTexture(GL_TEXTURE_2D,ID2[17]);
//    glPushMatrix();
//    glTranslatef(0, 0, -5);
//    glScalef(1, 2, 1);
//    quad1();
//    glPopMatrix();
//
//    //glBindTexture(GL_TEXTURE_2D,ID2[18]);
//
//    glPushMatrix();
//    glTranslatef(0, 0, -2);
//    quad2();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(10, 0, -2);
//    quad2();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(0, 3, -2);
//    glRotatef(90, 1, 0, 0);
//    quad1();
//    glPopMatrix();
//
//    //glBindTexture(GL_TEXTURE_2D,ID2[5]);
//    glPushMatrix();
//    glTranslatef(0, 6, 1);
//    glScalef(1, 0.5, 1);
//    quad1();
//    glPopMatrix();
//
//    //glDisable(GL_TEXTURE_2D);
//
//
//}
//
void chairr()
{
    //seat part
    glPushMatrix();
    glScalef(0.5, 0.05, 0.5);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat left back
    glPushMatrix();
    glTranslatef(0, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat right back
    glPushMatrix();
    glTranslatef(1.35, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat left front leg
    glPushMatrix();
    glTranslatef(0, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat right front leg
    glPushMatrix();
    glTranslatef(1.35, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

}
void icecreamParlor()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,2);
    glPushMatrix();
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 11, -2);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1.5, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,4);

    glPushMatrix();
    glTranslatef(0, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, -2);
    glRotatef(90, 1, 0, 0);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(0, 6, 1);
    glScalef(1, 0.5, 1);
    quad1();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


}
void tablee()
{
    //table
    glPushMatrix();
    glScalef(4, 0.3, 4);
    drawSphere(0.8,0.4,0.00,  0.4,0.2,0);
    glPopMatrix();

    //stand
    glPushMatrix();
    glScalef(0.1, -1, -0.1);
    drawCube1(0,0,0, 0,0,0.5);
    glPopMatrix();

    //stand bottom
    glPushMatrix();
    glTranslatef(0, -2.8, 0);
    glScalef(1, 0.2, 1);
    drawSphere(1,0.549,0.00,  0.5,0.2745,0);
    glPopMatrix();
}
void cylinder(GLint c1, GLint c2,GLint c3, GLboolean emission=false)
{

    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {r,g,b,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    const double PI = 3.14159;

    /* top triangle */
    double i, resolution  = 0.1;
    double height = 1;
    double radius = 0.5;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    //top Circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(0, height, 0);  /* center */
    for (i = 2 * PI; i >= 0; i -= resolution)

    {
        glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to 0 degrees */
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(radius, height, 0);
    glEnd();


    //bottom Circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(0, 0, 0);  /* center */
    for (i = 0; i <= 2 * PI; i += resolution)
    {
        glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
        glVertex3f(radius * cos(i), 0, radius * sin(i));
    }
    glEnd();



    //cylinder side
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= 2 * PI; i += resolution)
    {
        const float tc = ( i / (float)( 2 * PI ) );
        glTexCoord2f( tc, 0.0 );
        glVertex3f(radius * cos(i), 0, radius * sin(i));
        glTexCoord2f( tc, 1.0 );
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to zero degrees */
    glTexCoord2f( 0.0, 0.0 );
    glVertex3f(radius, 0, 0);
    glTexCoord2f( 0.0, 1.0 );
    glVertex3f(radius, height, 0);
    glEnd();

    glPopMatrix();


}
void diningSet()
{
    glPushMatrix();
    glTranslatef(0, -16, 0);
    tablee();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-8.8,0);
    glRotatef(90,-1,0,0);
    glutWireCone(7,3,10,1000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-11,0);
    glScalef(.3,10,.3);
    cylinder(255,255,255);
    glPopMatrix();

    for(int i = 0; i <= 360; i+=72)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);
        glTranslatef(0, -17, -4);
        chairr();
        glPopMatrix();
    }
}
static GLfloat cube2[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.75, -1.0},
    {-1.0, 1.75, -1.0},

};
void drawcube2(GLint c1, GLint c2, GLint c3, GLboolean emission = false)
{

    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {r,g,b,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);




    for (GLint i = 0; i <6; i++)
        for (GLint i = 0; i <6; i++)
        {
            glBegin(GL_QUADS);

            glVertex3fv(&cube2[quadIndices[i][0]][0]);
            glTexCoord2f(1,1);
            glVertex3fv(&cube2[quadIndices[i][1]][0]);
            glTexCoord2f(1,0);
            glVertex3fv(&cube2[quadIndices[i][2]][0]);
            glTexCoord2f(0,0);
            glVertex3fv(&cube2[quadIndices[i][3]][0]);
            glTexCoord2f(0,1);
            glEnd();
        }

}
void trashLid()
{

    glPushMatrix();
    glTranslatef(0,2.8,0);
    glRotatef(14.036,1,0,0);
    glScalef(3.1,.2,3.1);
    drawcube(68,76,81);
    glPopMatrix();
}

void trash()
{

    glPushMatrix();
    glTranslatef(-3,0,0);
    glScalef(.2,2,3);
    drawcube2(30,85,41);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3,0,0);
    glScalef(.2,2,3);
    drawcube2(30,85,41);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2.8);
    glScalef(2.8,2,.2);
    drawcube(26,72,34);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,.75,-2.8);
    glScalef(2.8,2.75,.2);
    drawcube(26,72,34);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-1.8,0);
    glScalef(2.8,.2,2.8);
    drawcube(147,159,159);
    glPopMatrix();


    //trash lid
    glPushMatrix();
    glTranslatef(0,2.8,-3.1);
    glRotatef(lidTheta, 1,0,0);
    glTranslatef(0,-2.8,3.1);
    trashLid();
    glPopMatrix();


    //pivot

    glPushMatrix();
    glTranslatef(-2.2, 3.4,-3.25);
    glRotatef(90,0,0,1);
    glScalef(.5,1,.5);
    cylinder(209,217,216);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(2.2, 3.4,-3.25);
    glRotatef(90,0,0,1);
    glScalef(.5,1,.5);
    cylinder(209,217,216);
    glPopMatrix();



}
void icecreamRod()
{
    glPushMatrix();
    glPushMatrix();
    //glTranslatef( 39.4,8,2.6);
    glScalef(3,0.2,0.2);
    drawcube(40,40,40);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.8,-0.4,0);
    glRotatef(90,1,0,0);
    //glScalef(3,0.2,0.2);
    glutSolidCone(0.2,1,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 2.8,-0.4,0);
    //glRotatef(90,1,0,0);
    glScalef(0.2,0.2,0.2);
    drawSphere(1,1,1,0,0,0);

    glPopMatrix();

    glPopMatrix();
}
void tripod_side()
{


    glPushMatrix();
    glTranslatef( 0.2,-0.5,0);
    glRotatef(30,0,0,1);
    glScalef(0.1,0.7,0.1);
    cylinder(240,245,240);

    glPopMatrix();
}
void tripod()
{
    glPushMatrix();
    //glRotatef(30,0,0,1);
    glScalef(0.1,2,0.1);
    cylinder(240,245,240);

    glPopMatrix();

    glPushMatrix();
    tripod_side();

    glPopMatrix();
    glPushMatrix();
//    glTranslatef(ttx,tty,ttz);
//    glRotatef(120,0,1,0);
//    glRotatef(30,0,0,1);
    glTranslatef(ttx,tty,ttz);
    glTranslatef( 0.2,-0.5,0);
//    glScalef(0.1,0.7,0.1);
//    cylinder(240,245,240);
    glRotatef(120,0,1,0);
    glTranslatef( -0.2,0.5,0);
    tripod_side();

    glPopMatrix();

//      glPushMatrix();
//    glTranslatef( 0.2,-0.5,0);
//    glRotatef(240,0,1,0);
//    glRotatef(30,0,0,1);
//    glScalef(0.1,0.7,0.1);
//    cylinder(240,245,240);
//
//    glPopMatrix();

//    glPushMatrix();
//    glRotatef(120,0,1,0);
//    glScalef(0.1,0.7,0.1);
//    cylinder(240,245,240);
//    glPopMatrix();
}
void sound_box()
{
    glPushMatrix();

    glPushMatrix();
    glTranslatef(-5.9,27,-1.5);
    glScalef(1.3,2.3,1.3);
    drawcube(168, 168, 168);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.6,27.6,-1.5);
    glRotatef(90,0,0,1);
    glScalef(0.8,0.1,0.8);
    cylinder(10,8, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 0,-1.8,0);
    glTranslatef(-4.6,27.6,-1.5);
    glRotatef(90,0,0,1);
    glScalef(0.8,0.1,0.8);
    cylinder(10,8, 8);
    glPopMatrix();

    glPopMatrix();

}
void roads()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    for(int i =0; i<100; i++)
    {
        glPushMatrix();
        glTranslatef(0,.5,i*20);
        glScalef(1,.2,7);
        drawcube(255,255,255);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0,.5,-i*20);
        glScalef(1,.2,7);
        drawcube(255,255,255);
        glPopMatrix();
    }





    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,200);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-200);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,400);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-400);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,600);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-600);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,800);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-800);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1000);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1000);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1200);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1200);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1400);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1400);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1600);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1600);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1800);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1800);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void elevator()
{

    glPushMatrix();

    glPushMatrix();
    glScalef(2,0.08,2);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef( -1.9,2,0);
    glScalef(0.08,2,2);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef( 1.9,2,0);
    glScalef(0.08,2,2);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 0,4,0);
    glScalef(2,0.08,2);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 1.5,2,-1.8);
    glScalef(0.1,2,0.1);
    drawcube(0,30,250);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(  -0.7,0,0);
    glTranslatef( 1.5,2,-1.8);
    glScalef(0.1,2,0.1);
    drawcube(0,30,250);
    glPopMatrix();


    glPushMatrix();
    glTranslatef( -1.5,0,0);
    glTranslatef( 1.5,2,-1.8);
    glScalef(0.1,2,0.1);
    drawcube(0,30,250);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -2.4,0,0);
    glTranslatef( 1.5,2,-1.8);
    glScalef(0.1,2,0.1);
    drawcube(0,30,250);
    glPopMatrix();

    //door
    glPushMatrix();
    glTranslatef( 0,1,1.9);
    glScalef(1.9,0.1,0.08);
    drawcube(30,40,240);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 0,5,0);
    glScalef(0.08,1,0.08);
    drawcube(20,40,40);
    glPopMatrix();

    glPopMatrix();

}

void tower()
{

    glPushMatrix();

    glPushMatrix();
    glTranslatef(-127.5,31.5,-10.4);
    glScalef(0.8,32,0.8);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-127.5,60.5,-10.4);
    glScalef(0.8,0.8,3);
    drawcube(255,255,255);
    glPopMatrix();

    glPopMatrix();
}

void wiree()
{
    glPushMatrix();
    glTranslatef( 0,60.8,-7.6);
    glScalef(200,0.1,0.1);
    drawcube(20,20,20);


    glPopMatrix();


}

void circle_3D(GLdouble radius)
{
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);

    glRotatef(270, 1, 0, 0);
    gluSphere(qobj, radius, 20, 20);
    gluDeleteQuadric(qobj);

}
void cylinder_3D(GLdouble height, GLdouble rad, GLdouble radd)
{
    GLUquadric* qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glRotatef(90, 1, 0, 0);

    gluCylinder(qobj, rad, radd, height, 20, 20);
    gluDeleteQuadric(qobj);
}


void sub_tree()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(0,40,0);
    cylinder_3D(25,1,1);//base
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glTranslatef(0,40,0);
    circle_3D(10); //leaf
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void sub_tree_upper()
{
    glPushMatrix();
    glTranslatef(0,90,0);
    glRotatef(90,0,1,0);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,88,0);
    glRotatef(10,1,0,0);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,88,0);
    glRotatef(-10,1,0,0);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,90,0);
    glRotatef(10,0,0,1);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,90,0);
    glRotatef(-10,0,0,1);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();
}
void tree()
{

//11111111111111111111111111111111111111


    glPushMatrix();
    glTranslatef(0,95,-8);
    glRotatef(55,1,0,0);
    glScalef(0.7,0.7,0.7);
    sub_tree();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,95,8);
    glRotatef(-55,1,0,0);
    glScalef(0.7,0.7,0.7);
    sub_tree();  //1
    glPopMatrix();


//3333333333333333333333333

    glPushMatrix();
    sub_tree_upper();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,10,0);
    glScalef(0.8,1,0.8);
    sub_tree_upper();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,120,0);
    glBindTexture(GL_TEXTURE_2D,9);
    cylinder_3D(80,4,8);  //tree base
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void toster()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::toasterr);

    glPushMatrix();
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void toster_line()
{
    glPushMatrix();
    drawcube(0,0,0);
    glPopMatrix();
}
void toster_ruti()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::ruti);
    glPushMatrix();
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void coffee_up()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::cup_coffee);
    glPushMatrix();
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void coffee_pipe()
{
    glPushMatrix();
    drawcube(255,255,255);
    glPopMatrix();
}
void coffee_water()
{
    glPushMatrix();
    draw_sphere(103,71,54);
    glPopMatrix();
}

void icecreammen()
{

    glPushMatrix();
    glRotatef(90,0,1,0);
    glScalef(0.14,0.14,0.14);
    // Left Leg
    glPushMatrix();
    glTranslatef( -5,0,0);
    //glRotatef(30,1,0,0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glTranslatef( 5,0,0);
    // glRotatef(30,1,0,0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(0, 22.5, 0);
    glScalef(6, 15, 0.1);
    DrawCube(255, 0, 255);
    glPopMatrix();

    // Neck
    glPushMatrix();
    glTranslatef(0, 40, 0);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(0, 45, 0);
    glScalef(5, 5, 5);
    draw_sphere(20, 20, 240);
    glPopMatrix();

    // Left Arm
    glPushMatrix();
    glTranslatef(-7.5, 32.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 25, 0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glTranslatef(7.5, 32.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 32.5, -7.5);
    glRotatef(90,1,0,0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();


//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, Textures::smile);
//    glPushMatrix();
//    glTranslatef( 10.3,34,-12.2);
//    draw_cupp(255,255,255);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

    // Ball in right hand
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_shininess[] = { 0 };
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//
//    glPushMatrix();
//    glTranslatef(ballX, ballY, ballZ);
//    glScalef(2.5, 2.5, 2.5);
//    glutSolidSphere(1, 20, 20);
//    glPopMatrix();
    glPopMatrix();
}
static void Bowler()
{
    glPushMatrix();
    // Left Leg
    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glTranslatef(5, 0, 0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(0, 22.5, 0);
    glScalef(6, 15, 0.1);
    DrawCube(255, 0, 255);
    glPopMatrix();

    // Neck
    glPushMatrix();
    glTranslatef(0, 40, 0);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(0, 45, 0);
    glScalef(5, 5, 5);
    draw_sphere(20, 20, 240);
    glPopMatrix();

    // Left Arm
    glPushMatrix();
    glTranslatef(-7.5, 32.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 25, 0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glTranslatef(7.5, 32.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 32.5, -7.5);
    glRotatef(90,1,0,0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures::smile);
    glPushMatrix();
    glTranslatef( 10.3,34,-12.2);
    draw_cupp(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Ball in right hand
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_shininess[] = { 0 };
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//
//    glPushMatrix();
//    glTranslatef(ballX, ballY, ballZ);
//    glScalef(2.5, 2.5, 2.5);
//    glutSolidSphere(1, 20, 20);
//    glPopMatrix();
    glPopMatrix();

}
static void Bowlerr()
{
    glPushMatrix();
    // Left Leg
    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glTranslatef(5, 0, 0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(0, 22.5, 0);
    glScalef(6, 15, 0.1);
    DrawCube(255, 0, 255);
    glPopMatrix();

    // Neck
    glPushMatrix();
    glTranslatef(0, 40, 0);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(0, 45, 0);
    glScalef(5, 5, 5);
    draw_sphere(20, 20, 240);
    glPopMatrix();

    // Left Arm
    glPushMatrix();
    glTranslatef(-7.5, 32.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 25, 0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glTranslatef(7.5, 32.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 5, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 32.5, -7.5);
    glRotatef(90,1,0,0);
    glScalef(1, 15, 1);
    Cylinder(115, 60, 45);
    glPopMatrix();


//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, Textures::smile);
//    glPushMatrix();
//    glTranslatef( 10.3,34,-12.2);
//    draw_cupp(255,255,255);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

    // Ball in right hand
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_shininess[] = { 0 };
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//
//    glPushMatrix();
//    glTranslatef(ballX, ballY, ballZ);
//    glScalef(2.5, 2.5, 2.5);
//    glutSolidSphere(1, 20, 20);
//    glPopMatrix();
    glPopMatrix();

}
void human()
{


    glPushMatrix();
    glTranslatef(6,1.1,humanz);
    glScalef(0.1,0.1,0.1);
    Bowler();
    glPopMatrix();

}
void humann()
{


    glPushMatrix();
    glTranslatef( -10.1,25.6,-3.8);
    glScalef(0.1,0.1,0.1);
    Bowlerr();
    glPopMatrix();

}

void sphere2(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluQuadricTexture(qobj,1);
    gluSphere(qobj,10,25,25);
}
void draw_all()
{
    glPushMatrix();
//    glTranslatef(0,-30,-25);
    draw_room();
    glPopMatrix();

    glPushMatrix();
//    glTranslatef(0,-30,-25);
    glTranslatef(doorDistx1, 0, 0);
    door();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(doorDistx2, 0, 0);
    glTranslatef( 4.8,0,0);
    door();
    glPopMatrix();
//
//    glPushMatrix();
////    glTranslatef(0,-30,-25);
//    draw_cabinet();
//    glPopMatrix();

//
//    glPushMatrix();
////    glTranslatef(0,-30,-25);
//    draw_basin();
//    glPopMatrix();

//
//    glPushMatrix();
////    glTranslatef(0,-30,-25);
//    draw_shelf();
//    glPopMatrix();


//    glPushMatrix();
////    glTranslatef(14,0,-13);
////    glRotatef( alpha,axis_x, axis_y, axis_z );
////    glRotatef( theta, axis_x, axis_y, axis_z);
////    glRotatef(beta, axis_x, axis_y, axis_z);
////    glTranslatef(-14,0,13);
//    draw_fridge();
//
//
//    glPopMatrix();


//    glPushMatrix();
//    draw_switch();
//    glPopMatrix();
//
//
//    glPushMatrix();
//    draw_racks();
//    glPopMatrix();


//    glPushMatrix();
//    draw_kettle();
//    glPopMatrix();
//
//    glPushMatrix();
//    draw_stove();
//    glPopMatrix();


    glPushMatrix();
    //glTranslatef(ttx,tty,ttz);
    draw_fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.5,16,-19.7);
    glRotatef(theta_fan_rotate, 0.0, 0.0, 1.0);
    glTranslatef(+15.5,-16,+19.7);
    fan_blade();
    glPopMatrix();



    glPushMatrix();
    draw_bulb();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-17, 15.3, -7);
    glScalef(.2,.2,.2);
    draw_Sphere(1,1,1, light_0_on);

    glPopMatrix();
    glPushMatrix();

    //glTranslatef(ttx,tty,ttz);
    table();
    glPopMatrix();
    glPushMatrix();

    glTranslatef( 22.6,0,0);
    table();
    glPopMatrix();
    glPushMatrix();

    glTranslatef(0,0,19.8);
    table();
    glPopMatrix();
    glPushMatrix();

    glTranslatef( 22.6,0,19.8);
    table();
    glPopMatrix();

    glPushMatrix();
    human();
    glPopMatrix();

    glPushMatrix();
    humann();
    glPopMatrix();


//    glPushMatrix();
//    glTranslatef(ttx,tty,ttz);
//    glRotatef(95, 0, 1, 0);
//    legs();
//    glPopMatrix();
    glPushMatrix();
    glRotated(95, 0, 1, 0);
    glPopMatrix();

    glPushMatrix();
    fan_s();
    glPopMatrix();

    glPushMatrix();
    fan_handle_s();
    glPopMatrix();
    glPushMatrix();
    upper_light();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 24.6,0,0);
    upper_light2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 24.6,0,17.6);
    upper_light3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.27676e-15,0,-39);
    draw_room2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8.2,2.2,-17);
    tap_water();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,0,-20.2);
    draw_basin();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-6.8,0,0.6);
    glScalef(0.4,0.4,0.4);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,0,-5.6);
    glScalef(0.4,0.4,0.4);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.2,0,19);
    glScalef(0.4,0.4,0.4);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.2,0,14.2);
    glScalef(0.4,0.4,0.4);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16,0,-0.4);
    glScalef(0.4,0.4,0.4);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.2,0,-5.8);
    glScalef(0.4,0.4,0.4);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -12,0,44);
    glScalef(0.4,0.4,0.4);
    chair();
    glPopMatrix();


    glPushMatrix();
    glTranslatef( -3.6,0,44.6);
    glScalef(0.4,0.4,0.4);
    chair();
    glPopMatrix();

//    glPushMatrix();
//    sky();
//    glPopMatrix();

    glPushMatrix();
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 2,0,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 4,0,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 6,0,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 8,0,0);
    fence();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 10,0,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 12,0,0);
    fence();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25,0,2.4);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( -25,0,4.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( -25,0,6.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,2.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,4.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,6.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,8.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,10.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,12.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,14.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,16.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,18.6);
    glRotatef(90,0,1,0);
    fence();
    glPopMatrix();
    glPushMatrix();

    desk();
    glPopMatrix();


    glPushMatrix();
    rooftop_room();

    glPopMatrix();

    glPushMatrix();
    glTranslatef( 41.2,0,-5);
    shiri();
    glPopMatrix();

//    glPushMatrix();
//    glTranslatef(ttx,tty,ttz);
//    glRotatef(180,0,1,0);
//    shiri();
//    glPopMatrix();

    glPushMatrix();

    firstFloorFence();
    glPopMatrix();

    // glPopMatrix();
//    glPushMatrix();
//
//    glTranslatef( 24.6,20.4,-38.8);
//    table();
//    glPopMatrix();
//
//    glPushMatrix();
//
//    glTranslatef( 24.6,20.4,-21.8);
//    table();
//    glPopMatrix();
//
//    glPushMatrix();
//
//    glTranslatef( 24.6,20.4,-4.8);
//    table();
//    glPopMatrix();
//
//    glPushMatrix();
//
//    glTranslatef( 24.6,20.4,13.8);
//    table();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(17,20.2,15.2);
//    glScalef(0.4,0.4,0.4);
//    chair();
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(17,20.2,-3.2);
//    glScalef(0.4,0.4,0.4);
//    chair();
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(17,20.2,-20.2);
//    glScalef(0.4,0.4,0.4);
//    chair();
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(17,20.2,-38.2);
//    glScalef(0.4,0.4,0.4);
//    chair();
//    glPopMatrix();

    glPushMatrix();

    glTranslatef(-88.1,4.4,0+carz);
    glRotatef(90,0,1,0);
    glScalef(0.2,0.2,0.2);
    car(0,0,1,1,0,0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(12.2,19,40.2);
    //glScalef(0.1,0.1,0.1);
    pirateBoat();
    glPopMatrix();

//    glPushMatrix();
//    glTranslatef( 10.4,1,40.4);
//    glRotatef(90,0,1,0);
//    glScalef(0.1,0.1,0.1);
//    sitmen();
//    glPopMatrix();


    glPushMatrix();
    glTranslatef( 12,46.8,9.2);
    glScalef(1.4,1.4,1.4);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 12,46.8,-11.2);
    glScalef(1.4,1.4,1.4);
    diningSet();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 12,46.8,-31.2);
    glScalef(1.4,1.4,1.4);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 12,46.8,-51.2);
    glScalef(1.4,1.4,1.4);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -6.4,1,-16);
    glScalef(0.5,0.5,0.5);
    trash();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.88578e-16,21.2,16.6);
    glScalef(0.5,0.5,0.5);
    trash();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(31,0,7.8);
    glRotatef(90,0,1,0);
    glScalef(1.9,1.9,1.9);
    icecreamParlor();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(39.4+icex,8.2,3.6);
    // glRotatef(90,0,1,0);
    //glScalef(1.9,1.9,1.9);
    glRotatef(ice, 1,0,0);
    icecreamRod();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 43.8,1.0,4.1);
    // glRotatef(90,0,1,0);
    //glScalef(1.9,1.9,1.9);
    icecreammen();
    glPopMatrix();


    glPushMatrix();
    sound_box();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-32.9);
    sound_box();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -97.7,0,0);
    roads();
    glPopMatrix();


    glPushMatrix();
    glTranslatef( -31.8+cablex,54.8,-7.6);
    elevator();
    glPopMatrix();

    glPushMatrix();

    tower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 271.4,0,0);
    tower();
    glPopMatrix();

    glPushMatrix();

    wiree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -70,-8,-28.6);
    glScalef(0.2,0.2,0.2);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -70,-8,18.6);
    glScalef(0.2,0.2,0.2);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -70,-8,65.8);
    glScalef(0.2,0.2,0.2);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -70,-8,113);
    glScalef(0.2,0.2,0.2);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 37.1,-3,-3.2);
    glPushMatrix();
    glTranslatef( -18.6,10.6,-44.2);
    glScalef(1.5,1.2,0.8);
    toster();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-18.4,11.8,-44.8);
    glScalef(0.8,0.2,0.01);
    toster_line();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-18.4,11.8+tosterY,-44.8);
    glScalef(0.8,0.3,0.01);
    toster_ruti();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18.4,11.8,-43.8);
    glScalef(0.8,0.2,0.01);
    toster_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18.4,11.8+tosterY,-43.8);
    glScalef(0.8,0.3,0.01);
    toster_ruti();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef( 21.9,0,0);
    glPushMatrix();
    glTranslatef(-11.6,12,-21);
    glScalef(2,2.5,1);
    coffee_up();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.6,6,-21);
    glScalef(2,1,1);
    coffee_up();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.6,10,-21.2);
    glScalef(0.1,1,0.1);
    coffee_pipe();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.6,10+waterY,-21.2);
    glScalef(.1,.1,.1);
    coffee_water();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.8,7.4,-21);
    draw_cup(255,255,255);
    glPopMatrix();

    glPopMatrix();


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(300+sunx,suny,-800);
    glScalef(4,4,4);
    glBindTexture(GL_TEXTURE_2D,t);
    sphere2(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glRotatef(nightTheta,0,0,1);
    glRotatef(skyTheta, 0,1,0);
    glRotatef(90,0,0,1);
    glScalef(100,100,100);
    glBindTexture(GL_TEXTURE_2D,t2);
    sphere2(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);






}
int state = 1;
vec3 color = { 0.8, 0.8, 0.8 };
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    glFrustum(-10, 10, -10, 10, 4, 200);
    gluPerspective(60,1,5,200000);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upx, upy, upz);
    glViewport(0,0, windowHeight, windowWidth);
    glScalef(scale_x, scale_y, scale_z);
    glRotatef( alpha,axis_x, axis_y, axis_z );
    glRotatef( theta,axis_x, axis_y, axis_z );
    glRotatef( beta,axis_x, axis_y, axis_z );

//
//
    glPushMatrix();

    draw_all();
    glPopMatrix();
//
//    glPushMatrix();
//
//    sitmen();
//    glPopMatrix();


//    glPushMatrix();
//
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { 1, 1, 1, 1.0 };
//    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = {60};
//
//    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
//
//
//    //sun.model = load_obj(".\\objects\\spear.obj");
//    //C:\Users\dipto\OneDrive\Desktop\LAb_project\3DExample1\objects
//    glTranslatef(20,10,30);
//    glScalef(5,5,5);
//    sun.model = load_obj("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\3DExample1\\objects\\spear.obj");
//    sun.position.x = sun.position.y = sun.position.z = 0.0;
//    sun.texture = get_texture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\3DExample1\\textures\\sun.tga");
//    drawObj(sun.model, sun.texture, color);
//    glPopMatrix();


//    glPushMatrix();
//    drawcube(50,50,50);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(0.1,20,0.1);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(20,0.1,0.1);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glScalef(0.1,0.1,20);
//    drawcube(50,50,50);
    glPopMatrix();

    light(-17, 15.3, -7,GL_LIGHT0, light_0_on, false);
    light2(-12,12,-12.8, GL_LIGHT3, light_3_on, false);
    //light1(300+sunx,suny,-800,GL_LIGHT0, light_1_on, true,1,1,1);


    glFlush();
    glutSwapBuffers();
}



void init(int d)
{
    if(d!=f)
    {
        angleYaw = 90.0;
        anglePitch = 90.0;
        angleRoll = 90.0;
        eyeX = 0;
        eyeY = 3;
        eyeZ = 80;
        lookX = 0;
        lookY = 0;
        lookZ = 50;
        upx = 0;
        upy = 1;
        upz = 0;
        f=d;
        scale_x=1;
        scale_y=1;
        scale_z=1;
    }
//     b_swap();
}


void setCameraEye_Yaw()
{

//    init(1);
//    f = 1;
    std::cout<<"before-----------"<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;
    lookX = 50.0*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookZ = 50.0*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
    std::cout<<"after============="<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;
//    std::cout<<angleYaw<<std::endl;
//    (cos(anglePitch*3.1416/180.0))
}

void setCameraEye_Roll()
{

    upx = (cos(angleRoll*3.1416/180.0));
    upy = (sin(angleRoll*3.1416/180.0));

}

void setCameraEye_Pitch()
{
//    init(3);
//    f=3;
    std::cout<<"before-----------"<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;
    lookX = 50.0*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookY = 50.0*(sin(anglePitch*3.1416/180.0));
    lookZ = 50.0*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
    std::cout<<"after============="<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;

}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case 'l':
        if(anglePitch<anglePitchLimit1)
        {
            anglePitch += roll_value;
            setCameraEye_Pitch();
        }


        glutPostRedisplay();

        break;
    case 'j':
        if(anglePitch>anglePitchLimit2)
        {
            anglePitch -= roll_value;
            setCameraEye_Pitch();
        }

        glutPostRedisplay();
        break;
    case 'i':
        if(angleYaw<angleYawLimit1)
        {
            angleYaw += roll_value;
            setCameraEye_Yaw();
        }

        glutPostRedisplay();

        break;
    case 'k':
        if(angleYaw>angleYawLimit2)
        {
            angleYaw -= roll_value;
            setCameraEye_Yaw();
        }

        glutPostRedisplay();
        break;
    case 'o':

        angleRoll += roll_value;
        printf("%lf\n", angleRoll);
        setCameraEye_Roll();
        glutPostRedisplay();


        break;
    case 'u':
        angleRoll -= roll_value;
        setCameraEye_Roll();
        glutPostRedisplay();

        break;





    case 'q':
    case 'Q':
        bRotate = !bRotate;
        uRotate = false;
        tRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0.0;
        glutPostRedisplay();
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        tRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        glutPostRedisplay();
        break;

    case 't':
    case 'T':
        tRotate = !tRotate;
        uRotate = false;
        bRotate = false;
        axis_x=0.0;
        axis_y=0.0;
        axis_z=1.0;
        glutPostRedisplay();
        break;

    case 'w':
    case 'W':
        eyeY++;
        lookY++;
        glutPostRedisplay();
        break;
    case 's':
    case 'S':
        eyeY--;
        lookY--;
        glutPostRedisplay();
        break;
    case '+':
        eyeZ++;
        lookZ++;
        glutPostRedisplay();
        break;
    case '-':
        eyeZ--;
        lookZ--;
        glutPostRedisplay();
        break;

    case 'd':
    case 'D':
        eyeX++;
        lookX++;
        glutPostRedisplay();
        break;
    case 'a':
    case 'A':
        eyeX--;
        lookX--;
        glutPostRedisplay();
        break;

    case 'z':
    case 'Z':
        //eyez-=2;
        //init(4);
        f=4;
        scale_x+=0.05;
        scale_y+=0.05;
        scale_z+=0.05;
        glutPostRedisplay();
        break;
    case 'c':
    case 'C':
        //eyez-=2;
        //init(4);
        f=4;
        if(scale_x==0.05)break;
        scale_x-=0.05;
        scale_y-=0.05;
        scale_z-=0.05;
        glutPostRedisplay();
        break;
    //light 1 toggle
    case '1':
        light_0_on = !light_0_on;
        break;

    case '4':
        fan_Rotate = !fan_Rotate;
        break;
    case 'v':
        tty -= 0.2;
        break;
    case 'b':
        tty += 0.2;
        break;

    case'g':
        //glutIdleFunc(reverse);
        sentinel = 1;
        break;

    case'f':
            glutIdleFunc(NULL);
        break;
    case ';':
        humanMove = !humanMove;
        break;
    case ':':
        PlaySound(TEXT("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\Car Racing Sound Effect ! Formula 1 Car Sound ! Free Sound Effects.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

        carMove = !carMove;
        break;
    case '#':
        //PlaySound(TEXT("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\Car Racing Sound Effect ! Formula 1 Car Sound ! Free Sound Effects.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

        cableMove = !cableMove;
        break;
    case '9':
        light_3_on = !light_3_on;
        break;
    case '[':
        doorOpen = true;
        doorClose=false;
        break;
    case '{':
        doorOpen = false;
        doorClose=true;

        break;
    case ']': //pirate boat
        if(pirateBoatFlag == false)
        {
            pirateBoatFlag = true;
            break;
        }
        else if( pirateBoatFlag == true)
        {
            pirateBoatFlag = false;
            break;
        }

        break;
    case '(':
        lidOpen = true;
        lidClose = false;
        break;
    case ')':
        lidOpen = false;
        lidClose = true;
        break;

    case '!':
        PlaySound(TEXT("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\Ice Cream - Turkish Song.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);


        iceon = true;
        iceoff = false;
        break;
    case '*':
        iceon = false;
        iceoff = true;

        break;

    case '&':
        PlaySound(TEXT("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\Jungkook – Dreamers (FIFA World Cup 2022).wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        break;
    case 'n':
        toPlay = true;
        toPause = false;
        break;
    case 'm':
        toPlay = false;
        toPause = true;
        break;
    case 'N':
        waterplay = false;
        waterpause = true;
        break;
    case 'M':
        waterplay = true;
        waterpause = false;
        break;
    case 'x':
        skyRotate=!skyRotate;
        break;

    case 27:	// Escape key
        exit(1);
    }
}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        ttz -= 0.1;
        break;
    case GLUT_KEY_DOWN:
//do something here
        ttz += 0.1;
        break;
    case GLUT_KEY_LEFT:
//do something here
        ttx -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
//do something here
        ttx += 0.1;
        break;
    }
    std:: cout<<"Starting Point "<<ttx<<","<<tty<<","<<ttz<<" \n";

    glutPostRedisplay();
}

void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);

    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);

    }

    if (tRotate == true)
    {
        beta += 0.2;
        if(beta > 360.0)
            beta -= 360.0*floor(beta/360.0);

    }


    if(humanMove==true)
    {

        if(moveState==true)
        {
            if(humanz>-5)
            {

                humanz-=.05;
                std::cout << humanz << std::endl;
                if(int(humanz)==-5)
                {
                    GLint counter = 5;

                    moveState = false;
//                    glRotatef(180, 0,1,0);
                }
            }
        }


        else if(moveState==false)
        {
            if(humanz<16.5)
            {
                humanz+=.05;
                if(humanz==16.5)
                {
                    moveState = true;
//                    glRotatef(180, 0,1,0);
                }
            }
        }



    }
    if(iceon == true)
    {
        if(ice>-180)
        {
            ice-=1.0;
            icex-=.025;
        }

    }
    if(iceoff == true)
    {
        if(ice<0)
        {
            ice+=1.0;
            icex+=0.025;
        }
    }
    if (carMove == true)
    {
        if(carz>-1800)
        {
            carz-=0.8;
        }
    }
    if (cableMove == false)
    {
        if(cablex>-170)
        {
            cablex-=0.8;
            if(cablex<=-170)
            {
                cablex = 170;
            }
        }
    }
    if(toPlay == true)
    {
        if(tosterY<0.5)
        {
            tosterY = tosterY + 0.01;
        }
    }
    if(toPause == true)
    {
        if(tosterY>0)
        {
            tosterY = tosterY-0.01;
        }
    }
    if(waterplay == true)
    {
        if(waterY>-2)
        {
            waterY -= .05;
        }
        else
        {
            waterY = 0;
        }
    }
    if(waterpause == true)
    {
        if(waterY<0)
        {
            waterY = waterY+0.2;
        }
    }


    if(lidOpen == true)
    {
        if(lidTheta>-90)
        {
            lidTheta-=1.0;
        }
    }
    if(lidClose == true)
    {
        if(lidTheta<0)
        {
            lidTheta+=1.0;
        }
    }
    if(pirateBoatFlag == true)
    {
        if(pirateBoatCheck == true)
        {
            pirateBoatTheta += 2;
            if(pirateBoatTheta == 60)
            {
                pirateBoatCheck = false;
            }
        }
        else
        {
            pirateBoatTheta -= 2;
            if(pirateBoatTheta == -70)
            {
                pirateBoatCheck = true;
            }
        }
    }
    else
    {
        if(pirateBoatTheta < 0)
        {
            pirateBoatTheta += 1;
            if(pirateBoatTheta == 0)
            {
                pirateBoatTheta = 0;
            }
        }
        else if(pirateBoatTheta > 0)
        {
            pirateBoatTheta -= 1;
            if(pirateBoatTheta == 0)
            {
                pirateBoatTheta = 0;
            }
        }
    }
    if(doorOpen == true)
    {




        if(doorDistx1>-4.7) doorDistx1-=.05;

        if(doorDistx2<4.7) doorDistx2+=.05;

    }


    if(doorClose == true)
    {


        if(doorDistx1<0) doorDistx1+=.05;

        if(doorDistx2>0) doorDistx2-=.05;


    }
    if(skyRotate == true)
    {

        if(night==false)
        {
            if(sunx>-500)
            {
                if(suny<500)
                {
                    sunx--;
                    suny++;
                }
            }
            else if(suny>0)
            {
                sunx--;
                if(sunx==-750) t2=24;
                suny--;
            }
            if(suny==0)
            {
                night = true;
                t = 21;
                t2 = 23;
                sunx=0;
                suny=0;
            }
//
        }
        if(night==true)
        {
            if(sunx>-500)
            {
                if(suny<500)
                {
                    sunx--;
                    suny++;
                }
            }
            else if(suny>0)
            {
                sunx--;
                suny--;
            }
            if(suny==0)
            {
                night = false;
                t = 20;
                t2 = 22;
                sunx=0;
                suny=0;
            }
        }

        if(skyTheta<360)
        {
            skyTheta++;
        }
        else
        {
            skyTheta=0.0;
        }
    }
    if (fan_Rotate == true)
    {
        theta_fan_rotate += 2.0;
        if(theta_fan_rotate >= 360) theta_fan_rotate = 0.0;
    }
    static float delang = 0.5;

    if ( fabs(angle_1) > 26.0)  delang *= -1.0;

    angle_1 += delang;
    angle_2 -= delang;



    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("kitchen");

    std::cout << glGetString(GL_RENDERER) << std::endl;

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\red-metal.bmp"); // 5         1
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\blackred.bmp"); // 16         2
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\pinkblue.bmp"); // 17         3
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\baskin-robin-ad.bmp"); // 17  4
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\floor.bmp");            //    5
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\coffeewall.bmp");        //   6
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\road.bmp");         //7
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\leaf2.bmp");        //   8
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\tree_base2.bmp");        //   9
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\glasswall.bmp");        //   10
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\door.bmp");          //11
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\Carpet.bmp");        //   12
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\roof-texture.bmp");   //13
    //LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\stage.bmp");        //   9
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\stagee.bmp");        //   14


    //   9

    //   9
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\counterr.bmp");        //   15
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\toasterr.bmp");        //   16
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\ruti.bmp");        //   17
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\cup_coffee.bmp");        //   18
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\smile.bmp");        //   19

    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\sun.bmp");        //   20
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\moon.bmp");        //   21
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\day.bmp");        //   22
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\night.bmp");        //   23
    LoadTexture("C:\\Users\\dipto\\OneDrive\\Desktop\\LAb_project\\sunset.bmp");        //   24






    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(SpecialInput);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
