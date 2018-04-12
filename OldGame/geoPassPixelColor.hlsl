struct PS_IN
{
	float4 pos_S		: SV_POSITION;
	float2 texCoord		: TARGET0;
	float4 normal		: TARGET1;
};

struct PS_OUT
{
	float4 diffuse		: SV_TARGET;
};

cbuffer rndModeBuffer : register(b0)
{
	int mode;
	int fill0;
	int fill1;
	int fill2;
};

Texture2D diffuseMap	: register(t0);

SamplerState gSampler	: register(s0);

PS_OUT PS(PS_IN input)
{
	PS_OUT output;

	// TEXTURE-MODE
	if (mode == 0)
	{
		output.diffuse = float4(diffuseMap.Sample(gSampler, input.texCoord).rgb, 1.0f);
	}
	else
	{
		output.diffuse = (input.normal+0.1f);
	}

	// NORMALS-MODE

	// RENDERWHITE-MODE
	//output.diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);


	return output;
}