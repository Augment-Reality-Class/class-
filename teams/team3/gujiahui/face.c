#include <GL/glut.h>

#define X 0.525731112119133606
#define Z 0.850650808352039932

static GLfloat vdata[113][3] = {
	0.000000f,1.061000f,-0.371000f,
0.174000f,0.800000f,-0.024000f,
0.000000f,0.539000f,0.085000f,
0.000000f,0.278000f,0.107000f,
0.000000f,0.213000f,0.085000f,
0.000000f,-0.222000f,0.210000f,
0.000000f,-0.265000f,0.124000f,
0.000000f,-0.417000f,0.142000f,
0.000000f,-0.526000f,0.150000f,
0.000000f,-0.591000f,0.107000f,
//10
0.000000f,-0.852000f,0.063000f,
0.217000f,1.039000f,-0.371000f,
0.457000f,0.909000f,-0.328000f,
0.435000f,0.626000f,-0.111000f,
0.610000f,0.539000f,-0.328000f,
0.522000f,0.278000f,-0.111000f,
0.391000f,0.374000f,0.0300000f,
0.130000f,0.278000f,0.107000f,
0.391000f,0.322000f,0.0300000f,
0.304000f,0.225000f,-0.002000f,
//20
0.470000f,0.148000f,-0.111000f,
0.304000f,0.204000f,-0.000000f,
0.304000f,0.122000f,-0.000000f,
0.130000f,0.148000f,-0.000000f,
0.304000f,0.104000f,-0.000000f,
0.109000f,-0.157000f,0.037000f,
0.174000f,-0.244000f,0.037000f,
0.387000f,-0.100000f,-0.045000f,
0.550000f,-0.250000f,-0.328000f,
0.609000f,0.148000f,-0.328000f,
//30
0.470000f,-0.600000f,-0.328000f,
0.246000f,-0.461000f,-0.000000f,
0.174000f,-0.809000f,0.000000f,
0.043000f,-0.396000f,0.150000f,
-0.174000f,0.800000f,-0.024000f,
0.000000f,0.539000f,0.085000f,
0.000000f,0.278000f,0.107000f,
0.000000f,0.213000f,0.085000f,
0.000000f,-0.222000f,0.210000f,
0.000000f,-0.265000f,0.124000f,
//40
0.000000f,-0.461000f,0.124000f,
0.000000f,-0.526000f,0.150000f,
0.000000f,-0.591000f,0.107000f,
0.000000f,-0.852000f,0.063000f,
-0.217000f,1.039000f,-0.371000f,
-0.457000f,0.909000f,-0.328000f,
-0.435000f,0.626000f,-0.111000f,
-0.610000f,0.539000f,-0.328000f,
-0.522000f,0.278000f,-0.111000f,
-0.391000f,0.374000f,0.030000f,
//50
-0.130000f,0.278000f,0.107000f,
-0.391000f,0.322000f,0.030000f,
-0.304000f,0.225000f,-0.002000f,
-0.470000f,0.148000f,-0.111000f,
-0.304000f,0.204000f,-0.000000f,
-0.304000f,0.122000f,-0.000000f,
-0.130000f,0.148000f,-0.000000f,
-0.304000f,0.104000f,-0.000000f,
-0.109000f,-0.157000f,0.037000f,
-0.174000f,-0.244000f,0.037000f,
//60
-0.387000f,-0.100000f,-0.045000f,
-0.550000f,-0.250000f,-0.328000f,
-0.609000f,0.148000f,-0.328000f,
-0.470000f,-0.600000f,-0.328000f,
-0.246000f,-0.461000f,-0.000000f,
-0.174000f,-0.809000f,0.000000f,
-0.043000f,-0.396000f,0.150000f,
0.348000f,0.200000f,-0.0300000f,
0.348000f,0.115000f,-0.0300000f,
-0.348000f,0.200000f,-0.0300000f,
//70
-0.348000f,0.115000f,-0.0300000f,
0.265000f,0.200000f,-0.0300000f,
0.265000f,0.115000f,-0.0300000f,
-0.265000f,0.200000f,-0.0300000f,
-0.265000f,0.115000f,-0.0300000f,
0.080000f,-0.220000f,0.150000f,
-0.080000f,-0.220000f,0.150000f,
0.022000f,0.213000f,0.063000f,
-0.022000f,0.213000f,0.063000f,
0.123000f,-0.410000f,0.063000f,
//80
-0.123000f,-0.410000f,0.063000f,
0.100000f,-0.461000f,0.050000f,
-0.100000f,-0.461000f,0.050000f,
0.100000f,-0.461000f,0.050000f,
-0.100000f,-0.461000f,0.050000f,
0.123000f,-0.508000f,0.063000f,
-0.123000f,-0.508000f,0.063000f,
0.000000f,-0.461000f,0.124000f,
0.200000f,-0.461000f,-0.024000f,
-0.200000f,-0.461000f,-0.024000f,
//90
0.357000f,-0.461000f,-0.050000f,
-0.357000f,-0.461000f,-0.050000f,
0.065000f,0.028000f,0.050000f,
-0.065000f,0.028000f,0.050000f,
0.000000f,0.068000f,0.100000f,
0.387000f,0.201000f,-0.056000f,
-0.387000f,0.201000f,-0.056000f,
0.387000f,0.186000f,-0.056000f,
-0.387000f,0.186000f,-0.056000f,
0.387000f,0.126000f,-0.056000f,
//100
-0.387000f,0.126000f,-0.056000f,
0.387000f,0.117000f,-0.067000f,
-0.387000f,0.117000f,-0.067000f,
0.217000f,0.201000f,-0.013000f,
-0.217000f,0.201000f,-0.013000f,
0.217000f,0.186000f,-0.013000f,
-0.217000f,0.186000f,-0.013000f,
0.217000f,0.126000f,-0.013000f,
-0.217000f,0.126000f,-0.013000f,
0.217000f,0.117000f,-0.024000f,
//110
-0.217000f,0.117000f,-0.024000f,
0.120000f,-0.265000f,0.100000f,
-0.120000f,-0.265000f,0.100000f
};

