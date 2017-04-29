
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <limits.h>

typedef struct Node{
    int value;
    int min_sum;
    int sum;
    char path[20];
    char isgraph;
    struct Node *nextbottomleft;
    struct Node *nextbottomright;
    struct Node *nextbottom;

}node;

void assignGraph(node** nodeTable, int m, int n, int s){
                   int i;
for(i = 0; i<m*n;i++)
{

if (abs(((i%n)-(s))) <= (i/n) )
    {
        nodeTable[i]->isgraph = 't';
    }
else
    {
        nodeTable[i]->isgraph = 'n';
    }
}
}
void connect(node ** nodeTable, int m, int n, int i){
    if(!((i/m == (m-1))))
    nodeTable[i]->nextbottom = nodeTable[i+n];
    if(((i%n != 0)&&(i/m != (m-1))))
    nodeTable[i]->nextbottomleft = nodeTable [i+n-1];
    if(((i%n != (n-1))&&((i/m != (m-1)))))
    nodeTable[i]->nextbottomright = nodeTable [i+n+1];
}
void drukuj_Tablice(int** tab, int m, int n){
    int i,j;
    for(i = 0; i < m; i++)
{

        for(j = 0; j< n; j++)
            {
               printf("%d ", tab[i][j]);
            }
    printf("\n");
}
}
void freenodes(node ** nodeTable, int m, int n){
    int i;
for(i = 0; i<m*n; i++)
    {
        free(nodeTable[i]);
    }
    free(nodeTable);
}
void freetable(int **table, int m ){
    int i = 0, j=0;
    for(i = 0; i<m; i++)
        {
            free(table[i]);
        }
        free(table);
}
void assign(node **nodeTable, int m, int n, int** tab){
int i;
            for(i = 0; i<m*n; i++)
                {
                    nodeTable[i]->value = tab[i/n][i%n];
                }
        }

