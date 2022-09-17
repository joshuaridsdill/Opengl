#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <Windows.h>

static GLuint CompileShader(GLuint type, const std::string& source)
{
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << '\n';
        std::cout << message << '\n';
        glDeleteShader(id);
        return 0;
    }

    std::cout << "Successfully compiled " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << '\n';

    return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";
    
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    GLuint shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    GLfloat r = 0;

    GLdouble time = glfwGetTime();
    GLdouble elapsed_time = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        elapsed_time = glfwGetTime() - time;
        time = glfwGetTime();

        std::cout << elapsed_time << '\n';

        std::cout << 1 / elapsed_time << '\n';

        /* Render here */
        glClearColor(sinf(r), 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        //std::cout << sinf(r) << '\n';

        r+=elapsed_time;

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