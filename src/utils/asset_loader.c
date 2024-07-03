#include "cat_renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>

static FILE* openFile(const char* filePath) {
	FILE* file = fopen(filePath, "r");
	if (file == NULL) {
		printf("Error opening the file: %s\n", filePath);
	}
	return file;
}

static bool closeFile(FILE* file, const char* filePath) {
	if (fclose(file) != 0) {
		printf("Error closing the file: %s\n", filePath);
		return false;
	}
	return true;
}

bool fileExists(const char* filePath) {
	FILE* file = openFile(filePath);
	if (file != NULL) {
		closeFile(file, filePath);
		return true;
	}
	return false;
}

unsigned int loadTextureAdvanced(const char* filePath, GLint wrapping, GLint filtering) {
	printf("Loading texture at %s...\n", filePath);
	if (!fileExists(filePath)) {
		printf("No texture was found at the specified path!\n");
		return 0;
	}

	unsigned int texture = 0;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		printf("The texture (%d)%s was loaded!\n", texture, filePath);
	}
	else {
		printf("Failed to load texture!!\n");
		printf("Reason: %s\n", stbi_failure_reason());
		glDeleteTextures(1, &texture);
		return 0;
	}

	stbi_image_free(data);
	return texture;
}

unsigned int loadTexture(const char* filepath) {
	return loadTextureAdvanced(filepath, GL_REPEAT, GL_NEAREST);
}

const char* loadTextFile(const char* filePath) {
	if (!fileExists(filePath))
		return "NULL";
	
	FILE* file = openFile(filePath);
	
	if (fseek(file, 0, SEEK_END) != 0) {
		printf("Error seeking to the end of the file: %s\n", filePath);
		closeFile(file, filePath);
		return "NULL";
	}

	long file_size = ftell(file);
	if (file_size == -1) {
		printf("Error determining file size: %s\n", filePath);
		closeFile(file, filePath);
		return "NULL";
	}
	
	if (fseek(file, 0, SEEK_SET) != 0) {
		printf("Error seeking to the beginning of the file: %s\n", filePath);
		closeFile(file, filePath);
		return "NULL";
	}

	// Removing BOMS in case of UTF-8 file
	int bom1 = fgetc(file);
	int bom2 = fgetc(file);
	int bom3 = fgetc(file);

	if (!(bom1 == 0xEF && bom2 == 0xBB && bom3 == 0xBF)) {
		// If the file doesn't start with UTF-8 BOM, seek back to the beginning of the file
		if (fseek(file, 0, SEEK_SET) != 0) {
			printf("Error seeking to the beginning of the file: %s\n", filePath);
			closeFile(file, filePath);
			return "NULL";
		}
	}

	char* text = (char*)malloc(file_size + 1);
	if (text == NULL) {
		printf("Memory allocation error.\n");
		closeFile(file, filePath);
		return "NULL";
	}

	char* cursor = text;
	int c;
	while ((c = fgetc(file)) != EOF) {
		*cursor++ = (char)c;
	}
	*cursor = '\0';

	if (!closeFile(file, filePath)) {
		free(text);
		return "NULL";
	}

	return text;
}

void unloadImage(unsigned int id) {
	glDeleteTextures(1, &id);
	printf("Texture (%d) was unloaded!\n", id);
}