int main(){
int m,n,**tab, i,j,s,k;
char beniz;
FILE *fp;
printf("Witaj w programie podaj teraz liczbe wierszy macierzy, ktora chcesz utworzyc\n");//pobranie wymiarow od uzytkownika
scanf("%d", &m);
printf("Podaj teraz liczbe kolumn macierzy, ktora chcesz utworzyc\n");//pobranie wymiarow od uzytkownika
scanf("%d", &n);
tab = (int**)malloc(m*sizeof(int*));//uworzenie tablicy o wymiarach mxn, podanych przez uzytkownika
for (i = 0;i <m;i++)
tab[i] = (int*)malloc(n*sizeof(int));

if((fp = fopen("C:/Users/Jan/Desktop/plikdowczytu.txt", "r")) == NULL)//jesli otwarcie pliku tekstowego sie nie powiedzie
        {

                    printf("Otwieranie pliku tekstowego sie nie powiodlo, uruchom program ponownie\n");
                    exit(1);

        }

for(i = 0; i < m; i++)
        {
            for(j = 0; j < n; j++)
                {
                fscanf(fp,"%c",&beniz);
                while(beniz<48 || beniz>57)
                    fscanf(fp,"%c", &beniz);
                tab[i][j] = (int)(beniz-48);
                }
        }

printf("Wczytywanie sie powiodlo! Oto nasza macierz:\n");
drukuj_Tablice(tab, m, n);
printf("Uzytkowniku, wybierz teraz pozycje startowa grafu (liczbe od 1 do %d)\n", n );
do
{
    scanf("%d", &s);
    if (!(s>0 && s<=n))
        printf("Zla liczba, podaj jeszcze raz\n");
}while(!(s>0 && s<=n));

printf("Uzytkowniku, wybierz teraz pozycje koncowa grafu (liczbe od 1 do %d)\n", n );
do
{
    scanf("%d", &k);
    if (!(k>0 && k<=n))
        printf("Zla liczba, podaj jeszcze raz\n");
    if(abs((k-s)>(m-1)))
       printf("Wybrane 2 liczby sa za daleko od siebie!\n");
}while(!(k>0 && k<=n));
fclose(fp);
fflush(stdin);

s=s-1;
k=k-1;



node** nodeTable;

nodeTable = (node **)malloc(m*n*sizeof(int));
for (i=0; i<m*n; i++)
    {
        nodeTable[i] = (node *)malloc(sizeof(node));
    }



assign(nodeTable, m, n, tab);
/*for(i = 0; i<m*n; i++){//sprawdzenie poprawnosci funkcji assign
printf("%d ", nodeTable[i] -> value);
if(i%10 == 9)
    puts("\n");
}
*/
for(i = 0; i<m*n; i++)
{
    connect(nodeTable, m, n, i);
}

//isgraph



assignGraph(nodeTable,m,n,s);
/*puts("\n");
for(i=0;i<m*n;i++)
    printf("%c", nodeTable[i]->isgraph);
*/
nodeTable[s]->min_sum = nodeTable[s]->value;//Przypisanie pierwszemu elementowi startowemi

int l = 0;
int check = 0;
for(i = 0; i<m*n; i++)
    {if((i%n == 0)&&(i!=0)){
    l++;}
        int check = 0, s=0;
        if(nodeTable[i]->isgraph == 't')
            {
            //printf("\nWchodze do, i = %i\n", i);
            if(((i/n)!=0)){
                if((nodeTable[i-n]->nextbottom == nodeTable[i])&&(nodeTable[i-n]->isgraph=='t')){
                    (nodeTable[i]->min_sum) = (nodeTable[i-n]->min_sum + nodeTable[i]->value);
                        //printf(" bottom");
                        check = 1;
                        for(s = 0; s<l; s++)
                        nodeTable[i]->path[s] = nodeTable[i-n]->path[s];
                        nodeTable[i]->path[l] = 'b';

                    }
            }


            if(((i%n)!=(n-1))&&((i/n)!=0)){
                if(((nodeTable[i-n+1]->nextbottomleft == nodeTable[i])&&(nodeTable[i-n+1]->isgraph=='t'))&&((((nodeTable[i-n+1]->min_sum + nodeTable[i]->value) < (nodeTable[i]->min_sum)))||(check == 0))){
                    (nodeTable[i]->min_sum) = (nodeTable[i-n+1]->min_sum + nodeTable[i]->value);
                        //printf(" bottomleft");
                         check = 1;
                        for(s = 0; s<l; s++)
                        nodeTable[i]->path[s] = nodeTable[i-n+1]->path[s];
                        nodeTable[i]->path[l] = 'l';

                }
            }

            if(((i%n)!=(0)&&(i/n)!=0)){
                if(((nodeTable[i-n-1]->nextbottomright == nodeTable[i])&&(nodeTable[i-n-1]->isgraph=='t'))&&(((nodeTable[i-n-1]->min_sum + nodeTable[i]->value) < (nodeTable[i]->min_sum))||(check == 0))){
                    (nodeTable[i]->min_sum) = (nodeTable[i-n-1]->min_sum + nodeTable[i]->value);
                        //printf(" bottomright");
                             check = 1;
                        for(s = 0; s<l; s++)
                        nodeTable[i]->path[s] = nodeTable[i-n-1]->path[s];
                        nodeTable[i]->path[l] = 'r';

                }
            }
                }



            }
/*for(i=0;i<m*n;i++){
if(nodeTable[i]->isgraph == 't')
printf("%d\t",nodeTable[i]->min_sum);

}*/


//wynik programu

if(nodeTable[k+n*(m-1)]->isgraph == 'n')
    puts("Przy obecnych zalozeniach, taka droga nie istnieje");
else printf("\n\nNajktorsza droga miedzy punktami wynosi %d", nodeTable[k+n*(m-1)]->min_sum);
puts("\nOto droga:\n");
 for(i=1;i<m;i++)
 printf("%c\t", nodeTable[k+n*(m-1)]->path[i]);



FILE *result;
result = fopen("C:/Users/Jan/Desktop/plikzwynikiem.txt", "w");
fprintf(result,"Najktorsza droga miedzy punktami wynosi %d,  droga do celu to %s", nodeTable[k+n*(m-1)]->min_sum, nodeTable[k+n*(m-1)]->path); //wpisaæ swoj¹ œcie¿kê
fclose(result);
//strefa zwalniania pamieci
freenodes(nodeTable, m, n);
freetable(tab, m);


return 0;
}

