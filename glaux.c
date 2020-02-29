#include <windows.h>                                        
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>


using namespace std;
float angle = 0.0;//параметр отвечающий за движение по оси х
float q = 0.0;//счетчик для Возврата волны
float w = 1.0;//параметр увеличивающий пи
int t = 500;//кол-во линий
float x;//координаты x
float y;//координаты y

		//сохранение пропорций
void proporsion(int w, int h)
{
	if (h == 0)
	{
		h = 1;
	}
	float ratio = float(w) / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 500, 500);
	glMatrixMode(GL_MODELVIEW);
}

//рисование
void paint(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// очистка буфера

	glLineWidth(3);//толщина линии

	glPushMatrix();//сохранение матрицы
	glScalef(0.3, 0.3, 1.0);//масштабирование
	glRotatef(6, 0, 0, 1);//поворот
	glTranslatef(angle, 0, 0);//перемещение
	glBegin(GL_LINE_STRIP);//рисуем линии
	glColor3ub(205, 102, 29);//цвет
							 //флаг
	for (int i = 0; i <= t; i++)
	{
		float a = (float)i / (float)t * 3.1415f * (3.5 * w);//градус
		x = a * 2 - 5;
		y = cos(x) / 2 + 5;
		glVertex2f(x, y);

		x = a * 2 - 5;
		y = cos(x) / 2 - 5;
		glVertex2f(x, y);

	}
	glEnd();
	glPopMatrix();//восстановление матрицы

				  //стороны
				  //левая
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-5, 5);
	glVertex2f(-1.35, 5);
	glVertex2f(-1.35, -5);
	glVertex2f(-5, -5);
	glEnd();
	//правая
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(5, 5);
	glVertex2f(5.0, -5);
	glVertex2f(2.0, -5);
	glVertex2f(2.0, 5);
	glEnd();


	glutSwapBuffers();
	//system("pause");

}
//установка таймера
void Timer(int)
{
	angle -= 0.5;//движение
	w += 0.03;//увеличение градуса
	q++;//счетчик
	if (q == 13)
	{
		angle = angle + 6.5;//возвращение в начальное положение
		q = 0;
		w = 1.0;
	}

	glutTimerFunc(100, Timer, 0);//обновлять экран каждые 100мсек
	glutPostRedisplay();
}

int main(int argc, char **argv) {

	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//double: буфер рисования и буф сторонних вычислений
	glutInitWindowPosition(100, 100);//позиция окна
	glutInitWindowSize(500, 500);//размеры окна
	glutCreateWindow("флаг");//название окна
	glClearColor(1.0, 1.0, 1.0, 1.0);//цвет окна
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);//установка границ

	glutDisplayFunc(paint);//вызов функции рисования
	glutReshapeFunc(proporsion);//вызов функции сохранения пропорций
	glutTimerFunc(0, Timer, 0);//вызов таймера
	glutMainLoop();//основной цикл
	return 1;
}