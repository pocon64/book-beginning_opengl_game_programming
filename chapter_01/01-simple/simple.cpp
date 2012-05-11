#include <iostream>
#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

using std::vector;

void error(const std::string& s) {
#ifdef _WIN32
	MessageBox(NULL, s.c_str(), "An error occurred", MB_ICONINFORMATION | MB_OK);
#else
	std::cerr << s << std::endl;
#endif
}

class SimpleApp
{
public:
    static const int WINDOW_WIDTH = 1024;
    static const int WINDOW_HEIGHT = 768;

    SimpleApp();
    bool initialize();
    void resize(int x, int y);
    void prepare();
    void render();
};

SimpleApp::SimpleApp()
{

}

bool SimpleApp::initialize()
{
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
    //Set up the projection matrix
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    return true;
}

void SimpleApp::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 1.0, 6.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
        //Send the vertices and colors for the triangle
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex3f(2.0, 2.5, -1.0);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex3f(-3.5, -2.5, -1.0);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex3f(2.0, -4.0, -1.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        //Send the vertices and colors for the triangle
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glVertex3f(2.1, 1.5, -1.0);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glVertex3f(-1.5, -2.5, -1.0);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glVertex3f(2.3, -4.3, -1.0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        //Send the vertices and colors for the pentagon
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex3f(-1.0, 2.0, 0.0);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex3f(-3.0, -0.5, 0.0);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex3f(-1.5, -3.0, 0.0);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex3f(1.0, -2.0, 0.0);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex3f(1.0, 1.0, 0.0);
    glEnd();
}

void SimpleApp::resize(int w, int h)
{
    //Prevent a divide by zero error
    if (h <= 0)
    {
        h = 1;
    }

    //When we resize the window, we tell OpenGL about the new viewport size
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION); //deprecated
    glLoadIdentity();
    //Then we set up our projection matrix with the correct aspect ratio
    gluPerspective(60.0f, float(w) / float(h), 1.0f, 100.0f); //deprecated

    glMatrixMode(GL_MODELVIEW); //deprecated
    glLoadIdentity(); //deprecated
}

int main(int argc, char** argv)
{
    SimpleApp myApp;

    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        std::cerr << "Could not initialize SDL" << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    std::string title = "BOGLGP Chapter 1";
    SDL_WM_SetCaption(title.c_str(), title.c_str());

    // Create the window
    if (!SDL_SetVideoMode(SimpleApp::WINDOW_WIDTH, SimpleApp::WINDOW_HEIGHT, 0, SDL_OPENGL | SDL_RESIZABLE))
    {
        std::cerr << "Could not create the window" << std::endl;
        return false;
    }

    if (!myApp.initialize())
    {
        SDL_Quit();
        return 1;
    }

    bool done = false;

    while (!done)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {

			switch(event.type) {
				case SDL_QUIT:
					done = true;
				break;
				case SDL_VIDEORESIZE:
					myApp.resize(event.resize.w, event.resize.h);
				break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						done = true;
					}
				break;
				default:
					break;
			}
        }

        myApp.render();
        SDL_GL_SwapBuffers();
    }

    SDL_Quit();

    return 0;
}
