#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

// ������ɫ��Դ��
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// ��ɫƬ����ɫ��Դ��
const char* fragmentShaderOrangeSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

// ��ɫƬ����ɫ��Դ��
const char* fragmentShaderBlueSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.2f, 0.5f, 1.0f, 1.0f);\n"
"}\n";

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

	// ����������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// ��鶥����ɫ�������Ƿ�ɹ�
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ������ɫƬ����ɫ��
	unsigned int fragmentShaderOrange;
	fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderOrangeSource, NULL);
	glCompileShader(fragmentShaderOrange);

	// ���Ƭ����ɫ�������Ƿ�ɹ�
	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ������ɫƬ����ɫ��
	unsigned int fragmentShaderBlue;
	fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderBlue, 1, &fragmentShaderBlueSource, NULL);
	glCompileShader(fragmentShaderBlue);

	// ���Ƭ����ɫ�������Ƿ�ɹ�
	glGetShaderiv(fragmentShaderBlue, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderBlue, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ������ɫ��ɫ������
	unsigned int shaderProgramOrange;
	shaderProgramOrange = glCreateProgram();

	// �������Ƭ����ɫ�����ӵ�������
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);

	// �����ɫ�����������Ƿ�ɹ�
	glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::RUN_FAILED\n" << std::endl;
	}

	// ������ɫ������
	unsigned int shaderProgramBlue;
	shaderProgramBlue = glCreateProgram();

	// �������Ƭ����ɫ�����ӵ�������
	glAttachShader(shaderProgramBlue, vertexShader);
	glAttachShader(shaderProgramBlue, fragmentShaderBlue);
	glLinkProgram(shaderProgramBlue);

	// �����ɫ�����������Ƿ�ɹ�
	glGetProgramiv(shaderProgramBlue, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramBlue, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::RUN_FAILED\n" << std::endl;
	}

	// ɾ����ɫ��������Ϊ�����Ѿ����ӵ������У�������Ҫ
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderBlue);

	// ���嶥������
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};

	// ������������
	unsigned int indices1[] = { 0, 1, 3 }; // ��һ��������
	unsigned int indices2[] = { 1, 2, 3 }; // �ڶ���������

	// �������㻺�����
	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	// ���������������
	unsigned int EBOs[2];
	glGenBuffers(2, EBOs);

	// ���������������
	unsigned int VAOs[2];
	glGenVertexArrays(2, VAOs);

	// �󶨶����������
	glBindVertexArray(VAOs[0]);

	// �󶨶��㻺����󲢽��������ݸ��Ƶ�������
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������������󲢽��������ݸ��Ƶ�������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	// �󶨶����������
	glBindVertexArray(VAOs[1]);

	// �󶨶��㻺����󲢽��������ݸ��Ƶ�������
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������������󲢽��������ݸ��Ƶ�������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	// ��󶥵㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// ��󶥵��������
	glBindVertexArray(0);

	// ���߿�ģʽ����
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ��������
		processInput(window);

		// �����ɫ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ʹ����ɫ������
		glUseProgram(shaderProgramOrange);
		// �󶨶����������
		glBindVertexArray(VAOs[0]);
		// ����������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ʹ����ɫ������
		glUseProgram(shaderProgramBlue);
		// �󶨶����������
		glBindVertexArray(VAOs[1]);
		// ����������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// �������岢��ѯIO�¼�
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// ɾ�������������Ͷ��㻺�����
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	// ɾ����ɫ������
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramBlue);

	// ��ֹGLFW
	glfwTerminate();
	return 0;
}
