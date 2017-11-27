#include "TextureBuilder.h"
#include "SalahFace.h"
#include "WorldCup.h"
#include <glut.h>
#include <math.h>


int bg_x = 0; //scenes background x axis
int o_x = -100; //obstacle x axis
int p_x = -100; //obstacle x axis
int o_y = -100; //obstacle y axis
int man_x = 140; //man x axis
int man_y = 50; //man y axis
int o_c = 0; //obstacles counter
int o_n = 6; // number of obstacles for each powerup
int p_r = 0; //powerup rotation angle
int o_speed = 0; // o_speed range from 1 to 3
int man_l = 11; //man location initial location
int o_l = 0; //obstacle location
int b_a = 0; //ball angle
int b_x = 0; //ball x-axis
int b_y = 0; //ball y-axis
float Ll_a = 0; //left leg angle

double man_c_R = 0;//man obstacle color red att.
double man_c_G = 0;//man obstacle color green att.
double man_c_B = 0;//man obstacle color blue att.


double backRed = 0;
double backGreen = 0;
double backBlue = 0.5;

int redD = 1;
int greenD = 1;
int blueD = 1;

GLuint texID;

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and tis radius
void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void ads_bg(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	backRed += 0.1*redD;							//--
	if (backRed<0 || backRed>1)					//	|
		redD *= -1;								//	|
	//	|
	backGreen += 0.1*greenD;						//	|
	if (backGreen<0 || backGreen>0.5)				//	|		
		greenD *= -1;								//	|this code is called every 1000 ms "ever 1 sec"
	//	|		
	backBlue += 0.1*blueD;						//	|
	if (backBlue<0.5 || backBlue>0.75)				//	|
		blueD *= -1;								//	|
	//--
	glutPostRedisplay();						// redraw 		
	glutTimerFunc(1000, ads_bg, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}


void generate_star(){
	//star
	glPushMatrix();
		glScaled(0.5, 1, 0);
		glTranslated(0, 30, 0);
		glTranslated(p_x, o_y, 0);
		//glTranslated(50, 50, 0);
		glRotated(p_r, 0, 0, 1);
		glColor3f(0.952f, 0.917f, 0.125f);

		glBegin(GL_QUADS);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 25, 0);
		glVertex3d(25, 25, 0);
		glVertex3d(25, 0, 0);
		glEnd();
		
		glPushMatrix();
			glTranslated(13, -5, 0);
			glRotated(45, 0, 0, 1);
			glBegin(GL_QUADS);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 25, 0);
			glVertex3d(25, 25, 0);
			glVertex3d(25, 0, 0);
			glEnd();
		glPopMatrix();

	glPopMatrix();

	glutPostRedisplay();

}


