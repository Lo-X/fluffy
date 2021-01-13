#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec4 u_Color;

out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = u_Color; // set the output variable to a dark-red color
}