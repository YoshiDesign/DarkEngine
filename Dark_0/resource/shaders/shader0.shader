#shader vertex
#version 430
layout(location = 0) in vec3 position;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
};


#shader fragment
#version 430
out vec4 color;

void main(void)
{
	color = vec4(0.0, 0.0, 1.0, 1.0); 
};