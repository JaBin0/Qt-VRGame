attribute vec3 vPos;
attribute vec3 vColor;

varying vec3 fColor;

uniform mat4 perspective;
uniform mat4 lookAt;

void main() {
    gl_Position = perspective * lookAt * vec4(vPos, 1.0);
    fColor = vColor;
}
