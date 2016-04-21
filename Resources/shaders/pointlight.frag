#ifdef GL_ES
precision highp float;
#endif
//fixed number of lights
#define N_LIGHTS 3




varying vec2 v_texCoord;
uniform sampler2D u_normals;

uniform vec2 u_contentSize;
uniform vec2 u_spritePosInSheet;
uniform vec2 u_spriteSizeRelToSheet;
uniform vec2 u_spriteOffset;

uniform vec3  u_ambientColor;
uniform vec3  u_lightPos[N_LIGHTS];
uniform vec3  u_lightColor[N_LIGHTS];

uniform int  u_spriteRotated;
uniform int  u_lightsNumber;



uniform float u_brightness[N_LIGHTS];
uniform float u_cutoffRadius[N_LIGHTS];
uniform float u_halfRadius[N_LIGHTS];




void main(void)
{
    vec4 texColor=texture2D(CC_Texture0, v_texCoord);
    vec3 normal=texture2D(u_normals, v_texCoord).rgb;
	normal=normal*2.0-1.0;
    vec2 spriteTexCoord = (v_texCoord - u_spritePosInSheet) / u_spriteSizeRelToSheet; // [0..1]
    vec2 pixelPos = spriteTexCoord * u_contentSize + u_spriteOffset; // [0..origSize]
    vec3 curPixelPosInLocalSpace = (u_spriteRotated == 1) ? vec3(pixelPos.y, pixelPos.x, 0.0)                    // origin: bottom-left
    : vec3(pixelPos.x, u_contentSize.y - pixelPos.y, 0.0);

    

    vec3 Sum = vec3(0.0);
    
    for (int i=0; i<u_lightsNumber; i++) {
        

        vec3 lightVec = curPixelPosInLocalSpace - u_lightPos[i];
        vec3 posToLight = -normalize(lightVec);
        float normDotPosToLight=max(0.0,dot(normal,posToLight));
        float intercept = u_cutoffRadius[i] * u_halfRadius[i];
        float dx_1 = 0.5 / intercept;
        float dx_2 = 0.5 / (u_cutoffRadius[i] - intercept);
        float offset = 0.5 + intercept * dx_2;
        float lightDist = length(lightVec);
        float falloffTermNear = clamp((1.0 - lightDist * dx_1), 0.0, 1.0);
        float falloffTermFar  = clamp((offset - lightDist * dx_2), 0.0, 1.0);
        float falloffSelect = step(intercept, lightDist);
        float falloffTerm = (1.0 - falloffSelect) * falloffTermNear + falloffSelect * falloffTermFar;
        
        vec3 diffuse = normDotPosToLight * u_brightness[i] * falloffTerm * u_lightColor[i];
        
        Sum+=texColor.rgb * (diffuse + u_ambientColor);
    }
    
    
    gl_FragColor = vec4(Sum, texColor.a);
}