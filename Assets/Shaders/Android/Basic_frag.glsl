varying highp vec3 fColor;
varying highp vec2 fText;

uniform sampler2D ourTexture[1];

void main() {
    highp vec4 imgColor = texture2D(ourTexture[0], fText);
    gl_FragColor = vec4(imgColor.rgb, 1.0);
}
