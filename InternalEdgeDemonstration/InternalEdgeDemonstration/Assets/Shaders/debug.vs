#version 330 core
layout(location = 0) in vec3 Vertex_Position;
layout(location = 1) in vec3 Vertex_Color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 VertexColor;

void main()
{
		gl_Position = Projection * View * Model * vec4(Vertex_Position,1);
		VertexColor = Vertex_Color;
		//gl_Position = vec4(Vertex_Position,1);
}