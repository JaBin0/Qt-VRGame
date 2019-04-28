attribute vec3 vPos;
attribute vec3 vNormal;
attribute vec2 vText;

varying vec3 fNormal;
varying vec2 fText;
varying vec3 fPos;

uniform mat4 transExt;
uniform mat4 transformInt;

uniform mat4 lookAt;
uniform mat4 perspective;

void main() {
    gl_Position = perspective * lookAt * transExt * transformInt * vec4(vPos, 1.0);
    fPos = vPos;
    fNormal = vNormal;
    fText = vText;
}
