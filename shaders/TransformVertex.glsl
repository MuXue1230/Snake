#version 460

uniform mat4 worldTransform;
uniform mat4 viewProj;

uniform int colorId;

in vec3 inPosition;

out int cid;

void main()
{
    cid = colorId;
    vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * worldTransform * viewProj;
}