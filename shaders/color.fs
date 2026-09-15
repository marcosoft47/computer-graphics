#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos[2];

uniform vec3 objectColor;
uniform vec3 lightColor[2];
uniform vec3 viewPos;

void main()
{
    vec3 result = vec3(0.0);

    for (int i = 0; i < 2; i++)
    {
        // ambient
        float ambientStrength = 0.3;
        vec3 ambient = ambientStrength * lightColor[i];

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(LightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor[i];

        // specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(-FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = specularStrength * spec * lightColor[i];

        result += (ambient + diffuse + specular) * objectColor;
    }

    FragColor = vec4(result, 1.0);
}