void generate_obstacle(){
	//man
	glPushMatrix();//body
	
		glTranslated(o_x, o_y, 0);
		glScaled(0.4, 1, 0);
		glRotated(180, 1, 0, 0);
		glRotated(260, 0, 0, 1);
		glColor3f(man_c_R, man_c_G, man_c_B);

			//shoulders
		glPushMatrix();
			glTranslated(10, -10, 0);
			glScalef(0.5, 1, 1);
			drawCircle(0, 130, 20);
		glPopMatrix();

		glBegin(GL_POLYGON);
		glVertex3d(0, 70, 0);
		glVertex3d(20, 70, 0);//width = 20
		glVertex3d(20, 120, 0);//height = 60
		glVertex3d(0, 120, 0);//shifted by 70
		glEnd();


	//head
	glPushMatrix();
	glColor3f(0.972, 0.882, 0.588);
	glTranslated(10, 150, 0);
	glScaled(-0.5f, 1, 0);
	GLUquadric *quad = gluNewQuadric();
	//gluQuadricDrawStyle(quad, GLU_SILHOUETTE);
	//glColor3ub(1, 1, 1); // purple
	gluDisk(quad, 0, 20, 64, 64);
	glPopMatrix();

	//legs

	//left
	glPushMatrix();//left short
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3d(0, 50, 0);
	glVertex3d(9, 50, 0);//width = 9
	glVertex3d(9, 70, 0);//height = 20
	glVertex3d(0, 70, 0);//shifted by 50
	glEnd();

	//left leg
	glTranslated(1, 15, 0);
	glColor3f(0.980f, 0.854f, 0.501f);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(6, 0, 0);//width = 6
	glVertex3d(6, 35, 0);//height = 30
	glVertex3d(0, 35, 0);
	glEnd();

	//left foot
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 15, 0);//width = 6
	glVertex3d(10, 0, 0);//height = 30
	glEnd();
	glPopMatrix();

	//right
	glPushMatrix();//right short
	glTranslated(11, 0, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3d(0, 50, 0);
	glVertex3d(9, 50, 0);//width = 9
	glVertex3d(9, 70, 0);//height = 20
	glVertex3d(0, 70, 0);//shifted by 50
	glEnd();

	//right leg
	glTranslated(1, 15, 0);
	glColor3f(0.980f, 0.854f, 0.501f);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(6, 0, 0);//width = 6
	glVertex3d(6, 35, 0);//height = 30
	glVertex3d(0, 35, 0);
	glEnd();

	//right foot
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 15, 0);//width = 6
	glVertex3d(10, 0, 0);//height = 30
	glEnd();
	glPopMatrix();


	glPopMatrix();

	

	glutPostRedisplay();

}



void drawBitmapText(char *string, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void drawBitmapText_small(char *string, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}


int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}

int rep = 1;


