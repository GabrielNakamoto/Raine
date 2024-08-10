#version 410 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture_diffuse1;

void main() {
    // FragColor = vec4(texCoord, 0.0, 1.0);
    // vec2 adjusted_coords = vec2(texCoord.x, -texCoord.y);
    FragColor = texture(texture_diffuse1, texCoord);
    // FragColor = vec4(texCoord, 0.0, 1.0);
    // FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
