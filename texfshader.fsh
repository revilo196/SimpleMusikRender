#version 330
in vec2 UV;
out vec4 daColor;

//layout(location = 1) out vec3 color;

//uniform sampler2D tex;
//uniform bool dos;

const float blurSizeH = 1.0 / 70.0;
const float blurSizeV = 1.0 / 70.0;

uniform sampler2D texFramebuffer;

void main()
{
    vec4 sum = vec4(0.0);

    vec4 sum2 = vec4(0.0);

    vec4 sum3 = vec4(0.0);
    for (int x = -6; x <= 6; x++)
        for (int y = -6; y <= 6; y++)
        {
            sum += texture2D(
                texFramebuffer,
                vec2(UV.x + x * blurSizeH, UV.y + y * blurSizeV)

            ) / (12.0*12.0);

            sum2 += texture2D(
                        texFramebuffer,
                        vec2(UV.x + x * blurSizeH/3.0, UV.y + y * blurSizeV/3.0)) / (12.0*12.0);

            sum3 += texture2D(
                        texFramebuffer,
                        vec2(UV.x + x * blurSizeH*4.0, UV.y + y * blurSizeV*4.0)) / (12.0*12.0);
        }

   daColor = sum + sum2 + (sum3);


   //daColor = texture2D(texFramebuffer, UV);
}
