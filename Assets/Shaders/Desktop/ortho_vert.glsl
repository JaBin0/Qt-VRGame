attribute vec2 vPos;

uniform mat4 ort;
uniform mat4 transform;

void main() {
    gl_Position = ort * transform * vec4(vPos, 1.0, 1.0);
}
