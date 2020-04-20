#include <cmath>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>  
#include <ctime>
#include <random>

using namespace std;



int window_width = 600;
int window_height = 400;



//��Ƥ��Ч���ı���
bool DrawingLine = true;
enum DrawingState { NonePoint, FirstPoint };//ö�ٻ��Ƶ����н׶� SecondPointҪ��Ҫ�����ٿ���
static DrawingState NowDrawingState = NonePoint;//NowDrawingState ��ǰ���ƽ׶�
int MouseX, MouseY;//�任֮����������

int DrawPointVertices[4];//���������������

//��Ƥ�����
void StartDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);           // ���ԭ��ɫ
    glColor3f(0.0, 0.0, 0.0);
    //ʵʱ���������ʵ����Ƥ��Ч��
    if (NowDrawingState == FirstPoint) {
        if (DrawingLine) {
            glBegin(GL_LINES);
            glVertex2i(DrawPointVertices[0], DrawPointVertices[1]);
            glVertex2i(MouseX, MouseY);
            glEnd();
        }
    }

    glFlush();
}
//����ƶ�
void onMouseMovePassive(int x, int y) {//����ת��
    MouseX = x - window_width / 2;
    MouseY = window_height / 2 - y;

    if (NowDrawingState == FirstPoint) {
        glutPostRedisplay();
    }
}


void mouseClick(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "������£�" << x << "," << y << std::endl;

        //���ڻ���
        if (DrawingLine) {

            if (NowDrawingState == NonePoint) {//һ���㶼û�л�

                DrawPointVertices[0] = MouseX;
                DrawPointVertices[1] = MouseY;
                NowDrawingState = FirstPoint;
                cout << "��һ�����ҵ���" << endl;
                return;
            }
            else if (NowDrawingState == FirstPoint) {//�Ѿ�����һ����

                DrawPointVertices[2] = MouseX;
                DrawPointVertices[3] = MouseY;
                NowDrawingState = NonePoint;//���߽���
                cout << "���߽���" << endl;
                return;
            }
            else {
                return;
            }
        }


    }

}

void init() {

    glClearColor(1.0, 1.0, 1.0, 1.0);       //���ñ���ɫ (R,G,B,alpha)
    glMatrixMode(GL_PROJECTION);            //ͶӰ
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);		//(left right bottom top)

}

void display() {
    glMatrixMode(GL_PROJECTION);//ͶӰ
    glPushMatrix();//��ջ
    glLoadIdentity();//���õ�ǰָ���ľ���Ϊ��λ����.


    glOrtho(-300, 300, -200, 200, -10, 10);//һ��ƽ��ͶӰ�޽��ռ�
    glMatrixMode(GL_MODELVIEW);//ͶӰ������ɺ�ʼ��ͼ,��Ҫ�л���ģ����ͼ���������ȷ��ͼ.
    //glLoadIdentity();


    glutSwapBuffers();//��������������ָ�룬�����Ƶ��ˢ�µ��µĻ�����˸����
    StartDraw();

}




int main(int argc, char* argv[]) {
    //glut��ͨ�õĳ�ʼ������
    glutInit(&argc, argv);
    //��������Ϊ���ó�ʼ��ʾģʽ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("С�ƽ�");
    //�˴�init��������Ϊ�Լ�д��
    init();

    glutDisplayFunc(display);//����ע��һ����ͼ����
    glutMouseFunc(mouseClick);

    glutPassiveMotionFunc(onMouseMovePassive);//ע������ƶ�



    glutMainLoop();
    return 0;
}