// 과목명: 컴퓨터 그래픽스
// 작성자: 김태현(2016312644)
// 최종수정날짜: 2020-06-21(일)
// 프로그램 주제: 3X3 Rubik's Cube
// 프로그램 목적: 3D 오브젝트 모델링
// 프로그램 설명: Rubik's Cube를 모델링 하고, 간단하게 회전변환, 이동변환, 시점변환 등의 모델변환 작업을 수행.

#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>

/*--- 상수 및 static 변수---*/
#define SIDE 0.115  // 큐브 조각의 한 변을 SIDE라고 정의하고, 그 길이는 0.115로 함. (테스트 후 가장 적합한 길이 선정)
static int key = 0; // 메뉴 선택 변수 (3x3, 2x3, QUIT)

/*--- 전역변수 ---*/
GLint ViewX = 300, ViewY = 300;                                           // 마우스 좌표 및 시점변환 변수
GLfloat rtx = 0.0, rdx = 0.0, rfx = 0.0, rbx = 0.0, rlx = 0.0, rrx = 0.0; // 회전변환 변수
GLint flag = 0;                                                           // wire rendering, solid rendering 구분 변수

/*--- 배열 ---*/
GLfloat vertices[8][3] = {
    {SIDE, SIDE, SIDE},    // V0 + + +
    {SIDE, SIDE, -SIDE},   // V1 + + -
    {-SIDE, SIDE, -SIDE},  // V2 - + -
    {-SIDE, SIDE, SIDE},   // V3 - + +
    {SIDE, -SIDE, SIDE},   // V4 + - +
    {SIDE, -SIDE, -SIDE},  // V5 + - -
    {-SIDE, -SIDE, -SIDE}, // V6 - - -
    {-SIDE, -SIDE, SIDE},  // V7 - - +
};
GLubyte colors[6][3] = {
    {231, 29, 54},   // #E71D36 (붉은색)     TOP
    {46, 196, 182},  // #2EC4B6 (민트색)     BOTTOM
    {239, 255, 233}, // #EFFFE9 (하얀색계열) FRONT
    {1, 22, 39},     // #011627 (검은색)     BACK
    {255, 188, 66},  // #FFBC42 (주황색)     LEFT
    {132, 177, 237}, // #84B1ED (소라색)     RIGHT
};
GLfloat positions[27][3] = {
    //Left Top
    {0.24, 0.24, 0.24},
    {0.24, 0.24, 0},
    {0.24, 0.24, -0.24},
    //Center Top
    {0, 0.24, 0.24},
    {0, 0.24, 0},
    {0, 0.24, -0.24},
    //Right Top
    {-0.24, 0.24, 0.24},
    {-0.24, 0.24, 0},
    {-0.24, 0.24, -0.24},

    //Left Center
    {0.24, 0, 0.24},
    {0.24, 0, 0},
    {0.24, 0, -0.24},
    //Center Center
    {0, 0, 0.24},
    {0, 0, 0},
    {0, 0, -0.24},
    //Right Center
    {-0.24, 0, 0.24},
    {-0.24, 0, 0},
    {-0.24, 0, -0.24},

    //Left Bottom
    {0.24, -0.24, 0.24},
    {0.24, -0.24, 0},
    {0.24, -0.24, -0.24},
    //Center Bottom
    {0, -0.24, 0.24},
    {0, -0.24, 0},
    {0, -0.24, -0.24},
    //Right Bottom
    {-0.24, -0.24, 0.24},
    {-0.24, -0.24, 0},
    {-0.24, -0.24, -0.24},
};

