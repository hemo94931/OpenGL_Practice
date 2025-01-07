#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

// 顶点着色器源码
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// 橘色片段着色器源码
const char* fragmentShaderOrangeSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

// 蓝色片段着色器源码
const char* fragmentShaderBlueSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.2f, 0.5f, 1.0f, 1.0f);\n"
"}\n";

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

	// 创建顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 检查顶点着色器编译是否成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 创建橘色片段着色器
	unsigned int fragmentShaderOrange;
	fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderOrangeSource, NULL);
	glCompileShader(fragmentShaderOrange);

	// 检查片段着色器编译是否成功
	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 创建蓝色片段着色器
	unsigned int fragmentShaderBlue;
	fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderBlue, 1, &fragmentShaderBlueSource, NULL);
	glCompileShader(fragmentShaderBlue);

	// 检查片段着色器编译是否成功
	glGetShaderiv(fragmentShaderBlue, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderBlue, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 创建橘色着色器程序
	unsigned int shaderProgramOrange;
	shaderProgramOrange = glCreateProgram();

	// 将顶点和片段着色器附加到程序上
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);

	// 检查着色器程序链接是否成功
	glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::RUN_FAILED\n" << std::endl;
	}

	// 创建着色器程序
	unsigned int shaderProgramBlue;
	shaderProgramBlue = glCreateProgram();

	// 将顶点和片段着色器附加到程序上
	glAttachShader(shaderProgramBlue, vertexShader);
	glAttachShader(shaderProgramBlue, fragmentShaderBlue);
	glLinkProgram(shaderProgramBlue);

	// 检查着色器程序链接是否成功
	glGetProgramiv(shaderProgramBlue, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramBlue, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::RUN_FAILED\n" << std::endl;
	}

	// 删除着色器对象，因为它们已经链接到程序中，不再需要
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderBlue);

	// 定义顶点数据
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	// 定义索引数据
	unsigned int indices1[] = { 0, 1, 3 }; // 第一个三角形
	unsigned int indices2[] = { 1, 2, 3 }; // 第二个三角形

	// 创建顶点缓冲对象
	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	// 创建索引缓冲对象
	unsigned int EBOs[2];
	glGenBuffers(2, EBOs);

	// 创建顶点数组对象
	unsigned int VAOs[2];
	glGenVertexArrays(2, VAOs);

	// 绑定顶点数组对象
	glBindVertexArray(VAOs[0]);

	// 绑定顶点缓冲对象并将顶点数据复制到缓冲中
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 绑定索引缓冲对象并将索引数据复制到缓冲中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	// 绑定顶点数组对象
	glBindVertexArray(VAOs[1]);

	// 绑定顶点缓冲对象并将顶点数据复制到缓冲中
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 绑定索引缓冲对象并将索引数据复制到缓冲中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	// 解绑顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 解绑顶点数组对象
	glBindVertexArray(0);

	// 以线框模式绘制
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		// 处理输入
		processInput(window);

		// 清除颜色缓冲
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 使用着色器程序
		glUseProgram(shaderProgramOrange);
		// 绑定顶点数组对象
		glBindVertexArray(VAOs[0]);
		// 绘制三角形
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 使用着色器程序
		glUseProgram(shaderProgramBlue);
		// 绑定顶点数组对象
		glBindVertexArray(VAOs[1]);
		// 绘制三角形
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 交换缓冲并轮询IO事件
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// 删除顶点数组对象和顶点缓冲对象
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	// 删除着色器程序
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramBlue);

	// 终止GLFW
	glfwTerminate();
	return 0;
}
