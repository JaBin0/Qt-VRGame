attribute vec3 vPos;
attribute vec3 vNormal;
attribute vec2 vText;

varying highp vec3 fNormal;
varying highp vec2 fText;
varying highp vec3 fPos;

uniform highp mat4 transExt;
uniform highp mat4 transformInt;
uniform highp mat4 perspective;
uniform highp mat4 lookAt;

void main() {
    //gl_Position = perspective * lookAt * transformExt * transformInt * vec4(vPos, 1.0);
    gl_Position = perspective * lookAt * transExt * transformInt * vec4(vPos, 1.0);
    fPos = vPos;
    fNormal = vNormal;
    fText = vText;
}
