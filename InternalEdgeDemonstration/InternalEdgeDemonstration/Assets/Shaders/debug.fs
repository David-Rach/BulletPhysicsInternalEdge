#version 330 core

out vec4 fragment;
in vec3 VertexColor;

void main(){
		fragment = normalize(vec4(VertexColor,1.0));
}