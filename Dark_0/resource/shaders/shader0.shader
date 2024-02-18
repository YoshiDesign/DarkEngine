#shader vertex
#version 430
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