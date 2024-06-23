
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


int mapX = 8, mapY = 8, mapS = 64;
int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void drawMap2D() {
	for (int x = 0; x < mapX; x++)
	{
		for (int y = 0; y < mapY; y++)
		{
			if (map[x, y] == 1) { glColor3f(1, 1, 1); }
			else { glColor3f(0, 0, 0); }
		}
	}
}

float px, py; //Player X and Y
void drawPlayer() //Draw a player on the screen
{
	glColor3f(1, 1, 0); 
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2f(px, py);
	glEnd();
}

void buttons(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A && action == GLFW_REPEAT) px -= 0.02f;
	if (key == GLFW_KEY_D && action == GLFW_REPEAT) px += 0.02f;
	if (key == GLFW_KEY_S && action == GLFW_REPEAT) py -= 0.02f;
	if (key == GLFW_KEY_W && action == GLFW_REPEAT) py += 0.02f;
}



int main(void)
{
	//------Setting GLFW/GLEW------//
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(1024, 512, "Raycast Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	//------------------------------------Write after this line only------------------------------------//




	//------Render Loop------//
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.3, 0.3, 0.3, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		drawPlayer();

		glfwSwapBuffers(window);

		glfwSetKeyCallback(window, buttons);
	

		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}