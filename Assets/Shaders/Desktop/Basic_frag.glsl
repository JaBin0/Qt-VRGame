varying vec3 fColor;
varying vec2 fText;

uniform sampler2D sampler;

void main() {
    vec4 imgColor = texture2D(sampler, fText);
    gl_FragColor = vec4(imgColor.rgb, 1.0);
}
