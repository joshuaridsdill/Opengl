#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <Windows.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    int major = 0;
    int minor = 0;
    int rev = 0;
    glfwGetVersion(&major, &minor, &rev);

    std::cout << "GLFW " << major << "." << minor << "." << rev << " has been loaded" << '\n';

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return -1;

    std::cout << "GLEW " << glGetString(GL_VERSION) << " has been loaded" << '\n';

    GLfloat vertices[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

    GLfloat r = 0;

    GLdouble time = glfwGetTime();
    GLdouble elapsed_time = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        elapsed_time = glfwGetTime() - time;
        time = glfwGetTime();

        std::cout << elapsed_time << '\n';

        /* Render here */
        glClearColor(sinf(r * elapsed_time), 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        //std::cout << sinf(r) << '\n';

        r++;

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "GLFW has been terminated\n";

    return 0;
}