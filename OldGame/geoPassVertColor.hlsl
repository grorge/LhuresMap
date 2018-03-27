struct VS_IN {
	float3 pos_M	: POSITION;
	float4 color	: COLOR;
};

struct VS_OUT {
	float4 pos_S	: SV_POSITION;
	float4 color	: TARGET0;
};


VS_OUT VS(VS_IN input) 
{
	VS_OUT output;

	// Convert the vertices pos from Model space to World space
	output.pos_S = float4(input.pos_M, 1.0f);
	output.color = input.color;

	return output;
}