cbuffer objectBuffer : register(b0)
{
	float4x4 WVP;
	float4x4 world;
};

struct VS_IN {
	float3 pos_M		: POSITION;
	float2 texCoord		: TEXTURE;
	float3 normal		: NORMAL;
};

struct VS_OUT {
	float4 pos_S		: SV_POSITION;
	float2 texCoord		: TARGET0;
	float4 normal		: TARGET1;
	float4 pos_W		: TARGET2;
};


VS_OUT VS(VS_IN input) 
{
	VS_OUT output;


	float4x4 transfMatrix = mul(world, WVP);
	// Convert the vertices pos from Model space to World space
	float4 inpoutPosFloat4 = float4(input.pos_M, 1.0f);
	output.pos_S = mul(inpoutPosFloat4, transfMatrix);
	output.pos_W = mul(inpoutPosFloat4, world);
	//output.pos_S = float4(input.pos_M, 1.0f);
	output.texCoord = input.texCoord;

	//output.normal = float4(input.normal, 1.0f);
	output.normal = normalize(float4(mul(input.normal, (float3x3)world), 1.0f));

	return output;
}