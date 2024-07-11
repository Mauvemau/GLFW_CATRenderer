#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 fragColor;
out vec2 texCoord;

void main(){
	gl_Position = aPosition;
	fragColor = aColor;
	texCoord = aTexCoord;
}
