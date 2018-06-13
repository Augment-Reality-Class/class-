#define WindowWidth  400
#define WindowHeight 400
#define WindowTitle  "OpenGL纹理测试"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

//定义两个纹理对象编号
GLuint texGround;
GLuint texWall;

#define BMP_Header_Length 54  //图像数据在内存块中的偏移量
static GLfloat angle = 0.0f;   //旋转角度

// 函数power_of_two用于判断一个整数是不是2的整数次幂
int power_of_two(int n)
{
	if( n <= 0 )
		return 0;
	return (n & (n-1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID=0, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if( pFile == 0 )
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while( line_bytes % 4 != 0 )
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if( pixels == 0 )
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if( fread(pixels, total_bytes, 1, pFile) <= 0 )
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 若图像宽高超过了OpenGL规定的最大值，也缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if( !power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max )
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while( new_line_bytes % 4 != 0 )
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if( new_pixels == 0 )
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if( texture_ID == 0 )
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID=last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	free(pixels);
	return texture_ID;
}


void display(void)
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 设置视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-4, 7,7, 0, 0, 0, 0, 0, 1);

	glRotatef(angle, 0.0f, 0.0f, 1.0f); //旋转

	// 绘制底面以及纹理
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	GLfloat vdata[113][3] = {
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
	glEnd();
	// 绘制立面
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 5.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	//绘制另外一个立面
	glBegin(GL_QUADS);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(6.0f, 9.0f, 0.0f);		 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(6.0f, 9.0f, 5.0f);		 
	glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);	 
	glEnd();	

	glutSwapBuffers();  
}

void myIdle(void)  
{     
	angle += 1.8f;    
	if( angle >= 360.0f )      
		angle = 0.0f;   
	display();  
}   

int main(int argc, char* argv[])
{
	// GLUT初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);	
	glEnable(GL_DEPTH_TEST);    
	glEnable(GL_TEXTURE_2D);    // 启用纹理
	texGround = load_texture("2.bmp");  //加载纹理
	//texWall = load_texture("p4.bmp");
	glutDisplayFunc(&display);   //注册函数 
	glutIdleFunc(&myIdle);  
	glutMainLoop(); //循环调用
	return 0;
}
