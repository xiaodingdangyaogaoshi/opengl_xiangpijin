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



//橡皮筋效果的变量
bool DrawingLine = true;
enum DrawingState { NonePoint, FirstPoint };//枚举绘制的所有阶段 SecondPoint要不要保留再考虑
static DrawingState NowDrawingState = NonePoint;//NowDrawingState 当前绘制阶段
int MouseX, MouseY;//变换之后的鼠标坐标

int DrawPointVertices[4];//存放两个顶点坐标

//橡皮筋绘制
void StartDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);           // 清空原颜色
    glColor3f(0.0, 0.0, 0.0);
    //实时跟随鼠标来实现橡皮筋效果
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
//鼠标移动
void onMouseMovePassive(int x, int y) {//坐标转换
    MouseX = x - window_width / 2;
    MouseY = window_height / 2 - y;

    if (NowDrawingState == FirstPoint) {
        glutPostRedisplay();
    }
}


void mouseClick(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "鼠标落下：" << x << "," << y << std::endl;

        //正在画线
        if (DrawingLine) {

            if (NowDrawingState == NonePoint) {//一个点都没有画

                DrawPointVertices[0] = MouseX;
                DrawPointVertices[1] = MouseY;
                NowDrawingState = FirstPoint;
                cout << "第一个点找到了" << endl;
                return;
            }
            else if (NowDrawingState == FirstPoint) {//已经有了一个点

                DrawPointVertices[2] = MouseX;
                DrawPointVertices[3] = MouseY;
                NowDrawingState = NonePoint;//画线结束
                cout << "画线结束" << endl;
                return;
            }
            else {
                return;
            }
        }


    }

}

void init() {

    glClearColor(1.0, 1.0, 1.0, 1.0);       //设置背景色 (R,G,B,alpha)
    glMatrixMode(GL_PROJECTION);            //投影
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);		//(left right bottom top)

}

void display() {
    glMatrixMode(GL_PROJECTION);//投影
    glPushMatrix();//入栈
    glLoadIdentity();//重置当前指定的矩阵为单位矩阵.


    glOrtho(-300, 300, -200, 200, -10, 10);//一个平行投影修建空间
    glMatrixMode(GL_MODELVIEW);//投影设置完成后开始画图,需要切换到模型视图矩阵才能正确画图.
    //glLoadIdentity();


    glutSwapBuffers();//交换两个缓冲区指针，解决了频繁刷新导致的画面闪烁问题
    StartDraw();

}




int main(int argc, char* argv[]) {
    //glut包通用的初始化方法
    glutInit(&argc, argv);
    //函数功能为设置初始显示模式
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("小菲酱");
    //此处init（）方法为自己写的
    init();

    glutDisplayFunc(display);//用于注册一个绘图函数
    glutMouseFunc(mouseClick);

    glutPassiveMotionFunc(onMouseMovePassive);//注册鼠标移动



    glutMainLoop();
    return 0;
}