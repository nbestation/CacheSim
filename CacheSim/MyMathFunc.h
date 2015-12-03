int log2(int a)
{
	int pow = 0;
	while (a != 1)
	{
		a = a / 2;
		pow++;
	}
	return pow;
}

int pow2(int a)
{
	int pow = 1;
	for (int i = 0; i < a; i++)
	{
		pow = pow * 2;
	}
	return pow;
}