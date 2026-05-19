#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float gradient;

void main()
{
    // FragColor = texture(ourTexture, TexCoord);
    // FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);  
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 + TexCoord.x, TexCoord.y)), gradient);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), gradient);
}