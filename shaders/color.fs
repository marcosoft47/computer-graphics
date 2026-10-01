#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
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
in vec2 TexCoords;

uniform Light light;
uniform Material material;
uniform vec3 lightColor[2];
uniform vec3 viewPos;

void main()
{
    vec3 result = vec3(0.0);

    for (int i = 0; i < 2; i++)
    {
        // ambient
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(LightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor[i] * vec3(texture(material.diffuse, TexCoords));

        // specular
        vec3 viewDir = normalize(-FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

        // emission

        vec3 emission = texture(material.emission, TexCoords).rgb;

        result += (ambient + diffuse + specular + emission);
    }

    FragColor = vec4(result, 1.0);
}