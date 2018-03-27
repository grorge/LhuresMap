struct PS_IN
{
	float4 pos_S		: SV_POSITION;
	float4 color		: COLOR2;
};

struct PS_OUT
{
	float4 diffuse		: SV_TARGET;
};

PS_OUT PS(PS_IN input)
{
	PS_OUT output;

	output.diffuse = input.color;
	//output.diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return output;
}