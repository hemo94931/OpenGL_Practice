#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

// �����ڴ�С�ı�ʱ�������ӿڴ�С�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// ��������ĺ���������ESC��ʱ�رմ���
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	// ��ʼ��GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����һ�����ڶ���
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader myShader("resource/shader/Triangle.vs", "resource/shader/Triangle.fs");

	// ���嶥������
	float vertices[] = {
		// λ��              // ��ɫ
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};

	// ������������
	unsigned int indices[] = { 0, 1, 2 }; // ��һ��������

	// �������㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// ���������������
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// ���������������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// �󶨶����������
	glBindVertexArray(VAO);

	// �󶨶��㻺����󲢽��������ݸ��Ƶ�������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������ɫ����ָ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ������������󲢽��������ݸ��Ƶ�������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ��󶥵㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// ��󶥵��������
	glBindVertexArray(0);

	// ���߿�ģʽ����
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ��������
		processInput(window);

		// �����ɫ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		// �󶨶����������
		glBindVertexArray(VAO);
		// ����������
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		// �������岢��ѯIO�¼�
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// ɾ�������������Ͷ��㻺�����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// ��ֹGLFW
	glfwTerminate();
	return 0;
}
