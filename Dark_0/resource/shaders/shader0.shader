#shader vertex
#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 v_fragColor;
layout(location = 2) in vec3 normal;
// layout(location = 3) in vec2 uv;

layout(location = 0) out vec4 fragColor;

void main() {
	
	gl_Position = vec4(position, 1.0);
	fragColor = vec4(position, 1.0);
}




#shader fragment
#version 450
layout(location = 0) in vec4 fragColor;
layout(location = 0) out vec4 outColor;
// uniform sampler2D texture_atlas;

void main() {
	outColor = fragColor;
}