cbuffer objectBuffer : register(b0)
{
	float4x4 WVP;
	float4x4 world;
};

struct VS_IN {
	float3 pos_M		: POSITION;
	float2 texCoord		: TEXTURE;
};

struct VS_OUT {
	float4 pos_S		: SV_POSITION;
	float2 texCoord		: TARGET0;
};


VS_OUT VS(VS_IN input) 
{
	VS_OUT output;

	float4x4 transfMatrix = mul(world, WVP);
	// Convert the vertices pos from Model space to World space
	output.pos_S = mul(float4(input.pos_M, 1.0f), transfMatrix);
	//output.pos_S = float4(input.pos_M, 1.0f);
	output.texCoord = input.texCoord;

	return output;
}