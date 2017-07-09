template <size_t rozmiar>
struct Moj_bitset : public bitset < rozmiar >
{
	ll* T;
	int roz;
	Moj_bitset()
	{
		T = (ll*)this;
		roz = rozmiar/64 + (rozmiar%64);
	}
};
