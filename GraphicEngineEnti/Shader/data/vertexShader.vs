#version 110
uniform mat4 MVP;
uniform vec4 uColor;
attribute vec3 vCol;
attribute vec3 vPos;

varying vec3 color;
void main()
{
	
    gl_Position = MVP * vec4(vPos, 1.0);
	if(uColor == vec4(0.0, 0.0, 0.0, 0.0))
    color = vec3(uColor);
	else
	color = vec3(uColor) + vCol;
}