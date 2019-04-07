attribute vec3 vPos;
attribute vec2 vText;
attribute vec3 vNormal;

varying vec3 fColor;
varying vec2 fText;

uniform mat4 perspective;
uniform mat4 lookAt;

void main() {
    gl_Position = perspective * lookAt * vec4(vPos, 1.0);
    fColor = vNormal;
    fText = vText;
}
