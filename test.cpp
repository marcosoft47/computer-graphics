// g++ test.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o test
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <math.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void processInput(GLFWwindow* window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *vertexShaderGaySource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   cor = aColor;\n"
    "}\0";

const char *fragmentShaderPurpleSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.3f, 0.0f, 0.5f, 1.0f);\n"
    "}\n\0";
const char *fragmentShaderPinkSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.0f, 0.5f, 1.0f);\n"
    "}\n\0";
const char *fragmentShaderGradienteSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 cor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(cor, 1.0);\n"
    "}\n\0";
    
int main(int argc, char** argv){
    // Inicialização
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Criação de Janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "aeiou", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    

    // Carregar GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    // ----- Configurar Shaders-----
    unsigned int vertexShader;
    unsigned int fragmentShaderPurple = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderPink = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderGradiente = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramPurple = glCreateProgram();
    unsigned int shaderProgramPink = glCreateProgram();
    unsigned int shaderProgramGradiente = glCreateProgram();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glShaderSource(vertexShader, 1, &vertexShaderGaySource, NULL);
    glCompileShader(vertexShader);
    
    // Shader Purple
    glShaderSource(fragmentShaderPurple, 1, &fragmentShaderPurpleSource, NULL);
    glCompileShader(fragmentShaderPurple);
    // Shader Pink
    glShaderSource(fragmentShaderPink, 1, &fragmentShaderPinkSource, NULL);
    glCompileShader(fragmentShaderPink);
    // Shader Gradiente
    glShaderSource(fragmentShaderGradiente, 1, &fragmentShaderGradienteSource, NULL);
    glCompileShader(fragmentShaderGradiente);
    // shader Gay

    // Link Shaders
    glAttachShader(shaderProgramPurple, vertexShader);
    glAttachShader(shaderProgramPurple, fragmentShaderPurple);
    glLinkProgram(shaderProgramPurple);

    glAttachShader(shaderProgramGradiente, vertexShader);
    glAttachShader(shaderProgramGradiente, fragmentShaderGradiente);
    glLinkProgram(shaderProgramGradiente);

    glAttachShader(shaderProgramPink, vertexShader);
    glAttachShader(shaderProgramPink, fragmentShaderPink);
    glLinkProgram(shaderProgramPink);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderPurple);
    glDeleteShader(fragmentShaderPink);

    // ----- Criar Triângulo -----

    float triangulo1[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f,  // top   
    };
    float triangulogay[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// left  
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right 
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top   
    };
    float triangulo2[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f, -1.0f, 0.0f
    };

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // Primeiro Triângulo
    glBindVertexArray(VAOs[0]); // Vou usar esse VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // Vou usar esse VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangulo1), triangulo1, GL_STATIC_DRAW); // Colocar esses vértices no VBO/Buffer atual
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Leia esse VBO desse jeito
    glEnableVertexAttribArray(0); // O jeito de ler o VBO está nessa posição na lista de leituras
    // Segundo Triângulo
    glBindVertexArray(VAOs[1]); // Vou usar esse VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // Vou usar esse VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangulo2), triangulo2, GL_STATIC_DRAW); // Colocar esses vértices no VBO/Buffer atual
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Leia esse VBO desse jeito
    glEnableVertexAttribArray(0); // O jeito de ler o VBO está nessa posição na lista de leituras

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // ---------- Mainloop ----------
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramPink);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glUseProgram(shaderProgramPurple);

        glUseProgram(shaderProgramGradiente);
        float timeValue = glfwGetTime();
        float greenV = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgramGradiente, "cor");
        glUniform4f(vertexColorLocation, 0.0f, greenV, 0.0f, 1.0f);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h){
    glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}