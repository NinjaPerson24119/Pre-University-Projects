//Even or odd function for integers
enum EVEN_ODD { EVEN, ODD };
EVEN_ODD even_odd(int check)
{
	if(check/2*2 == check) return EVEN; else return ODD;
}