#include "fakeirisgl.hpp"

#include "GLFW/glfw3.h"
#include <cmath>

void pushmatrix() {}
void popmatrix() {}
void loadmatrix() {}
void scale() {}
void ortho2(float a, float b, float c, float d) {}

void RGBcolor(int r, int g, int b) 
{
    glColor3ub(r, g, b);
}

void circ(float cx, float cy, float r) 
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float degInRad = i * 3.14159 / 180;
        glVertex2f(cx + std::cos(degInRad) * r, cy + std::sin(degInRad) * r);
    }
    glEnd();
} 



void v3f() {}
void endline() {}
void bgnpolygon() {}
void v4f() {}
void endpolygon() {}
void multmatrix(float m[4][4]) {}
void clear() {}
void keepaspect(int x, int y) {}
void prefposition(int a, int b, int c, int d) {}
void doublebuffer() {}
void RGBmode() {}
void gconfig() {}
void qdevice(int i) {}
void ortho(float a, float b, float c, float d, float e, float f) {}
void translate(float a, float b, float c) {}
void getsize(long* a, long* b) {}
void getorigin(long* a, long* b) {}
int qtest() { return 0; }
int qread(short* sp) { return 0; }
void gexit() {}
void reshapeviewport() {}
void swapbuffers() {}
void bgnline() {}
void v2d(double* d) {}
void v2i(int* i) {}
void prefsize(int i, int j) {}
int winopen(const char* cp) { return 0;  }
void cpack(int i) {}
int getvaluator(int i) { return 0; }
void qreset() {}
void qenter(int i, short s) {}
void winset(int i) {}
void winclose(int i) {}
//void drawbody(float m[4][4]) {}
void foreground() {}

