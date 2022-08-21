#version 330 core

out vec4 FragColor;
// in vec4 vColor;
in vec2 vTexCoord;
uniform sampler2D u_Texture;

void main()
{
   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   vec4 texColor = texture(u_Texture, vTexCoord);
   // FragColor = vColor;
   FragColor = texColor;
}
