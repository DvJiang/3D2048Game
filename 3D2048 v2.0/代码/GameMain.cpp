#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include "gameSDK.h"
static float anglex=0.78,angley = 0.4,ratio;
static float red = 0.0f,green = 1.0f, blue = 0.0f;
static float sred = 1.0f,sgreen = 1.0f, sblue = 1.0f;
static float x = 0.0f,y = 0.0f,z = 0.0f;
static float win_scale = 2.5;
static float camera_lenth = 11.0f;
static float doki_scale = 1.0f,doki_scale_i = 1,doki_speed = 2,doki_s = 0.3;
static bool self_span = 0,doki = 1,lineStyle = 1,show_set = 0,colorStyle = 1,sizeStyle = 1,num_flag = 1,help_flag = 0;
GLuint mainw,helpw;
Game game;

static const GLint quads[][4] = {  //6个面的绘制顺序,存储的是顶点的下标  
    0, 2, 3, 1,  
    0, 4, 6, 2,  
    0, 1, 5, 4,  
    4, 5, 7, 6,  
    1, 3, 7, 5,  
    2, 6, 7, 3,  
};  

std::string int2str(int num) {
    std::string strs;
    std::stringstream s;
    s << num;
    s >> strs;
    s.clear();
    return strs;
}

std::string strAnd(std::string a,std::string b) {
    std::string strs;
    std::stringstream s;
    s << a << b;
    s >> strs;
    s.clear();
    return strs;
}

