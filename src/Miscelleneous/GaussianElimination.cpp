#define MAX_N 300       // adjust this value as needed
struct AugmentedMatrix { double mat[MAX_N][MAX_N + MAX_N + 10]; };
struct ColumnVector { double vec[MAX_N]; };

// 0 indexed row and column
AugmentedMatrix GaussianElimination(int N, AugmentedMatrix Aug) {
	// input: N X 2N matrix  [A I], output: [I invA]

	// forward eliminataion phase
	for(int i=0;i<N;i++){
		int l = i;
		// which row has largest column value
		for(int j=i+1;j<N;j++)
			if( fabs(Aug.mat[j][i]) > fabs(Aug.mat[l][i]) )
				l = j;
		// swap this pivot row to minimize error
		for(int k=i;k<2*N;k++)
			swap(Aug.mat[i][k],Aug.mat[l][k]);
		// calculate forward elimination
		for(int j=i+1;j<N;j++)
			for(int k=2*N-1;k>=i;k--)
				Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];
	}

	// normalize pivots
	for(int i=0;i<N;i++)
		for(int j=2*N-1;j>=i;j--)
			Aug.mat[i][j] /= Aug.mat[i][i];

	// backward elimination
	for(int i=N-1;i>0;i--)
		for(int j=i-1;j>=0;j--)
			for(int k=2*N-1;k>=i;k--)
				Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];


	return Aug;
}

int main() {

	AugmentedMatrix Aug;
	int N; geti(N);
	rep(i,N) rep(j,N) scanf("%lf",&Aug.mat[i][j]);
	for(int i=N;i<2*N;i++) Aug.mat[i-N][i] = 1;
	
	AugmentedMatrix res = GaussianElimination(N, Aug);
	
	// Print inversion of A
	for(int i=0;i<N;i++){
		for(int j=N;j<2*N;j++) printf("%f ",res.mat[i][j]);
		printf("\n");
	}
	

	return 0;
}