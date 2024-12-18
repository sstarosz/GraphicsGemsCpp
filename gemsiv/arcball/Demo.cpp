/***** Demo.c *****/
/* Ken Shoemake, 1993 */

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif
//#include "../../fakeirisgl.hpp"

#include "BallAux.hpp"
#include "Body.hpp"
#include "Ball.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#include <iostream>

/* vvv Temporary workarounds vvv*/
using Device = int;

/* ^^^ End of Temporary workarounds ^^^*/

typedef struct {double x, y;} Place;
typedef struct {int x, y;} IPoint;


#define RADIUS	  (0.75)
#define CNTRLDN	  1
#define SHIFTDN	  2

long int gid = 0;
short active = 0;
Device dev = 0;
short val = 0;
IPoint winsize = {0, 0};
IPoint winorig = {0, 0};
Place mouseNow = {0, 0};
int keysDown = 0;
HVect vNow = {0, 0, 0, 0};
BallData ball;


// GLFW error callback
void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}


/* Draw the object being controlled. */
void body_Draw(BallData *ball)
{
	HMatrix mNow;
	Ball_Value(ball, mNow);
	glPushMatrix();
	glMultMatrixf((float *)mNow);
	glScalef(RADIUS, RADIUS, RADIUS);
	drawbody(mNow);
	glPopMatrix();
}

/* Draw whole window, including controller. */
void scene_Draw(BallData *ball)
{
	glColor3f(0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	body_Draw(ball);
	Ball_Draw(ball);
}


void handleUserInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	//Left mouse button
	if(glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		Ball_BeginDrag(&ball);
	}
	else
	{
		Ball_EndDrag(&ball);
	}

	//Control key
	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
	{
		keysDown = (keysDown & ~CNTRLDN) | CNTRLDN;
	}
	else
	{
		keysDown = keysDown & ~CNTRLDN;
	}

	glfwGetWindowPos(window, &winorig.x, &winorig.y);
	glfwGetWindowSize(window, &winsize.x, &winsize.y);
	glfwGetCursorPos(window, &mouseNow.x, &mouseNow.y);

	Ball_Mouse(&ball, vNow);
}

void updateScene(BallData* ball)
{
	Ball_Update(ball);
}

void drawScene(GLFWwindow* window, BallData* ball)
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
	{
		ImGui::Begin("Arcball Demo");
		
		ImGui::End();
	}

	ImGui::Render();

	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);

	scene_Draw(ball);
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}



int main(void)
{

	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(640, 640, "Arcball Demo", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL2_Init();

	//
	glOrtho(-1.f, 1.f, -1.f, 1.f, 0.001f, 100000.f);
	glTranslatef(0.f, 0.f, -3.f);

	//Initialize the ball
	Ball_Init(&ball);
	Ball_Place(&ball, qOne, RADIUS);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		handleUserInput(window);
		updateScene(&ball);
		drawScene(window, &ball);

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

/*

    keepaspect(1, 1);
    prefposition(50, 950, 50, 950);
    gid = winopen("Arcball Demo");
    doublebuffer();
    RGBmode();
    gconfig();
    qdevice(WINSHUT);
    qdevice(MOUSEX); qdevice(MOUSEY); qdevice(LEFTMOUSE);
    qdevice(LEFTCTRLKEY); qdevice(RIGHTCTRLKEY);
    qdevice(LEFTSHIFTKEY); qdevice(RIGHTSHIFTKEY);
    qdevice(CAPSLOCKKEY);
    //perspective(400, 1.f, 0.001, 100000.f); 
    ortho(-1.f, 1.f, -1.f, 1.f, 0.001f, 100000.f);
    translate(0.f, 0.f, -3.f);
    active = 0;

    getsize(&winsize.x, &winsize.y);
    getorigin(&winorig.x, &winorig.y);
    keysDown = 0;
    Ball_Init(&ball);
    Ball_Place(&ball, qOne, RADIUS);

    while (TRUE) {
	while (qtest()) {	 // process queued events
	    dev = qread(&val);
	    switch (dev) {
		case WINSHUT:	 // exit program
		    gexit();
		    exit(0);
		    break;
		case INPUTCHANGE:
		    active = val;
		    break;
		case REDRAW:
		    reshapeviewport();
		    getsize(&winsize.x, &winsize.y);
		    getorigin(&winorig.x, &winorig.y);
		    break;
		case MOUSEX:
		    mouseNow.x = val;
		    vNow.x = 2.f*(mouseNow.x - winorig.x)/winsize.x - 1.f;
		    break;
		case MOUSEY:
		    mouseNow.y = val;
		    vNow.y = 2.f*(mouseNow.y - winorig.y)/winsize.y - 1.f;
		    break;
		case LEFTMOUSE:
		    if (val) Ball_BeginDrag(&ball);
		    else     Ball_EndDrag(&ball);
		    break;
		case LEFTCTRLKEY: case RIGHTCTRLKEY:
		    keysDown = (keysDown&~CNTRLDN)|(val? CNTRLDN : 0);
		    break;
		case LEFTSHIFTKEY: case RIGHTSHIFTKEY:
		    keysDown = (keysDown&~SHIFTDN)|(val? SHIFTDN : 0);
		    break;
		case CAPSLOCKKEY:
		    if (val) Ball_ShowResult(&ball);
		    else     Ball_HideResult(&ball);
		    break;
		default:
		    break;
	    }			 // end of switch
	    Ball_Mouse(&ball, vNow);
	    switch (keysDown) {
		case CNTRLDN+SHIFTDN: Ball_UseSet(&ball, OtherAxes);  break;
		case CNTRLDN:	      Ball_UseSet(&ball, BodyAxes);   break;
		case	     SHIFTDN: Ball_UseSet(&ball, CameraAxes); break;
		default:	      Ball_UseSet(&ball, NoAxes);     break;
	    }
	}			 // end of while on qtest
	Ball_Update(&ball);
	scene_Draw(&ball);	 // draw into the back buffer
	swapbuffers();		 // and show it in the front buffer
    }
    // NOT REACHED

	*/

