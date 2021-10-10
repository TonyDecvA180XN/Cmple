#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

struct DirLight {
    vec3 Position;
    vec3 Color;
};

struct PointLight {
    vec3 Position;
    vec3 Color;
};

struct SpotLight {
    vec3 Position;
    vec3 Color;
    vec3 Direction;
    float angleInner;
    float angleOuter;
};

const float gamma = 2.2;
const int N_POINT_LIGHTS = 16;

uniform DirLight dirLight;
uniform PointLight pointLight[N_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform sampler2D diffuseTexture;
uniform vec3 viewPos;

uniform float exposure;

vec3 CalculateDirectionalLight() {
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 lightDir = normalize(dirLight.Position - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = dirLight.Color * diff * color;

    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    vec3 specular = dirLight.Color * spec;

    return diffuse + specular;
}

vec3 CalculatePointLight() {
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 result = vec3(0.0);

    for (int i = 0; i < N_POINT_LIGHTS; i++) {
        vec3 lightDir = normalize(pointLight[i].Position - fs_in.FragPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = pointLight[i].Color * diff * color;
        float distance = length(fs_in.FragPos - pointLight[i].Position);
        diffuse *= 1.0 / (distance * distance);

        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
        vec3 specular = pointLight[i].Color * spec;

        result += diffuse + specular;
    }

    return result;
}

vec3 CalculateSpotLight() {
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lighting = vec3(0.0);

    vec3 lightDir = normalize(spotLight.Position - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = spotLight.Color * diff * color;
    float distance = length(fs_in.FragPos - spotLight.Position);
    diffuse *= 1.0 / (distance * distance);

    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    vec3 specular = spotLight.Color * spec;

    float theta = dot(lightDir, normalize(-spotLight.Direction));
    float epsilon = spotLight.angleInner - spotLight.angleOuter;
    float intensity = clamp((theta - spotLight.angleOuter) / epsilon, 0.0, 1.0);

    return (diffuse + specular) * intensity;
}

void main() {
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 result = vec3(0.0);

    result += CalculateDirectionalLight();
    result += CalculatePointLight();
    result += CalculateSpotLight();

    result = vec3(1.0) - exp(-result * exposure);
    result = pow(result, vec3(1.0 / gamma));

    FragColor = vec4(result, 1.0);
}
