attribute vec3 vPos;
attribute vec3 vColor;

varying highp vec3 fColor;

uniform highp mat4 perspective;
uniform highp mat4 lookAt;

void main() {
    gl_Position = perspective * lookAt * vec4(vPos, 1.0);
    fColor = vColor;
}