/*--- 함수 정의 ---*/
void Change_Wire_Or_Solid(int i)
{ // 솔리드, 와이어 선택
  if (flag == 1)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 스타일을 와이어로 변경
  else if (flag == 0)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 스타일을 와이어로 변경
}
void DrawBaseCube()
{
  glBegin(GL_QUADS);
  {
    // Top
    glColor3ubv(colors[0]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[3]);

    // Bottom
    glColor3ubv(colors[1]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[7]);

    // Front
    glColor3ubv(colors[2]);
    glVertex3fv(vertices[7]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[3]);

    // Back
    glColor3ubv(colors[3]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[5]);

    // Right
    glColor3ubv(colors[4]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[4]);

    // Left
    glColor3ubv(colors[5]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[7]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[2]);
  }
  glEnd();
}
void DrawCube3by3()
{

  for (int cubenum = 0; cubenum < 27; cubenum++) // 27번 Loop
  {
    glPushMatrix();
    Change_Wire_Or_Solid(flag);
    if (positions[cubenum][1] > 0)
      glRotatef(rtx, 0.0, 1.0, 0.0);
    if (positions[cubenum][1] < 0)
      glRotatef(rdx, 0.0, -1.0, 0.0);
    if (positions[cubenum][2] > 0)
      glRotatef(rfx, 0.0, 0.0, 1.0);
    if (positions[cubenum][2] < 0)
      glRotatef(rbx, 0.0, 0.0, -1.0);
    if (positions[cubenum][0] > 0)
      glRotatef(rlx, 1.0, 0.0, 0.0);
    if (positions[cubenum][0] < 0)
      glRotatef(rrx, -1.0, 0.0, 0.0);

    glTranslatef(positions[cubenum][0], positions[cubenum][1], positions[cubenum][2]);
    DrawBaseCube();
    glPopMatrix();
  }
  glutPostRedisplay();
}
void DrawCube2by2()
{

  glPushMatrix();
  glTranslatef(0.12, 0.12, 0.12); // 2X2 CUBE 시작점
  for (int x = -1; x < 1; x++)
  {
    for (int y = -1; y < 1; y++)
    {
      for (int z = -1; z < 1; z++)
      {
        glPushMatrix();
        Change_Wire_Or_Solid(flag);
        glTranslatef(x * 0.24, y * 0.24, z * 0.24);
        DrawBaseCube();
        glPopMatrix();
      }
    }
  }
  glPopMatrix();
  glutPostRedisplay();
}
void MyDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /*--- 시점 변환 (gluLookAt) ---*/
  gluLookAt(0.0, 0.0, 0.0, (float)(ViewX - 300) / 300 * 5, (float)(ViewY - 300) / 300 * 5, 1.0, 0.0, 1.0, 0.0);
  //printf("%f %f\n", (float)(ViewX - 300) / 300 * 5, (float)(ViewY - 300) / 300 * 5);

  /*--- 큐브 그리기 ---*/
  if (key == 0 || key == 1)
    DrawCube3by3();
  if (key == 2)
    DrawCube2by2();

  /*--- QUIT메뉴 누르면 프로그램 종료 ---*/
  if (key == 3)
    exit(0);

  glFlush();
}

/*--- 마우스 콜백 함수 ---*/
void MyMouseButton(GLint Button, GLint State, GLint x, GLint y)
{
  if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
  {
    ViewX = x;
    ViewY = y;
  }
}
void MyMouseMove(GLint x, GLint y)
{
  ViewX = x;
  ViewY = y;

  glutPostRedisplay();
}

/*--- 키보드 콜백 함수 ---*/
void MyKeyboard(unsigned char Key, int X, int Y)
{
  switch (Key)
  {
  case 'q':
  case 'Q':
    exit(0);
    break;

  case 'w':
    flag = 1;
    break;
  case 's':
    flag = 0;
    break;

  case 't':
  case 'T':
    rtx += 90.0;
    break;

  case 'd':
  case 'D':
    rdx += 90.0;
    break;

  case 'f':
  case 'F':
    rfx += 90.0;
    break;

  case 'b':
  case 'B':
    rbx += 90.0;
    break;

  case 'l':
  case 'L':
    rlx += 90.0;
    break;

  case 'r':
  case 'R':
    rrx += 90.0;
    break;
  }
}

/*--- 메뉴 콜백 함수 ---*/
void MyMainMenu(int entryID)
{ //메뉴
  key = entryID;
}

/*--- 메인 함수 ---*/
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glEnable(GL_DEPTH_TEST);
  glutInitWindowSize(600, 600); // 윈도우 크기 600 X 600
  glutInitWindowPosition(100, 100);
  glutCreateWindow("FINAL PROJECT - 3X3 RUBIK'S CUBE | 2016312644 김태현");
  glClearColor(1.0, 1.0, 1.0, 0.0); // 흰색으로 초기화

  /*--- 메뉴 콜백 ---*/
  GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
  glutAddMenuEntry("3X3 CUBE", 1);
  glutAddMenuEntry("2X2 CUBE", 2);
  glutAddMenuEntry("QUIT", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  /*--- 콜백 함수 호출 ---*/
  glutDisplayFunc(MyDisplay);
  glutMouseFunc(MyMouseButton);
  glutMotionFunc(MyMouseMove);
  glutKeyboardFunc(MyKeyboard);

  glEnable(GL_DEPTH_TEST); // 깊이 버퍼 활성화
  glutMainLoop();
  return 0;
}
