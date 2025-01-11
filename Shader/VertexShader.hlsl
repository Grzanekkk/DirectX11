struct VSOut
{
    float3 color : Color;
    float4 pos : Sv_Position;
};

cbuffer ConstBuffer
{
    row_major matrix transform;
}

VSOut main(float3 pos : Position, float3 color : Color) 
{
    VSOut vsout;
    vsout.pos = mul( float4(pos.x, pos.y, pos.z, 1.0f), transform );
    vsout.color = color;
    return vsout;
}