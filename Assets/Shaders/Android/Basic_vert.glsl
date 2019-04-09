attribute vec3 vPos;
attribute vec2 vText;
attribute vec3 vNormal;

varying highp vec3 fNormal;
varying highp vec2 fText;
varying highp vec3 fPos;

uniform highp mat4 perspective;
uniform highp mat4 lookAt;

void main() {
    gl_Position = perspective * lookAt * vec4(vPos, 1.0);
    fPos = vPos;
    fNormal = vNormal;
    fText = vText;
}
