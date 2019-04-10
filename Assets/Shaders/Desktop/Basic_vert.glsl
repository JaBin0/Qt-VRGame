attribute vec3 vPos;
attribute vec3 vNormal;
attribute vec2 vText;

varying vec3 fNormal;
varying vec2 fText;
varying vec3 fPos;

uniform mat4 perspective;
uniform mat4 lookAt;

void main() {
    gl_Position = perspective * lookAt * vec4(vPos, 1.0);
    fPos = vPos;
    fNormal = vNormal;
    fText = vText;
}
