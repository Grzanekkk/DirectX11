struct VSOut
{
    float3 color : Color;
    float4 pos : Sv_Position;
};

VSOut main(float3 pos : Position, float3 color : Color) 
{
    VSOut vsout;
    vsout.pos = float4(pos.x, pos.y, pos.z, 1.0f);
    vsout.color = color;
    return vsout;
}