void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	//scenes backgrounds
	//ads background
	glPushMatrix();
		glTranslated(0, 250, 0);
		glBegin(GL_QUADS);
		glColor3f(backRed, backGreen, backBlue);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 50, 0);
		glVertex3d(500, 50, 0);
		glVertex3d(500, 0, 0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-bg_x, 0, 0);
		//background 1
		glPushMatrix();
			//ground
			for (int i = 0; i < 5; i++){
				glBegin(GL_QUADS);
				glColor3f(0.156f, 0.584f, 0.250f);
				glVertex3d(20 + i * 100, 0, 0);
				glVertex3d(0 + i * 100, 400, 0);
				glVertex3d(50 + i * 100, 400, 0);
				glVertex3d(70 + i * 100, 0, 0);
				glEnd();
			}

			//ads background
			glTranslated(0, 250, 0);
			glBegin(GL_QUADS);
			glColor3f(backRed, backGreen, backBlue);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 50, 0);
			glVertex3d(400, 50, 0);
			glVertex3d(400, 0, 0);
			glEnd();

			//ads Text
			glPushMatrix();
				//glTranslated(-100, 20, 0);
				glTranslated(300, 20, 0);
				char *text = "G";
				glColor3f(0.952f, 0.917f, 0.125f);
				drawBitmapText(text, 0, 0, 0);
				text = "U";
				glColor3f(1, 0, 0);
				drawBitmapText(text, 10, 0, 0);
				text = "C";
				glColor3f(0, 0, 0);
				drawBitmapText(text, 20, 0, 0);

				text = "German University in Cairo";
				glColor3f(0, 0, 0);
				drawBitmapText_small(text, 30, 0, 0);

			glPopMatrix();
		glPopMatrix();


		//background 2
		glPushMatrix();
			//glTranslated(-400, 0, 0);
			glTranslated(400, 0, 0);
			//ground
			for (int i = -4; i < 8; i++){
				glBegin(GL_QUADS);
				glColor3f(0.156f, 0.584f, 0.250f);
				glVertex3d(20 + i * 100, 0, 0);
				glVertex3d(0 + i * 100, 250, 0);
				glVertex3d(50 + i * 100, 250, 0);
				glVertex3d(70 + i * 100, 0, 0);
				glEnd();
			}

			//ads background
			glTranslated(0, 250, 0);
			glBegin(GL_QUADS);
			glColor3f(backRed, backGreen, backBlue);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 50, 0);
			glVertex3d(300, 50, 0);
			glVertex3d(300, 0, 0);
			glEnd();

			//ads Text
			glPushMatrix();
				glTranslated(120, 20, 0);
				text = "D";
				glColor3f(0.952f, 0.917f, 0.125f);
				drawBitmapText(text, 4, 0, 0);
				text = "M";
				glColor3f(1, 0, 0);
				drawBitmapText(text, 10, 0, 0);
				text = "E";
				glColor3f(0, 0, 0);
				drawBitmapText(text, 20, 0, 0);
				text = "T";
				glColor3f(0, 0, 1);
				drawBitmapText(text, 26, 0, 0);
				text = "502";
				glColor3f(0, 1, 1);
				drawBitmapText(text, 40, 0, 0);

				text = "Computer Graphics";
				glColor3f(0, 0, 0);
				drawBitmapText_small(text, 70, 0, 0);

				text = "RUSSIA 2018";
				glColor3f(1, 0, 0);
				drawBitmapText(text, 170, 0, 0);

				glTranslated(130, -15, 0);
				glPointSize(2.3);
				glScalef(1.0f, 1.0f, 1);
				world_cup();
				glPointSize(1);

				
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	

	//Goal
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslated(260, 30, 0);
		glScaled(5, 15, 0);
		glBegin(GL_LINES);
		glVertex2d(2,6);
		glVertex2d(2,12);

		glVertex2d(2, 12);
		glVertex2d(4, 10);

		glVertex2d(4, 10);
		glVertex2d(4, 6);

		glVertex2d(2, 12);
		glVertex2d(5, 6);

		glVertex2d(5, 6);
		glVertex2d(5, 0);

		glVertex2d(5, 6);
		glVertex2d(7, 4);

		glVertex2d(7, 4);
		glVertex2d(7, 0);
		glEnd();
	glPopMatrix();



	//man
	glPushMatrix();//body
	glTranslated(man_x + b_x - 585, man_y + b_y-280, 0);
		glColor3f(1, 0, 0);
		
		//shoulders
		glPushMatrix();
			glTranslated(10, -10, 0);
			glScalef(0.5, 1, 1);
			drawCircle(0, 130, 20);
		glPopMatrix();

		//main body rectangle
		glBegin(GL_QUADS);
		glVertex3d(0, 70, 0);
		glVertex3d(20, 70, 0);//width = 20
		glVertex3d(20, 120, 0);//height = 50
		glVertex3d(0, 120, 0);//shifted by 70
		glEnd();

		//ball
		glPushMatrix();
			glTranslated(b_x-585, b_y-280,0);
			//glRotated(b_a,0,0,1);
			//glTranslated(30, 35, 0);

			glColor3f(1, 1, 1);
			glTranslated(30, 35, 0);
			glScaled(-0.8f, -0.8f, 0);
			glScaled(-0.5f, 1, 0);
			GLUquadric *quad1 = gluNewQuadric();
			//gluQuadricDrawStyle(quad, GLU_SILHOUETTE);
			//glColor3ub(1, 1, 1); // purple
			gluDisk(quad1, 0, 20, 64, 64);


			//pentagon
			glTranslated(-20, 18 , 0);
			glScaled(5, 5, 0);
			glColor3f(0,0, 0);
			glBegin(GL_POLYGON);
			glVertex3d(3, -2, 0);
			glVertex3d(5, -2, 0);
			glVertex3d(6, -4, 0);
			glVertex3d(4, -6, 0);
			glVertex3d(2, -4, 0);
			glEnd();
		glPopMatrix();


		//T shirt writing
		glPushMatrix();
			glTranslated(1, 110, 0);
			text = "M. SALAH";
			glColor3f(1,1, 1);
			drawBitmapText_small(text, 0, 0, 0);

			glTranslated(4, -20, 0);
			text = "10";
			glColor3f(1, 1, 1);
			drawBitmapText(text, 0, 0, 0);
		glPopMatrix();

		//head
		glPushMatrix();
			glColor3f(0.972, 0.882, 0.588);
			glTranslated(10, 150, 0);
			glPushMatrix();
				glScaled(-0.5f, 1, 0);

				int width = 5;
				int height = 5;
			//	unsigned char* image = SOIL_load_image("msalah.png", &width, &height, 0, SOIL_LOAD_RGB);
			//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

				GLUquadric *quad = gluNewQuadric();
				//gluQuadricDrawStyle(quad, GLU_SILHOUETTE);
				//glColor3ub(1, 1, 1); // purple
				gluDisk(quad, 0, 10, 64, 64);
			glPopMatrix();

			glPushMatrix();
			glTranslated(-9, -19, 0);
			glScalef(0.11f, 0.25f, 1);
			salah_face();
			glPopMatrix();
		glPopMatrix();

		//legs

		//left
		glPushMatrix();//left short
			glRotatef(Ll_a, 0, 0, 1);
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			glVertex3d(0, 50, 0);
			glVertex3d(9, 50, 0);//width = 9
			glVertex3d(9, 70, 0);//height = 20
			glVertex3d(0, 70, 0);//shifted by 50
			glEnd();
			
			//left leg
			glTranslated(1, 15, 0);
			glColor3f(0.980f, 0.854f, 0.501f);
			glBegin(GL_QUADS);
			glVertex3d(0, 0, 0);
			glVertex3d(6, 0, 0);//width = 6
			glVertex3d(6, 35, 0);//height = 30
			glVertex3d(0, 35, 0);
			glEnd();

			//left foot
			glColor3f(0, 0, 0);
			glBegin(GL_TRIANGLES);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 15, 0);//width = 6
			glVertex3d(10, 0, 0);//height = 30
			glEnd();	
		glPopMatrix();

		//right
		glPushMatrix();//right short
			glRotatef(-Ll_a, 0, 0, 1);
			glTranslated(11,0,0);
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			glVertex3d(0, 50, 0);
			glVertex3d(9, 50, 0);//width = 9
			glVertex3d(9, 70, 0);//height = 20
			glVertex3d(0, 70, 0);//shifted by 50
			glEnd();

			//right leg
			glTranslated(1, 15, 0);
			glColor3f(0.980f, 0.854f, 0.501f);
			glBegin(GL_QUADS);
			glVertex3d(0, 0, 0);
			glVertex3d(6, 0, 0);//width = 6
			glVertex3d(6, 35, 0);//height = 30
			glVertex3d(0, 35, 0);
			glEnd();

			//right foot
			glColor3f(0, 0, 0);
			glBegin(GL_TRIANGLES);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 15, 0);//width = 6
			glVertex3d(10, 0, 0);//height = 30
			glEnd();
		glPopMatrix();


	glPopMatrix();

	generate_obstacle();
	generate_star();
	
	

	glFlush();
}

