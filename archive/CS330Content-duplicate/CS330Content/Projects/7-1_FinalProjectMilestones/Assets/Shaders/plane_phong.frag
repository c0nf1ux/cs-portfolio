#version 330 core
struct DirLight { vec3 direction; vec3 ambient; vec3 diffuse; vec3 specular; };
struct PointLight { vec3 position; vec3 ambient; vec3 diffuse; vec3 specular; float constant; float linear; float quadratic; };
struct SpotLight { vec3 position; vec3 direction; float cutOff; float outerCutOff; vec3 ambient; vec3 diffuse; vec3 specular; float constant; float linear; float quadratic; };

uniform DirLight uDirLight;
uniform PointLight uPointLight;
uniform SpotLight uSpotLight;
uniform bool uUseSpot;

uniform vec3 uViewPos;
uniform sampler2D uTexture;
uniform float uShininess;

in vec3 vFragPos;
in vec3 vNormal;
in vec2 vTex;

out vec4 FragColor;

vec3 CalcDir(DirLight light, vec3 normal, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec;
    return ambient + diffuse + specular;
}

vec3 CalcPoint(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpot(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular) * attenuation * intensity;
}

void main() {
    vec3 albedo = texture(uTexture, vTex).rgb;
    vec3 normal = normalize(vNormal);
    vec3 viewDir = normalize(uViewPos - vFragPos);

    vec3 color = CalcDir(uDirLight, normal, viewDir, albedo)
               + CalcPoint(uPointLight, normal, vFragPos, viewDir, albedo);

    if (uUseSpot) {
        color += CalcSpot(uSpotLight, normal, vFragPos, viewDir, albedo);
    }

    FragColor = vec4(color, 1.0);
}
