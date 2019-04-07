attribute vec3 vPos;
attribute vec2 vText;
attribute vec3 vNormal;

varying highp vec3 fColor;
varying highp vec2 fText;

uniform highp mat4 perspective;
uniform highp mat4 lookAt;

void main() {
    gl_Position = perspective * lookAt * vec4(vPos, 1.0);
    fColor = vNormal;
}
