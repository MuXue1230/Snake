#version 460

flat in int cid;

out vec4 outColor;

void main()
{
    if (cid == 0) {
        outColor = vec4(0.0, 1.0, 0.0, 1.0);
    }
    else if (cid == 1) {
        outColor = vec4(0.5, 1.0, 0.5, 1.0);
    }
    else if (cid == 2) {
        outColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
}