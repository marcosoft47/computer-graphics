#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos[2];

uniform Light light;
uniform Material material;
uniform vec3 objectColor;
uniform vec3 lightColor[2];
uniform vec3 viewPos;

void main()
{
    vec3 result = vec3(0.0);

    for (int i = 0; i < 2; i++)
    {
        // ambient
        vec3 ambient = material.ambient * lightColor[i] * light.ambient;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(LightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = (diff * material.diffuse) * lightColor[i];

        // specular
        vec3 viewDir = normalize(-FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = material.specular * spec * lightColor[i];

        result += (ambient + diffuse + specular) * objectColor;
    }

    FragColor = vec4(result, 1.0);
}