namespace FFT {
	const int MAX = 1 << 19;

	typedef ll value;
	typedef complex<double> comp;

	int N;
	comp omega[MAX];
	comp a1[MAX], a2[MAX];
	comp z1[MAX], z2[MAX];

	void fft(comp *a, comp *z, int m = N) {
		if (m == 1) {
			z[0] = a[0];
		} else {
			int s = N/m;
			m /= 2;

			fft(a, z, m);
			fft(a+s, z+m, m);

			rep(i, 0, m) {
				comp c = omega[s*i] * z[m+i];
				z[m+i] = z[i] - c;
				z[i] += c;
			}
		}
	}

	void mult(value *a, value *b, value *c, int len) {
		N = 2*len;
		while (N & (N-1)) ++N;
		assert(N <= MAX);

		rep(i, 0, N) a1[i] = 0;
		rep(i, 0, N) a2[i] = 0;
		rep(i, 0, len) a1[i] = a[i];
		rep(i, 0, len) a2[i] = b[i];

		rep(i, 0, N) omega[i] = polar(1.0, 2*M_PI/N*i);
		fft(a1, z1, N);
		fft(a2, z2, N);

		rep(i, 0, N) omega[i] = comp(1, 0) / omega[i];
		rep(i, 0, N) a1[i] = z1[i] * z2[i] / comp(N, 0);
		fft(a1, z1, N);

		rep(i, 0, 2*len) c[i] = round(z1[i].real());
	}


}

#define MAX (1<<19)
//dziala jakos wolno?
void mult_mod(ll *a, ll *b, ll *c, int len, int mod) {
	static ll a0[MAX], a1[MAX];
	static ll b0[MAX], b1[MAX];
	static ll c0[MAX], c1[MAX], c2[MAX];

	rep(i, 0, len) a0[i] = a[i] & 0xFFFF;
	rep(i, 0, len) a1[i] = a[i] >> 16;

	rep(i, 0, len) b0[i] = b[i] & 0xFFFF;
	rep(i, 0, len) b1[i] = b[i] >> 16;

	FFT::mult(a0, b0, c0, len);
	FFT::mult(a1, b1, c2, len);

	rep(i, 0, len) a0[i] += a1[i];
	rep(i, 0, len) b0[i] += b1[i];
	FFT::mult(a0, b0, c1, len);
	rep(i, 0, 2*len) c1[i] -= c0[i] + c2[i];

	rep(i, 0, 2*len) c1[i] %= mod;
	rep(i, 0, 2*len) c2[i] %= mod;
	rep(i, 0, 2*len) c[i] = (c0[i] + (c1[i] << 16) + (c2[i] << 32)) % mod;
}

//or convolution:
void tra(int *from, int *to, bool rev) 
{ 
    if(to - from == 1) 
        return; 
    int *mid = from + (to - from) / 2; 
    tra(from, mid, rev); 
    tra(mid, to, rev); 
    for(int i = 0; i < mid - from; i++) 
    {
		int mnoz = 1;
		if (rev) mnoz = -1;
        *(mid + i) += mnoz * (*(from + i)); 
	}
}
