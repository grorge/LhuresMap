struct PS_IN
{
	float4 pos_S		: SV_POSITION;
	float2 texCoord		: TARGET0;
	float4 normal		: TARGET1;
	float4 pos_W		: TARGET2;
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
cbuffer lightBuffer : register(b1)
{
	float3 lightpos; // Holds the postion of the light
	float4 lightcolor; // The color also holds the intensity
};


Texture2D diffuseMap	: register(t0);

SamplerState gSampler	: register(s0);

PS_OUT PS(PS_IN input)
{
	PS_OUT output;

							
	if (mode == 0)			// TEXTURE-MODE
	{
		output.diffuse = float4(diffuseMap.Sample(gSampler, input.texCoord).rgb, 1.0f);
	}
	else if (mode == 1)		// NORMALS-MODE
	{
		output.diffuse = (input.normal);
	}
	else if (mode == 2)		// LIGHTDIST - Renders depending on the distance to the light
	{
		// Get color
		output.diffuse = float4(diffuseMap.Sample(gSampler, input.texCoord).rgb, 1.0f);

		//------- Light calculations
		float dist = distance(float4(lightpos, 1.0f), input.pos_W);
		dist /= 50;
		output.diffuse *= (lightcolor * 1000.0f) / (pow(dist, 2));
	}
	else if (mode == 3)		// LIGHTNORMAL
	{
		// Get color
		output.diffuse = float4(diffuseMap.Sample(gSampler, input.texCoord).rgb, 1.0f);

		//------- Light calculations
		float dist = distance(float4(lightpos, 1.0f), input.pos_W);
		dist /= 100;
		output.diffuse *= (lightcolor * 1000.0f) / (pow(dist, 2));

		//------- Normals calculations 
		float4 lightdir = normalize(input.pos_W - float4(lightpos, 1.0f));
		//lightdir = !lightdir;
		float lightstrength = saturate(dot(input.normal * -1, lightdir));
		output.diffuse *= lightstrength;

	}
	else if (mode == -1)		// GUI
	{
		//The GUI only wants to send on the diffuse color
		output.diffuse = float4(diffuseMap.Sample(gSampler, input.texCoord).rgb, 0.0f);
		
	}
	else					// Default TEXTURE
	{
		output.diffuse = float4(diffuseMap.Sample(gSampler, input.texCoord).rgb, 1.0f);
	}



	saturate(output.diffuse);

	return output;
}