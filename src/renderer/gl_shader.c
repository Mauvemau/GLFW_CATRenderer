#include "cat_renderer.h"

#include <stdio.h>
#include <malloc.h>

const static char* default2DShapeVertexShaderSource =
	"#version 330 core\n\nlayout (location = 0) in vec4 aPosition;\nlayout (location = 1) in vec4 aColor;\n\nout vec4 fragColor;\n\nuniform mat4 u_MVP;\n\nvoid main()\n{\ngl_Position = u_MVP * aPosition;\nfragColor = aColor;\n}\n";

const static char* default2DShapeFragmentShaderSource =
	"#version 330 core\n\nin vec4 fragColor;\nout vec4 outColor;\n\nvoid main()\n{\noutColor = fragColor;\n}\n";

const static char* default2DTextureVertexShaderSource =
	"#version 330 core\n\nlayout (location = 0) in vec4 aPosition;\nlayout (location = 1) in vec4 aColor;\nlayout (location = 2) in vec2 aTexCoord;\n\nout vec4 fragColor;\nout vec2 texCoord;\n\nuniform mat4 u_MVP;\n\nvoid main()\n{\ngl_Position = u_MVP * aPosition;\nfragColor = aColor;\ntexCoord = aTexCoord;\n}\n";

const static char* default2DTextureFragmentShaderSource =
	"#version 330 core\nout vec4 FragColor;\nin vec4 fragColor;\nin vec2 texCoord;\n\nuniform sampler2D ourTexture;\n\nvoid main()\n{\nFragColor = texture(ourTexture, texCoord) * fragColor;\n}\n";

static unsigned int default2DShapeShaderProgram;
static unsigned int default2DTextureShaderProgram;

static unsigned int currentShader;

static const char* getShaderType(unsigned int type) {
	switch (type) {
	case GL_VERTEX_SHADER:
		return "VERTEX SHADER";
	case GL_FRAGMENT_SHADER:
		return "FRAGMENT SHADER";
	default:
		return "OTHER SHADER";
	}
}

static unsigned int compileShader(unsigned int type, const char* source) {
	unsigned int id = glCreateShader(type);
	const char* src = source;
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			printf("(Failed to compile %s Shader) %s\n", getShaderType(type), message);
		}
		else {
			printf("(Failed to compile %s Shader) Unknown error\n", getShaderType(type));
		}
		glDeleteShader(id);
		return 0;
	}
	else {
		printf("Compiled %s successfully!\n", getShaderType(type));
	}

	return id;
}

unsigned int createShader(const char* vertexShader, const char* fragmentShader) {
	printf("Creating Shader Program...\n");
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	if (vs == 0 || fs == 0) {
		printf("Failed to create shader program due to shader compilation error.\n");
		if (vs != 0) glDeleteShader(vs);
		if (fs != 0) glDeleteShader(fs);
		glDeleteProgram(program);
		return 0;
	}

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (!isLinked) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			char* message = (char*)alloca(length * sizeof(char));
			glGetProgramInfoLog(program, length, &length, message);
			printf("Failed to link shader program: %s\n", message);
		}
		else {
			printf("Failed to link shader program: Unknown error\n");
		}
		glDeleteProgram(program);
		return 0;
	}

	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	printf("(%d) Shader program created!\n", program);
	return program;
}

void destroyShader(unsigned int program) {
	printf("(%d) Unloading shader...\n", program);
	glDeleteProgram(program);
	printf("Shader unloaded!\n");
}

const char* loadShader(const char* filePath) {
	return loadTextFile(filePath);
}

void loadDefaultShaders() {
	printf("Loading default shaders...\n");
	default2DShapeShaderProgram = createShader(default2DShapeVertexShaderSource, default2DShapeFragmentShaderSource);
	default2DTextureShaderProgram = createShader(default2DTextureVertexShaderSource, default2DTextureFragmentShaderSource);
	useDefaultTextureShaderProgram();
}

void unloadDefaultShaders() {
	printf("Unloading default shaders...\n");
	glDeleteProgram(default2DShapeShaderProgram);
	glDeleteProgram(default2DTextureShaderProgram);
}

void useShaderProgram(unsigned int shaderProgram) {
	currentShader = shaderProgram;
	glUseProgram(shaderProgram);
}

void useDefaultShapeShaderProgram() {
	useShaderProgram(default2DShapeShaderProgram);
}

void useDefaultTextureShaderProgram() {
	useShaderProgram(default2DTextureShaderProgram);
}

unsigned int getCurrentShader() {
	return currentShader;
}
