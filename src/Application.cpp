#include <iostream>
#define GLFW_INCLUDE_GLU
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include  <cstdlib>
#include<shader.hpp>


void Resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main()
{
	// initialiser GLFW //
	glfwInit();

	// initialiser les parametres //
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// creer la fenetre principale //
	GLFWwindow* window = glfwCreateWindow(800, 800, "TP3 OPENGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to Open Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//std::cout << "Hello" <<std::endl ;

	// fenetre comme contexte pour opengl //
	glfwMakeContextCurrent(window);
	gladLoadGL();
	// init opengl //
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Could not initialize GLAD" << std::endl;
		return -1;
	}
	


	glViewport(0, 0, 800, 800);


	glfwSetFramebufferSizeCallback(window, Resize);

	float vertices[] = {
		1.0f, 0.0f, 0.0f,1.0f,0.0f,0.0f, //V1
		 0.0f, 1.0f, 0.0f,0.0f,0.0f,1.0f, // V2
		 -1.0f, 0.0f, 0.0f,0.0f,1.0f,0.0f // V3
	};

	GLuint VAO;
	GLuint VBO;
	//-Generer et lier le VAO :
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Fournir les sommets  OpenGL pour qu'ils soient places dans le VBO :
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Lier le premier buffer d'attributs (les sommets) et configurer le pointeur :
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	//On indique  OpenGL qu'on utilise un attribut donne:
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(sizeof(float)*3));
	//On indique  OpenGL qu'on utilise un attribut donne:
	glEnableVertexAttribArray(1);
	//Debinder le VAO et le VBO :
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	GLuint ShaderProgram;
	ShaderProgram = LoadShaders("Dependecies/shader/SimpleVertexShader.vertexshader","Dependecies/shader/SimpleFragmentShader.fragmentshader");



	// Main Loop //
	while (!glfwWindowShouldClose(window))
	{
		glUseProgram(ShaderProgram);
		//glUseProgram(ShaderProgram);
		glClearColor(0.82f, 0.40f, 0.17f, 1.0f);
	
		//Dans la boucle d'affichage :
		  //Lier le VAO :
		glBindVertexArray(VAO);
		//Dessiner le triangle :
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//En sortant de la boucle d'affichage, on procede au nettoyage :
		
		
		


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glClear(GL_COLOR_BUFFER_BIT);



	// finishing //
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}