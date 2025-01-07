#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

	Shader myShader("resource/shader/Triangle.vs", "resource/shader/Triangle.fs");

	// 定义顶点数据
	float vertices[] = {
		// 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};

	// 定义索引数据
	unsigned int indices[] = { 0, 1, 2 }; // 第一个三角形

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

	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 设置颜色属性指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 绑定索引缓冲对象并将索引数据复制到缓冲中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 解绑顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 解绑顶点数组对象
	glBindVertexArray(0);

	// 以线框模式绘制
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		// 处理输入
		processInput(window);

		// 清除颜色缓冲
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		// 绑定顶点数组对象
		glBindVertexArray(VAO);
		// 绘制三角形
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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
