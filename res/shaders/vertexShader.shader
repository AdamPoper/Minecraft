#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;
// layout (location = 1) in vec4 aColor;

// out vec4 vColor;
out vec2 vTexCoord;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main()
{
   // gl_Position = u_projection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);
   // vColor = aColor;
   vTexCoord = texCoord;
}