int p0[2];
int p1[2];
int p2[2];
int p3[2];
float t = 0;
float Ll_a_c; //left leg angle change

void background_movement(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{

	if (Ll_a <= -3){
		Ll_a_c = 0.3;
	} 
	if (Ll_a >= 0){
		Ll_a_c = -0.3;
	}
	Ll_a += Ll_a_c;


	if (t > 1){
		t = 0;
	}
	p0[0] = 585;
	p0[1] = 275;

	p1[0] = 571;
	p1[1] = 294;

	p2[0] = 604;
	p2[1] = 290;

	p3[0] = 586;
	p3[1] = 276;

	int*p = bezier(t, p0, p1, p2, p3);
	b_x = p[0];
	b_y = p[1];
	//printf(b_x);
	t += 0.025;

	if (b_a == 361)
		b_a = 1;
	b_a++;

	if (bg_x == 698){
		bg_x = 0;
	}
	else{
		bg_x++;
	}
	glutPostRedisplay();						// redraw 		
	glutTimerFunc(30, background_movement, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}

void man_movement(int val) //timer animation function, allows the user to pass an integer valu to the timer function.
{
	if (man_y<=130 && man_y>=-30){
		if (val > 0){
			man_y++;
			val--;
		}
		else if (val<0){
			man_y--;
			val++;
		}
	
		glutPostRedisplay();// redraw 		
		if (val != 0)
			glutTimerFunc(8, man_movement, val);
	}
	else if (man_y > 130){
		man_y = 130;
	}
	else if (man_y < -30){
		man_y = -30;
	}
}

void change_man_location(char *direction){

	/*
		map

		1   |   2   |   3   |  4    |   5   |  6    |   7  
		----|-------|-------|-------|----------------------
		8   |   9   |   10  |  11   |   12  |  13   |   14  
		----|-------|-------|-------|---------------------
		15  |   16  |   17  |  18   |   19  |  20   |   21  
	*/

	if (direction=="up" && man_l>7){
		man_l -= 7;
	}
	else if (direction == "down" && man_l<15){
		man_l += 7;
	}
	else if (direction == "right" ){
		man_l ++;
	}
	else if (direction == "left"){
		man_l--;
	}


	//x-axis
	switch (man_l%7 ){
		case 0: man_x = -50; break;
		case 1: man_x = -50; break;
		case 2: man_x = 50; break;
		case 3: man_x = 100; break;
		case 4: man_x = 140; break;
		case 5: man_x = 180; break;
		case 6: man_x = 240; break;
	}

	//y-axis
	if (man_l <= 7){//up
		glutTimerFunc(0, man_movement, 130-man_y);		//call the timer function
		//man_y = 130;
	}
	else if (man_l >= 15){//down
		glutTimerFunc(0, man_movement, -30 - man_y);		//call the timer function
		//man_y = -30;
	}
	else{//middle
		glutTimerFunc(0, man_movement, 50 - man_y);		//call the timer function
		//man_y = 50;
	}


}




void spe(int k, int x, int y)// keyboard special key function takes 3 parameters
// int k: is the special key pressed such as the keyboard arrows the f1,2,3 and so on
{

	if (k == GLUT_KEY_UP && man_y < 50 + 80)//if the up arrow is pressed, then the object will be translated in the y axis by 10. (moving upwords)
		change_man_location("up");
		//man_y += 80;
	if (k == GLUT_KEY_DOWN && man_y>50 - 80)//if the down arrow is pressed, then the object will be translated in the y axis by -10. (moving downwords)
		//man_y -= 80;
		change_man_location("down");
	//if (k == GLUT_KEY_RIGHT && man_y < 50 + 80)//if the up arrow is pressed, then the object will be translated in the y axis by 10. (moving upwords)
	//	change_man_location("right");
	//if (k == GLUT_KEY_LEFT && man_y>50 - 80)//if the down arrow is pressed, then the object will be translated in the y axis by -10. (moving downwords)
		//change_man_location("left");

	glutPostRedisplay();//redisplay to update the screen with the changes
}


int check_if_crashed(int o_x, int o_y){
	if (o_x > man_x - 10 && o_x < man_x + 10 && o_y > man_y-10 && o_y < man_y + 80){
		PlaySound(TEXT("crashed.wav"), NULL, SND_ASYNC);
		Sleep(500);
		PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC | SND_LOOP);
		change_man_location("left");
		return  -100;
	}
	else{
		return o_x;
	}
}

int check_if_powered_up(int p_x, int p_y){
	if (man_l % 7 == 4 &&  p_x > man_x + 130 && p_x < man_x + 170 && p_y > man_y - 10 && p_y < man_y + 80){
		PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC);
		Sleep(2000);
		PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC | SND_LOOP);
		change_man_location("right");
		return  -100;
	}
	else if (man_l % 7 == 5 && p_x > man_x + 160 && p_x < man_x +200 && p_y > man_y - 10 && p_y < man_y + 80){
		PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC);
		Sleep(2000);
		PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC | SND_LOOP);
		change_man_location("right");
		return  -100;
	}
	else if (man_l % 7 == 6 && p_x > man_x + 220 && p_x < man_x + 260 && p_y > man_y - 10 && p_y < man_y + 80){
		PlaySound(TEXT("Goal.wav"), NULL, SND_ASYNC);
		Sleep(16000);
		//PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC | SND_LOOP);
		change_man_location("right");
		return  -100;
	}
	else if (man_l % 7 == 3 && p_x > man_x +80 && p_x < man_x + 120 && p_y > man_y - 10 && p_y < man_y + 80){
		PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC);
		Sleep(2000);
		PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC | SND_LOOP);
		change_man_location("right");
		return  -100;
	}
	else if (man_l % 7 == 2 && p_x > man_x + 40 && p_x < man_x + 80 && p_y > man_y - 10 && p_y < man_y + 80){
		PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC);
		Sleep(2000);
		PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC | SND_LOOP);
		change_man_location("right");
		return  -100;
	}
	else{
		return p_x;
	}
}