void strShow(std::string str,float x,float y,float z) {
	int n = str.size();
	glRasterPos3f(x, y, z);
	for (int i = 0; i < n; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
}

void restart(){ //重新开始
    game.initial();
}

void changeSize(int w, int h)
{
// 防止被 0 除.
if(h == 0)  h = 1;
ratio = 1.0f * w / h;
// Reset the coordinate system before modifying
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
//设置视口为整个窗口大小
glViewport(0, 0, w, h);
//设置可视空间
gluPerspective(45,ratio,1,1000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
x = camera_lenth * cos(angley) * cos(anglex);
y = camera_lenth * sin(angley);
z = camera_lenth * cos(angley) * sin(anglex);
gluLookAt(-x, y, z,
    0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f);
}

void draw_cube(int num){  
    //8个顶点  
    GLfloat x=1.0f,y=1.0f,z=1.0f;
    static const GLfloat vetexs[][3] = {  
         0.0,0.0,0.0,  
         x,0.0,0.0,  
         0.0,y,0.0,  
         x,y,0.0,  
         0.0,0.0,z,  
         x,0.0,z,  
         0.0,y,z,  
         x,y,z  
    };  
     glColor3f(sred, sgreen, sblue);  
     glFrontFace(GL_CCW);  
     glCullFace(GL_BACK);  
     glEnable(GL_CULL_FACE);
     if (lineStyle)  
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (num != 3 && num_flag)
        strShow(int2str(num),0.0,0.0,0.0);
    glTranslatef(-x/2,-y/2,-z/2);  //平移至中心  
    //画立方体  
    for(int i = 0;i<6;i++){  
        glBegin(GL_QUADS);  
                glVertex3f(vetexs[quads[i][0]][0],vetexs[quads[i][0]][1],vetexs[quads[i][0]][2]);  
                glVertex3f(vetexs[quads[i][1]][0],vetexs[quads[i][1]][1],vetexs[quads[i][1]][2]);  
                glVertex3f(vetexs[quads[i][2]][0],vetexs[quads[i][2]][1],vetexs[quads[i][2]][2]);  
                glVertex3f(vetexs[quads[i][3]][0],vetexs[quads[i][3]][1],vetexs[quads[i][3]][2]);  
        glEnd();  
    }  
} 

void initScene() {
    glEnable(GL_DEPTH_TEST);
    game.initial();
}

void cameraMove(float angx,float angy) {
    x = camera_lenth * cos(angy) * cos(angx);
    y = camera_lenth * sin(angy);
    z = camera_lenth * cos(angy) * sin(angx);
    glLoadIdentity();
    gluLookAt(-x, y, z,
    0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f);
}

void cameraReset() {
    anglex=0.78;angley = 0.78;
    cameraMove(anglex,angley);
}

void help() {
    float posx = -4.0, posy = 3.0, lineSpace = -0.4, num = 3.0;
    strShow("Help and Related",-1.0,posy + 2.0 * lineSpace,posx + 3.0);
    strShow("Welcome to play DvJiang's 3D2048 Game, here is a \'help and related\' list.",0.0,posy + num * lineSpace,posx);
    num++;strShow("How to play:",0.0,posy + num * lineSpace,posx + 0.5);
    num++;strShow("Use WASDQE to control the game,and use direction key to control the camera view.",0.0,posy + num * lineSpace,posx);
    num++;strShow("Press the right mouse button to open the menu.Press R to reset the view of camera.",0.0,posy + num * lineSpace,posx);
    num++;strShow("Press P to return to the last step.",0.0,posy + num * lineSpace,posx);
    num++;strShow("Different ways was prepared to identify different cubes, click to choose them on the \'Style\' from the menu.",0.0,posy + num * lineSpace,posx);
    num++;strShow("For most options on the menu, click can change their state(open or close).",0.0,posy + num * lineSpace,posx);
    num++;strShow("About:",0.0,posy + num * lineSpace,posx + 0.5);
    num++;strShow("Author: DvJiang  Blog: dvjiang.github.io  Date: 2022-5-18",0.0,posy + num * lineSpace,posx);
    num++;num++;strShow("Click \'Help and Related\' from the menu to return",0.0,posy + num * lineSpace,posx + 4.0);
}

void gameOver() {
    int c = game.ifgameover();
    float posx = -4.0, posy = 3.0, lineSpace = -0.5, num = 5.0;
    if (c == 0) {
        strShow("Game Over",-1.0,posy + num * lineSpace,posx + 1.0);
        strShow(strAnd("Score:",int2str(game.score())),0.0,posy + num * lineSpace,posx + 4.0);
        strShow("Click \'Restart\' from the menu to restart game",0.0,posy + 12.0 * lineSpace,posx + 4.0);
    }
    else {
        strShow("2048 Get",-1.0,posy + num * lineSpace,posx + 1.0);
        strShow(strAnd("Score:",int2str(5000 - game.score())),0.0,posy + num * lineSpace,posx + 4.0);
        strShow("Click \'Restart\' from the menu to restart game",0.0,posy + 12.0 * lineSpace,posx + 4.0);
    }
}

void renderScene(void) {
    float size;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //doki-doki
    if (doki){
        doki_scale_i = doki_scale_i + doki_speed;
        if(doki_scale_i >= 78 || doki_scale_i <= 0)doki_speed = -doki_speed;
        doki_scale = 1.0 + doki_s*sin(doki_scale_i/314.15);
        }
    //self-span
    if (self_span) {
        anglex += 0.002f;
        cameraMove(anglex,angley);
    }
    if (help_flag || (game.ifgameover() != 2)) {
        if (help_flag) help();
        else gameOver();
    }
    else{
        //画了 16 个 方块
        sred = red;sgreen = green; sblue = blue;
        for(int i = -2; i < 2; i++)
            for(int j=-2; j < 2; j++) 
                for(int k = -2; k < 2; k++){
                    if(game.askBoard(i + 2, j + 2, k + 2) == 0) continue;
                    glPushMatrix();
                    glTranslatef((k+0.5)*1.5,(i+0.5)*1.5,(j+0.5) * 1.5);
                    if (game.askMatch(i + 2, j + 2, k + 2) && doki) 
                        glScalef(doki_scale,doki_scale,doki_scale);
                    if (colorStyle){
                        size = float(game.askBoard(i + 2, j + 2, k + 2));
                        size = 1.0 - (1.0/12.0) * log2(size);
                        sred = (red)?1.0:size; sgreen = (green)?1.0:size; sblue = (blue)?1.0:size;
                    }
                    if (sizeStyle){
                        size = float(game.askBoard(i + 2, j + 2, k + 2));
                        size = 1.0 - 1.0/12.0 * (log2(size) - 1);
                        glScalef(size,size,size);
                        }
                    draw_cube(game.askBoard(i + 2, j + 2, k + 2));
                    glPopMatrix();
                }

        glColor3f(0.0, 1.0, 0.0);  
        strShow("D",0.0,0.0,3.5);
        glPushMatrix();
            glTranslatef(0.0,0.0,4.25);
            glRotatef(180,0,-1,0);
            glutSolidCone(0.08f,0.5f,10,2);
        glPopMatrix();
        strShow("A",0.0,0.0,-3.5);
        glPushMatrix();
            glTranslatef(0.0,0.0,-4.25);
            glRotatef(0,0,0,0);
            glutSolidCone(0.08f,0.5f,10,2);
        glPopMatrix();
        strShow("W",0.0,3.5,0.0);
        glPushMatrix();
            glTranslatef(0.0,4.25,0.0);
            glRotatef(90,1,0,0);
            glutSolidCone(0.08f,0.5f,10,2);
        glPopMatrix();
        strShow("S",0.0,-3.5,0.0);
        glPushMatrix();
            glTranslatef(0.0,-4.25,0.0);
            glRotatef(-90,1,0,0);
            glutSolidCone(0.08f,0.5f,10,2);
        glPopMatrix();
        strShow("E",3.5,0.0,0.0);
        glPushMatrix();
            glTranslatef(4.25,0.0,0.0);
            glRotatef(-90,0,1,0);
            glutSolidCone(0.08f,0.5f,10,2);
        glPopMatrix();
        strShow("Q",-3.5,0.0,0.0);
        glPushMatrix();
            glTranslatef(-4.25,0.0,0.0);
            glRotatef(90,0,1,0);
            glutSolidCone(0.08f,0.5f,10,2);
        glPopMatrix();
        strShow(strAnd("Count:",int2str(game.score())),0.0,2.0,4.0);

        glColor3f(red, green, blue);
        if (show_set){
            std::string s;
            if (doki) s = "True"; else s = "False";
            strShow(strAnd("Doki:",s),0.0,2.0,5.0);
            if (lineStyle) s = "True"; else s = "False";
            strShow(strAnd("Cube:",s),0.0,1.0,5.0);
            if (colorStyle) s = "True"; else s = "False";
            strShow(strAnd("Color:",s),0.0,0.0,5.0);
            if (sizeStyle) s = "True"; else s = "False";
            strShow(strAnd("Size:",s),0.0,-1.0,5.0);
            if (num_flag) s = "True"; else s = "False";
            strShow(strAnd("Num:",s),0.0,-2.0,5.0);
            if (self_span) s = "True"; else s = "False";
            strShow(strAnd("Span:",s),0.0,-3.0,5.0);
        }
    }
    glutSwapBuffers();
 }

void inputSpecialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT :
            anglex -= 0.01f;
            cameraMove(anglex,angley);break;
        case GLUT_KEY_RIGHT :
            anglex += 0.01f;
            cameraMove(anglex,angley);break;
        case GLUT_KEY_UP :
            angley -= 0.01f;
            cameraMove(anglex,angley);break;
        case GLUT_KEY_DOWN :
            angley += 0.01f;
            cameraMove(anglex,angley);break;
    }
}

