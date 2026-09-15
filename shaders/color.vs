#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos[2];

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos[2];
void main()
{
	FragPos = vec3(view * model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(view * model))) * aNormal;

	gl_Position = projection * view * model * vec4(aPos, 1.0);
	for (int i = 0; i < 2; i++){
		LightPos[i] = vec3(view * vec4(lightPos[i], 1.0));
	}
}