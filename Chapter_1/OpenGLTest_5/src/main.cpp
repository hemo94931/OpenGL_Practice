#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
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

// ��������ĺ���������ESC��ʱ�رմ���
void keyPressed(GLFWwindow* window, float& mixValue)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (mixValue >= 0.9998)
			mixValue = 1.0;
		else
			mixValue += 0.0002;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (mixValue <= 0.0002)
			mixValue = 0.0;
		else
			mixValue -= 0.0002;
	}
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

	// ���嶥������
	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};

	// ������������
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 }; // ��һ��������

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

	// ������������󲢽��������ݸ��Ƶ�������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������ɫ����ָ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// �����������
	unsigned int texture[2];
	glGenTextures(2, texture);

	// ��������
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// ���������Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// ����������˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("resource/textures/container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		// ���������Ʒ�ʽ
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	// ���������Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// ����������˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("resource/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// ��󶥵��������
	glBindVertexArray(0);
	// ��󶥵㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// ��������������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// �������
	glBindTexture(GL_TEXTURE_2D, 0);

	// ���߿�ģʽ����
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader myShader("resource/shader/Triangle.vs", "resource/shader/Triangle.fs");

	myShader.use();
	myShader.setInt("texture1", 0);
	myShader.setInt("texture2", 1);

	float mixValue = 0.0f;
	myShader.setFloat("mixValue", mixValue);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	myShader.setMat4("transform", trans);

	Shader myShader2("resource/shader/Triangle.vs", "resource/shader/Triangle.fs");

	myShader2.use();
	myShader2.setInt("texture1", 0);
	myShader2.setInt("texture2", 1);
	myShader2.setFloat("mixValue", mixValue);

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ��������
		processInput(window);
		
		// �����ɫ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ������
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		myShader.use();
		// �󶨶����������
		glBindVertexArray(VAO);
		// ����������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ��鲢�����¼�
		keyPressed(window, mixValue);
		myShader.setFloat("mixValue", mixValue);

		// ��ת
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		myShader.setMat4("transform", trans);

		myShader2.use();
		// �󶨶����������
		glBindVertexArray(VAO);
		// ����������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		myShader2.setFloat("mixValue", mixValue);

		// ��ת2
		float timeValue1 = glm::abs(glm::sin(glfwGetTime())) + 0.2;
		float timeValue2 = glm::abs(glm::cos(glfwGetTime())) + 0.2;
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(timeValue1, timeValue2, 1));
		myShader.setMat4("transform", trans);

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