static GLuint tindices[184][3] = {
0,11,1,
0,1,34,
0,34,44,
11,12,1,
44,34,45,
1,12,13,
1,13,2,
1,2,34,
2,46,34,
34,46,45,
//10
12,14,13,
13,14,15,
13,15,16,
2,13,16,
2,16,17,
2,17,3,
2,3,50,
2,50,49,
2,49,46,
46,49,48,
//20
46,48,47,
45,46,47,
14,29,15,
15,29,20,
18,15,19,
18,16,15,
16,18,17,
17,18,19,
17,23,77,
3,17,77,
//30
3,78,50,
78,56,50,
50,52,51,
49,50,51,
48,49,51,
48,51,52,
48,53,62,
47,48,62,
29,28,27,
20,29,27,
//40
24,26,25,
57,58,59,
53,60,62,
62,60,61,
111,26,33,
75,26,111,
75,25,26,
76,59,58,
76,112,59,
112,66,59,
//50
6,33,7,
6,7,66,
9,32,10,
9,10,65,
6,76,5,
6,5,75,
3,77,78,
7,33,79,
7,79,81,
7,81,87,
//60
7,80,66,
7,82,80,
7,87,82,
80,82,89,
80,89,64,
79,88,81,
79,31,88,
26,79,33,
26,31,79,
59,66,80,
//70
59,80,64,
88,83,85,
88,85,31,
83,8,85,
83,40,8,
8,40,84,
8,84,86,
86,89,84,
86,64,89,
9,85,8,
//80
9,8,86,
32,85,31,
32,9,85,
65,86,64,
65,9,86,
27,26,24,
90,30,32,
90,32,31,
90,30,28,
90,26,31,
//90
90,27,26,
90,28,27,
60,59,57,
91,65,63,
91,64,65,
91,61,63,
91,64,59,
91,59,60,
91,60,61,
92,77,23,
//100
92,23,25,
92,25,75,
93,56,78,
93,76,58,
93,58,56,
94,77,92,
94,92,75,
94,75,5,
94,5,76,
94,76,93,
//110
94,93,78,
94,78,77,
20,95,15,
20,97,95,
20,101,99,
20,27,101,
95,19,15,
95,21,19,
95,97,21,
101,27,24,
//120
101,24,22,
101,22,99,
23,103,17,
23,105,103,
23,109,107,
23,25,109,
103,17,19,
103,19,21,
103,21,105,
109,107,22,
//130
109,22,24,
109,24,25,
56,104,50,
56,106,104,
56,110,108,
56,58,110,
104,52,50,
104,54,52,
104,106,54,
110,55,108,
//140
110,57,55,
110,58,57,
53,48,96,
53,98,96,
53,100,102,
53,102,60,
96,48,52,
96,52,54,
96,54,98,
102,100,55,
//150
102,55,57,
102,57,60,
111,6,75,
111,33,6,
112,76,6,
112,6,66,
73,74,70,
73,70,69,
67,68,72,
67,72,71,
//160
53,69,70,
56,74,73,
23,71,72,
20,68,67,
98,69,53,
54,69,98,
54,73,69,
54,106,73,
106,56,73,
56,108,74,
//170
55,74,108,
55,70,74,
55,100,70,
100,53,70,
20,67,97,
97,67,21,
21,67,71,
21,71,105,
105,71,23,
20,99,68,
//180
68,99,22,
22,72,68,
22,107,72,
107,23,72
};

static GLfloat spin = 0.0;

void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);  //������ģ����Ϊƽ��ģʽ
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();  //���������任�ļ���
	glRotatef(spin,0.0,1.0,0.0);
	glColor3f(0.5,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FRONT);
	glBegin(GL_TRIANGLES);
	int i;
	for(i=0;i<184;i++)
	{
		glVertex3fv(&vdata[tindices[i][0]][0]);
		glVertex3fv(&vdata[tindices[i][1]][0]);
		glVertex3fv(&vdata[tindices[i][2]][0]);
	}
	glEnd();
	glPopMatrix();  //�ظ�������ʼ̬
	glutSwapBuffers();
}

void spinDisplay(void)
{
	spin=spin + 0.1;
	if(spin>360.0)
		spin=spin - 360.0;
	glutPostRedisplay();
}

void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0,5.0,-5.0,5.0,-5.0,5.0);
	gluLookAt(1.0,1.0,0.5,0.0,0.0,0.0,0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button,int state,int x,int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON :
		if (state==GLUT_DOWN)
			glutIdleFunc(spinDisplay);  //���д���
		break;
	case GLUT_MIDDLE_BUTTON :
		if(state==GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default :
		break;
	}
}


int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(20,20);
	glutCreateWindow("�ҵĴ���");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}