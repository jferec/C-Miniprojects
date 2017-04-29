#include <stdio.h>
#include <stdlib.h>
void sortujLiczby(int *tab, int K)//funkcja sortujaca liczby w tabeli od najmniejszej do najwiekszej
{


	int i, j;
	int temp;
	for (i = 0; i<K*K-1; i++)
            {
                for(j=0; j<K*K-1-i; j++)
                    {
                        if (tab[j] > tab[j+1])// warunek zamiany ze soba wartosci w kolejnych komorkach tabeli
                        {
                            temp = tab[j+1];
                            tab[j+1] = tab[j];
                            tab[j] = temp;
                        }
                    }
            }
}
void filtuj(int K, int** B, int M, int N, int **C, int **A1, int R) //K rozmiar tablicy filtujacej, B tablica podstawowej, M i N rozmiary tablicy filtrowanej, C tablica wynikowa, A1 tablica , R promien tablicy filtrujacej
{
int m,n,*tab, j, i,temp;
    tab = (int*)malloc((K*K)*sizeof(int));
            for(m = R; m<M+R; m++)
                {
                    for(n = R; n<N+R; n++)


                        {

                                {
                                    B = (int**)malloc(K*sizeof(int*));

                                }

                            for(i=0;i<K;i++)
                                {
                                    B[i] = (int*)malloc(K*sizeof(int));
                                }

                            for(j=0;j<K;j++)
                                {
                                    for(i=0;i<K;i++)
                                        {
                                            B[j][i] = A1[m-R+i][n-R+j];
                                        }
                                }

                            for(i = 0; i<K; i++)
                                {

                                    for(j = 0; j<K; j++)
                                        {
                                             tab[K*i +j] = B[i][j];
                                        }


                                }

                                sortujLiczby(tab, K);

                            C[m-R][n-R] = (tab[(int)((K*K+1)/2)]);

                                for (i = 0; i<K;i++)
                                    free(B[i]);
                            free(B);
                        }
                }
    free(tab);
}
void poszerzMacierz (int **A,int **A1,int N, int M, int R)// A macierz podstawowa, A1 macierz poszerzona, N i M rozmiary macierzy A, promien macierzy filtrujacej
{

    int j, i;


        for(j=0;j<N;j++)// PETLA ZAPISUJACA SRODEK
                {
                    for(i=0;i<M;i++)
                        {
                            A1[i+R][j+R] = A[i][j];
                        }
                }
        for (i=0; i<R+1; i++)// PETLA ZAPISUJACA ROGI
            {
                for (j = 0; j<R+1; j++)//lewo gora
                    {
                        A1[i][j] = A[0][0];
                    }
                for (j = 0; j<R+1; j++)
                    {

                        A1[M+R+i-1][N+R+j-1] = A[M-1][N-1];
                    }
                for (j = 0; j<R+1; j++)//lewo dol
                    {
                        A1[M+R+i-1][j] = A [M-1][0];
                    }
                for (j = 0; j<R+1; j++)
                    {
                        A1[i][N+R+j-1] = A[0][N-1];
                    }
        }

        for (i = 0; i<R;i++)//PETLA ZAPISUJACA GORE I DOL BEZ ROGOW
        {
                    for(j = 0; j<N; j++)//zapisuje gore
                        {
                            A1[i][j+R] = A[0][j];
                        }
                    for(j = 0; j<N; j++)//zapisuje dol
                        {
                            A1[i+M+R][j+R] = A[M-1][j];
                        }
        }
        for (i = 0; i<M; i++)//PETLA ZAPISUJACA LEWO I PRAWO BEZ ROGOW
            {
                for(j = 0; j<R; j++)
                    {
                        A1[R+i][j] = A[i][0];//zapisuje lewa strone
                    }
                for(j = 0; j<R; j++)
                    {
                        A1[R+i][j+N+R] = A[i][N-1];//zapisuje prawa strone
                    }

            }
}

void drukujMacierz(int** A, int M, int N)//A macierz do wydrukowania, M i N wymiary macierzy
{
int j, i;
    for(j=0;j<M;j++)
        {
            for(i=0;i<N;i++)
                {
                    if (A[j][i] < 10)
                        printf("0");
                    printf("%i ", A[j][i]);
                }
        puts("\n");

        }
}

int main()
{

    int M,N,**A,**B,**C,i,j,zarodek,K,R,**A1;
    printf("Witaj w programie. Prosze podaj liczbe wierszy w macierzy glownej\n");
    scanf("%i", &M);
    printf("Podaj teraz liczbe kolumn\n");
    scanf("%i", &N);
    printf("Podaj rozmiar tablicy filtrujacej. Pamietaj jest ona kwadratowa i ma nieparzysta liczbe kolumn oraz wierszy\n");
    scanf("%i", &K);
    R = (K-1)/2;
    zarodek = time( NULL );
    srand(zarodek);
    A = (int**)malloc(M*sizeof(int*));

        for(i=0;i<M;i++)
            {
                A[i] = (int*)malloc(N*sizeof(int));
            }

    for(j=0;j<N;j++)
        {
            for(i=0;i<M;i++)
                {
                    if(rand()%100<=50)
                        A[i][j] = rand()%100;
                    else
                        A[i][j] = 0;

                }
        }

    A1 = (int**)malloc((M+2*R)*sizeof(int*));
        for(i=0;i<2*R+M;i++)
            {
                A1[i] = (int*)malloc((2*R+N)*sizeof(int));
            }

poszerzMacierz (A, A1,N, M, R);

    C = (int**)malloc(M*sizeof(int*));
        for(i=0;i<M;i++)
            {
                C[i] = (int*)malloc(N*sizeof(int));
            }
    for(j=0;j<N;j++)
        {
            for(i=0;i<M;i++)
                {
                    C[i][j] = 0;
                }
        }

puts("Macierz A1:\n");
    drukujMacierz(A1,M+2*R,2*R+N);

puts("Macierz A:\n");
    drukujMacierz(A, M, N);

    filtuj(K, B, M, N, C, A1, R);

puts("Macierz C:\n");
    drukujMacierz(C, M, N);


        for(i=0;i<M+2*R;i++)
            free(A1[i]);

        free(A1);

        for(i=0; i<M;i++)
            free(A[i]);

        free(A);

        for(i=0; i<M;i++)
            free(C[i]);

        free(C);

       return 0;
}
