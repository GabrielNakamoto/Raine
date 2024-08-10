#version 410 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D t_diffuse;
uniform sampler2D t_specular;
uniform sampler2D t_normal;

void main() {
    // FragColor = vec4(texCoord, 0.0, 1.0);
    // vec2 adjusted_coords = vec2(texCoord.x, -texCoord.y);
    FragColor = texture(t_diffuse, texCoord);
    // FragColor = vec4(texCoord, 0.0, 1.0);
    // FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
