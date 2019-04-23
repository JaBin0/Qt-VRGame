varying vec3 fNormal;
varying vec3 fPos;
varying vec2 fText;

uniform sampler2D sampler;

void main() {
    vec3 lightPos = vec3(3.0, 3.0, 3.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(lightPos - fPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec4 textureColor = texture2D(sampler, fText);

    vec3 result = (ambient + diffuse) * textureColor.rgb;

    gl_FragColor = vec4(result, 1.0);
}
