int main(int argc, char* argv[])
{
	char* p=argv[1];
	int test_num = stoi(argv[2]);
	char b[1000];
	
	for(int i=1; i!=test_num; i++)
	{
		DBG(i);
		sprintf(b, "./gen_%s %d > %s.in", p, i, p);
		system(b);
		sprintf(b, "./%s < %s.in >%s.out", p, p, p);
		system(b);
		sprintf(b, "./brute_%s < %s.in > brute_%s.out", p, p, p);
		system(b);
		sprintf(b, "diff -b %s.out brute_%s.out", p, p);
		if (system(b))
		{
			cout << i;
			break;
		}
	}
	
	return 0;
}
