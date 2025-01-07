#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "Shader.h"

// 当窗口大小改变时，调整视口大小的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// 处理输入的函数，按下ESC键时关闭窗口
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// 处理输入的函数，按下ESC键时关闭窗口
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
	// 初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建一个窗口对象
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 定义顶点数据
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	// 定义索引数据
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 }; // 第一个三角形

	// 创建顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// 创建索引缓冲对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// 创建顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// 绑定顶点数组对象
	glBindVertexArray(VAO);

	// 绑定顶点缓冲对象并将顶点数据复制到缓冲中
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 绑定索引缓冲对象并将索引数据复制到缓冲中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 设置颜色属性指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 创建纹理对象
	unsigned int texture[2];
	glGenTextures(2, texture);

	// 创建纹理
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// 设置纹理环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置纹理过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("resource/textures/container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		// 设置纹理环绕方式
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	// 设置纹理环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置纹理过滤方式
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

	// 解绑顶点数组对象
	glBindVertexArray(0);
	// 解绑顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 解绑索引缓冲对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// 解绑纹理
	glBindTexture(GL_TEXTURE_2D, 0);

	// 以线框模式绘制
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

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		// 处理输入
		processInput(window);
		
		// 清除颜色缓冲
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 绑定纹理
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		myShader.use();
		// 绑定顶点数组对象
		glBindVertexArray(VAO);
		// 绘制三角形
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 检查并调用事件
		keyPressed(window, mixValue);
		myShader.setFloat("mixValue", mixValue);

		// 旋转
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		myShader.setMat4("transform", trans);

		myShader2.use();
		// 绑定顶点数组对象
		glBindVertexArray(VAO);
		// 绘制三角形
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		myShader2.setFloat("mixValue", mixValue);

		// 旋转2
		float timeValue1 = glm::abs(glm::sin(glfwGetTime())) + 0.2;
		float timeValue2 = glm::abs(glm::cos(glfwGetTime())) + 0.2;
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(timeValue1, timeValue2, 1));
		myShader.setMat4("transform", trans);

		// 交换缓冲并轮询IO事件
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// 删除顶点数组对象和顶点缓冲对象
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// 终止GLFW
	glfwTerminate();
	return 0;
}
