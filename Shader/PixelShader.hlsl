cbuffer CBuf
{
    float4 FaceColor[6];
}

float4 main( uint TriangleID : SV_PrimitiveID ) : Sv_Target
{
    return FaceColor[ TriangleID / 2 ];
}