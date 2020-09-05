// �����: ��ǻ�� �׷��Ƚ�
// �ۼ���: ������(2016312644)
// ����������¥: 2020-06-21(��)
// ���α׷� ����: 3X3 Rubik's Cube
// ���α׷� ����: 3D ������Ʈ �𵨸�
// ���α׷� ����: Rubik's Cube�� �𵨸� �ϰ�, �����ϰ� ȸ����ȯ, �̵���ȯ, ������ȯ ���� �𵨺�ȯ �۾��� ����.

#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>

/*--- ��� �� static ����---*/
#define SIDE 0.115  // ť�� ������ �� ���� SIDE��� �����ϰ�, �� ���̴� 0.115�� ��. (�׽�Ʈ �� ���� ������ ���� ����)
static int key = 0; // �޴� ���� ���� (3x3, 2x3, QUIT)

/*--- �������� ---*/
GLint ViewX = 300, ViewY = 300;                                           // ���콺 ��ǥ �� ������ȯ ����
GLfloat rtx = 0.0, rdx = 0.0, rfx = 0.0, rbx = 0.0, rlx = 0.0, rrx = 0.0; // ȸ����ȯ ����
GLint flag = 0;                                                           // wire rendering, solid rendering ���� ����

/*--- �迭 ---*/
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
    {231, 29, 54},   // #E71D36 (������)     TOP
    {46, 196, 182},  // #2EC4B6 (��Ʈ��)     BOTTOM
    {239, 255, 233}, // #EFFFE9 (�Ͼ���迭) FRONT
    {1, 22, 39},     // #011627 (������)     BACK
    {255, 188, 66},  // #FFBC42 (��Ȳ��)     LEFT
    {132, 177, 237}, // #84B1ED (�Ҷ��)     RIGHT
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

/*--- �Լ� ���� ---*/
void Change_Wire_Or_Solid(int i)
{ // �ָ���, ���̾� ����
  if (flag == 1)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ��Ÿ���� ���̾�� ����
  else if (flag == 0)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ��Ÿ���� ���̾�� ����
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

  for (int cubenum = 0; cubenum < 27; cubenum++) // 27�� Loop
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
  glTranslatef(0.12, 0.12, 0.12); // 2X2 CUBE ������
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

  /*--- ���� ��ȯ (gluLookAt) ---*/
  gluLookAt(0.0, 0.0, 0.0, (float)(ViewX - 300) / 300 * 5, (float)(ViewY - 300) / 300 * 5, 1.0, 0.0, 1.0, 0.0);
  //printf("%f %f\n", (float)(ViewX - 300) / 300 * 5, (float)(ViewY - 300) / 300 * 5);

  /*--- ť�� �׸��� ---*/
  if (key == 0 || key == 1)
    DrawCube3by3();
  if (key == 2)
    DrawCube2by2();

  /*--- QUIT�޴� ������ ���α׷� ���� ---*/
  if (key == 3)
    exit(0);

  glFlush();
}

/*--- ���콺 �ݹ� �Լ� ---*/
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

/*--- Ű���� �ݹ� �Լ� ---*/
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

/*--- �޴� �ݹ� �Լ� ---*/
void MyMainMenu(int entryID)
{ //�޴�
  key = entryID;
}

/*--- ���� �Լ� ---*/
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glEnable(GL_DEPTH_TEST);
  glutInitWindowSize(600, 600); // ������ ũ�� 600 X 600
  glutInitWindowPosition(100, 100);
  glutCreateWindow("FINAL PROJECT - 3X3 RUBIK'S CUBE | 2016312644 ������");
  glClearColor(1.0, 1.0, 1.0, 0.0); // ������� �ʱ�ȭ

  /*--- �޴� �ݹ� ---*/
  GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
  glutAddMenuEntry("3X3 CUBE", 1);
  glutAddMenuEntry("2X2 CUBE", 2);
  glutAddMenuEntry("QUIT", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  /*--- �ݹ� �Լ� ȣ�� ---*/
  glutDisplayFunc(MyDisplay);
  glutMouseFunc(MyMouseButton);
  glutMotionFunc(MyMouseMove);
  glutKeyboardFunc(MyKeyboard);

  glEnable(GL_DEPTH_TEST); // ���� ���� Ȱ��ȭ
  glutMainLoop();
  return 0;
}
