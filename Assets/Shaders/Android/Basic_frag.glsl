varying highp vec3 fNormal;
varying highp vec2 fText;
varying highp vec3 fPos;

uniform sampler2D ourTexture[1];

void main() {
    highp vec3 lightPos = vec3(3.0, 3.0, 3.0);
    highp vec3 lightColor = vec3(1.0, 1.0, 1.0);

    highp float ambientStrength = 0.2;
    highp vec3 ambient = ambientStrength * lightColor;

    highp vec3 norm = normalize(fNormal);
    highp vec3 lightDir = normalize(lightPos - fPos);
    highp float diff = max(dot(norm, lightDir), 0.0);
    highp vec3 diffuse = diff * lightColor;

    highp vec4 textureColor = texture2D(ourTexture[0], fText);
    highp vec3 result = (ambient + diffuse) * textureColor.rgb;

    gl_FragColor = vec4(result, 1.0);
}