void inputNormalKey(unsigned char key, int x, int y) {
    switch (key) {
        case 'a' :
            game.getmove('a');break;
        case 'w' :
            game.getmove('s');break;
        case 's' :
            game.getmove('w');break;
        case 'd' :
            game.getmove('d');break;
        case 'q' :
            game.getmove('e');break;
        case 'e' :
            game.getmove('q');break;
        case 'p' :
            game.regret();break;
        case 'r' :
            cameraReset();break;
        case 27 :
            exit(0);
    }
}

void MainMenu(GLint MainOption)
{
	switch (MainOption)
	{
	case 1:
		restart();
        break;
	case 2:
		help_flag = (help_flag)?0:1;
        anglex = 0.0;angley = 0.0;
        cameraMove(anglex,angley);
		break;
	}
 
	glutPostRedisplay();
}

void ColorSubMenu(GLint colorOption)
{
	switch (colorOption)
	{
	case 1:
		red = 1.0f; green = 0.0f; blue = 0.0f;
		break;
	case 2:
		red = 0.0f; green = 0.0f; blue = 1.0f;
		break;
	case 3:
		red = 0.0f; green = 1.0f; blue = 0.0f;
		break;
    case 4:
		red = 1.0f; green = 1.0f; blue = 1.0f;
		break;
	}
 
	glutPostRedisplay();
}

void StyleSubMenu(GLint styleOption)
{
	switch (styleOption)
	{
	case 1:
		doki = (doki)?0:1;
		break;
    case 2:
        lineStyle = (lineStyle)?0:1;
        break;
    case 3:
        self_span = (self_span)?0:1;
        break;
    case 4:
        colorStyle = (colorStyle)?0:1;
        break;
    case 5:
        sizeStyle = (sizeStyle)?0:1;
        break;
    case 6:
        num_flag = (num_flag)?0:1;
        break;
    case 7:
        show_set = (show_set)?0:1;
        break;
	}
 
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640*win_scale,360*win_scale);
    mainw = glutCreateWindow("3D2048 Game");
    initScene();
    glutSpecialFunc(inputSpecialKey);
    glutKeyboardFunc(inputNormalKey);
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

	int subMenu1,subMenu2,Menu;
    subMenu1 = glutCreateMenu(ColorSubMenu);
    glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Blue", 2);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("White", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    subMenu2 = glutCreateMenu(StyleSubMenu);
    glutAddMenuEntry("Doki-Doki", 1);
    glutAddMenuEntry("Cube Style", 2);
    glutAddMenuEntry("Self Span", 3);
    glutAddMenuEntry("Color Style", 4);
    glutAddMenuEntry("Size Style", 5);
    glutAddMenuEntry("Show Number", 6);
    glutAddMenuEntry("Show Settings", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	Menu = glutCreateMenu(MainMenu);
	glutAddMenuEntry("Restart Game", 1);
	glutAddMenuEntry("Help and Related", 2);
    glutAddSubMenu("Color", subMenu1);
    glutAddSubMenu("Setting", subMenu2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return(0);
}