void obstacle(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{ 
	if (man_l % 7 == 1){
		PlaySound(TEXT("GameOver.wav"), NULL, SND_ASYNC);
		MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	else if (man_l % 7 == 0){
		PlaySound(TEXT("victory.wav"), NULL, SND_ASYNC | SND_LOOP);
		MessageBox(NULL, L"You Win", L"Info", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

   if (o_c == o_n+1 && p_x<-80){
		p_x = 620;
		o_c++;
		o_x = -100;
		int random_y_level = (rand() % 3) + 1;
		if (random_y_level == 1){ //up
			o_y = 160;
		}
		else if (random_y_level == 2){ // middle
			o_y = 80;
		}
		else{ // down
			o_y = 10;
		}
	}
	else if (o_c == o_n+2){
		p_x-=3;
		p_x = check_if_powered_up(p_x, o_y);
		if (p_x < -80)
			o_c = 0;
	}
	else{
		if (o_x < -80){
			//generate_obstacle();
			o_x = 300;
			o_c++;

			man_c_R = ((double)rand()) / ((double)RAND_MAX);
			man_c_G = ((double)rand()) / ((double)RAND_MAX);
			man_c_B = ((double)rand()) / ((double)RAND_MAX);
			o_speed = (rand() % 3) + 1;

			int random_y_level = (rand() % 3) + 1;
			if (random_y_level == 1){ //up
				o_y = 160;
			}
			else if (random_y_level == 2){ // middle
				o_y = 80;
			}
			else{ // down
				o_y = 10;
			}
		}
		else{
			o_x-=o_speed;
			o_x = check_if_crashed(o_x, o_y);
		}
	}
	

	p_r += 5;
	if (p_r == 365)
		p_r = 5;
	glutPostRedisplay();						// redraw
	glutTimerFunc(15, obstacle, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}


void loadBMP2(GLuint *texture, const char *filename, int width = 1024, int height = 512, bool wrap = true) {
	unsigned char *data;
	FILE *file;

	file = fopen(filename, "rb");
	if (file == NULL) return;
	data = (unsigned char *)malloc(width*height * 3);
	fread(data, width*height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width*height; ++i) {
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
}



void main(int argc, char** argv) {
	glutInit(&argc, argv);


	glutInitWindowSize(800, 400);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("RUSSIA 2018");


	PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC | SND_LOOP);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glutDisplayFunc(Display);

	gluOrtho2D(0.0, 300, 0.0, 300);
	glLineWidth(100);

	//glPointSize(2.5);

	glEnable(GL_TEXTURE_2D);




	loadBMP(&texID, "textures/msalah.bmp", false);
	//loadPPM(&texID, "textures/clouds.ppm", 200, 200, true);

	glutTimerFunc(0, background_movement, 0);		//call the timer function
	glutSpecialFunc(spe);			//call the keyboard special keys function
	glutTimerFunc(0, obstacle, 0);		//call the timer function
	glutTimerFunc(0, ads_bg, 0);		//call the timer function


	glutMainLoop();
}