#include<stdio.h>

void gauss(int n, int row, int col, float A[row][col]); // para fazer Gauss
void gaussJordan(int n, int row, int col, float A[row][col]); // para fazer Gauss Jordan
void printMatrix(int n, int row, int col, float A[row][col]); // para imprimir uma matriz
void printDist (int n, float x[n+1]); // para imprimir o vetor de deslocamentos
void printAmp(int n, float x[n+1], int a); // para imprimir as amplitudes
float det(int n, int row, int col, float A[row][col]); // para calcular o determinante de matrizes após Gauss e Gauss Jordan
void calcDesloc(int n, float A[n][n+1], float v[n+1], float des[n+1], char x); // calcular os deslocamentos (regra de Cramer)


void gauss(int n, int row, int col, float A[row][col]){
    int i, j, k;
    float c;
    for(j=1; j<=n; j++)
    /*Recebendo a matriz desejada como parâmetro, nesses loops ela será alterada para uma matriz triangular superior*/
    {
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
                c=A[i][j]/A[j][j];
                for(k=1; k<=col; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }

}


void gaussJordan(int n, int row, int col, float A[row][col]){
    float c;
    int j, k, i;
    for(j=1; j<=n; j++)
    /*Recebendo a matriz desejada como parâmetro, nesses loops ela será alterada para uma matriz diagonal*/
    {
    for(i=1; i<=n; i++)
    {
        if(i!=j)
        {
            c=A[i][j]/A[j][j];
            for(k=1; k<=col; k++)
            {
                A[i][k]=A[i][k]-c*A[j][k];
            }
        }
    }
    }
}

void printMatrix(int n, int row, int col, float A[row][col]){
    int i, j;
    j=n+1;
    i=n;
    printf("\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=(n+1); j++)
        {
            if(i==1 && j==n+1){
                printf("\t%.1f⎤", A[i][j]);
            }
            else if(i==1 && j==1){
                printf("\t⎡%.1f", A[i][j]);
            }
            else if(i==n && j==1){
                printf("\t⎣%.1f", A[i][j]);
            }
            else if(i==n && j==n+1){
                printf("\t%.1f⎦", A[i][j]);
            }
            else if(j==n){
                printf("\t%.1f|", A[i][j]);
            }
           else {
                printf("\t%.1f", A[i][j]);
           }  
        }
        printf("\n");
    }
}

void calcDesloc(int n, float A[n][n+1], float v[n+1], float des[n+1], char x){
    /*Regra de Cramer*/
    /*Recebo a matriz (já após Gauss ou Gauss Jordan), o vetor v de termos independentes da mesma matriz
    o vetor de deslocamentos que está vazio e vou o preencher dentro desta função, e um outro parâmetro adicional x
    que vai ser só para eu controlar se uso Gauss ou Gauss Jordan mais abaixo*/

    /*Matriz Ci é a matriz C, para cada d na posição i, com a coluna i trocada pelo vetor dos termos independentes*/
    float Ci[n][n];
    int g, i, j;

    /*Nos loops abaixo, gero a matriz Ci para cada deslocamento, e armazeno o detCi/detC em cada posição g do meu vetor
    de deslocamentos*/
    for (g=1; g<=n; g++){
        for(i=1; i<=n; i++)
        {
            for(j=1; j<=n; j++)
            {
            if (g==j){
                    Ci[i][j] = v[i];
            }
            else{
                Ci[i][j] = A[i][j];
            }
        }
        }
        /*No if e else abaixo: após gerar uma matriz Ci, não vai ser mais triangular superior/inferior, pois troquei uma das colunas
        pelo vetor de termos independentes. Portanto, faço gauss (ou gauss jordan) nela para que possa calcular o determinante
        apenas multiplicando os elementos da diagonal principal.*/
        if (x=='g'){
            gauss(n, n, n, Ci);
        }
        else{
            gaussJordan(n, n, n, Ci);
        }
        des[g] = (det(n, n, n, Ci)/det(n, n, n+1, A));
    }

}

float det(int n, int row, int col, float A[row][col]){
    /*Função para calcular o determinante: multiplico os elementos da diagonal principal*/
    float det = 1.0;
    int i;
    for (i=1; i<=n; i++){
        det *= A[i][i];
    }
    return det;
}



void printDist(int n, float x[n+1]){
    /*Função que recebe o vetor de deslocamentos e printa de um jeito padrãozinho*/
    int i;
    for(i=1; i<=n; i++)
    {
        printf("\n⊳ ⊳ ⊳ x%d = %f\n",i,x[i]);
    }
}


void printAmp(int n, float x[n+1], int a){
    /*Função que recebe o vetor de deslocamentos e o parâmetro a, e printa as amplitudes (a*d)*/
    int i;
    for(i=1; i<=n; i++)
    {
        printf("\n⊳ ⊳ ⊳ a * d%d = %f\n",i,a * x[i]);
    }
	printf("\n");
}

int main()
{

int aux = 1;
while(aux == 1){
    printf("Digite 1 para executar ou outro valor para encerrar:");
    scanf("%d",&aux);
    if(aux == 1){
		printf(" _______        _           _ _             __  __ _   _ __\n"); 
		printf("|__   __|      | |         | | |           |  \\/  | \\ | /_ |\n");
		printf("   | |_ __ __ _| |__   __ _| | |__   ___   | \\  / |  \\| || |\n");
		printf("   | | '__/ _` | '_ \\ / _` | | '_ \\ / _ \\  | |\\/| | . ` || |\n");
		printf("   | | | | (_| | |_) | (_| | | | | | (_) | | |  | | |\\  || |\n");
		printf("   |_|_|  \\__,_|_.__/ \\__,_|_|_| |_|\\___/  |_|  |_|_| \\_||_|\n");

		int i,j,n;
		float a;

		int flag;
        	printf("\n Deseja calibrar o sistema? \n 1-SIM \n Outro valor-NÃO \n");
        	scanf("%d",&flag);
        	if(flag == 1){
            		float a1;
			n =3;


			float Agc[n][n+1];
			float Agjc[n][n+1];

			float dc[n+1];
			float d1c[n+1];

			float desc[n+1];
			float des1c[n+1];

			a1 = 1;

			/*Preenchendo as matrizes*/
		for(i=1; i<=n; i++)
		{
		    for(j=1; j<=(n+1); j++)
		    {
			if (j==n+1){						
						Agc[i][4] = 12;
						Agjc[i][4] = 12;
					}
			if (i==j){
				Agc[i][j] = 10;
				Agjc[i][j] = 10;
			}
			if(j != n+1 && i!=j){
				Agc[i][j] = 1;
				Agjc[i][j] = 1;			
			}
		    }
		}
			
			
			 printf("\n+-----------------------------------------------------------+\n");
			    printf("|         _____         _    _  _____ _____                 |\n");
			    printf("|        / ____|   /\\  | |  | |/ ____/ ____|                |\n");
			    printf("|       | |  __   /  \\ | |  | | (___ | (___                 |\n");
			    printf("|       | | |_ | / /\\ \\| |  | |\\___ \\ \\___ \\                |\n");
			    printf("|       | |__| |/ ____ \\ |__| |____) |___) |                |\n");
			    printf("|        \\_____/_/    \\_\\_____|______/_____/                |\n|\t\t\t\t\t\t\t    |\n|\t\t\t\t\t\t\t    |");

			printf("\n+---------------------Matriz resolvida:---------------------+\n");
		gauss(n, n, n+1, Agc);
		printMatrix(n, n, n+1, Agc);

		printf("\n---------------------Os deslocamentos sao:-------------------\n");
		/*preencho o vetor d com os termos independentes da matriz de Gauss*/
		for (int i=1; i<=n; i++){
		    dc[i] = Agc[i][n+1];
		}

		/*faço a regra de cramer e armazeno no vetor des os deslocamentos*/
		calcDesloc(n, Agc, dc, desc, 'g');
		printDist(n, desc);

		printf("\n---------------------As amplitudes sao:----------------------\n");
		printAmp(n, desc, a1);

		printf("+-----------------------------------------------------------+\n");
		

		 printf("|         _____         _    _  _____ _____                 |\n");
			    printf("|        / ____|   /\\  | |  | |/ ____/ ____|                |\n");
			    printf("|       | |  __   /  \\ | |  | | (___ | (___    ____         |\n");
			    printf("|       | | |_ | / /\\ \\| |  | |\\___ \\ \\___ \\  |____|        |\n");
			    printf("|       | |__| |/ ____ \\ |__| |____) |___) |                |\n");
			    printf("|        \\_____/_/    \\_\\_____|______/_____/                |\n");
			    printf("|             _  ____  _____  _____          _   _          |\n");
			    printf("|            | |/ __ \\|  __ \\|  __ \\   /\\   | \\ | |         |\n");
			    printf("|            | | |  | | |__) | |  | | /  \\  |  \\| |         |\n");
			    printf("|        _   | | |  | |  _  /| |  | |/ /\\ \\ | . ` |         |\n");
			    printf("|       | |__| | |__| | | \\ \\| |__| / ____ \\| |\\  |         |\n");
			    printf("|        \\____/ \\____/|_|  \\_\\_____/_/    \\_\\_| \\_|         |\n|\t\t\t\t\t\t\t    |");

		printf("\n+---------------------Matriz resolvida:---------------------+\n");
		gaussJordan(n, n, n+1, Agjc);
		printMatrix(n, n, n+1, Agjc);

		printf("\n---------------------Os deslocamentos sao:-------------------\n");
		/*preencho o vetor d1 com os termos independentes da matriz de Gauss Jordan*/
		for (int i=1; i<=n; i++){
		    d1c[i] = Agjc[i][n+1];
		}
		/*faço a regra de cramer e armazeno no vetor des1 os deslocamentos*/
		calcDesloc(n, Agjc, d1c, des1c, 'j');
		printDist(n, des1c);

		printf("\n---------------------As amplitudes sao:----------------------\n");
		printAmp(n, des1c, a1);

		printf("+-----------------------------------------------------------+\n");


}
		printf("\n+--------------Entre com o numero de Pêndulos:--------------+\n>>> ");
		scanf("%d",&n);


		/*Nos parâmetros abaixo: um deles é a matriz de coeficientes, os outros são cópias que fiz da mesma
		para passá-lás como parâmetros quando for utilizar Gauss e Gauss Jordan e poder ir alterando-as no processo*/
		float A[n][n+1];
		float Ag[n][n+1];
		float Agj[n][n+1];


		/*d vai armazenar o vetor de termos independentes da matriz de Gauss e d1 de Gauss Jordan*/
		float d[n+1];
		float d1[n+1];

		/*des vai armazenar os deslocamentos da matriz de Gauss e des1 da matriz de Gauss Jordan*/
		float des[n+1];
		float des1[n+1];

		printf("--------------------Entre o parâmetro a:---------------------\n>>> ");
		scanf("%f", &a);
		printf("-----------Entre os elementos da matriz por linha:-----------\n");


		/*Preenchendo as matrizes*/
		for(i=1; i<=n; i++)
		{
		    for(j=1; j<=(n+1); j++)
		    {
			if (j==n+1){
						printf("\t\t\t→ V[%d]: ",i);
						scanf("%f", &A[i][j]);
						Ag[i][j] = A[i][j];
						Agj[i][j] = A[i][j];
					}
			else{
			printf(">>>\t\t\t→ A[%d][%d]:", i,j);
			scanf("%f",&A[i][j]);
			Ag[i][j] = A[i][j];
			Agj[i][j] = A[i][j];
			}
		    }
		}
			    printf("\n+-----------------------------------------------------------+\n");
			    printf("|         _____         _    _  _____ _____                 |\n");
			    printf("|        / ____|   /\\  | |  | |/ ____/ ____|                |\n");
			    printf("|       | |  __   /  \\ | |  | | (___ | (___                 |\n");
			    printf("|       | | |_ | / /\\ \\| |  | |\\___ \\ \\___ \\                |\n");
			    printf("|       | |__| |/ ____ \\ |__| |____) |___) |                |\n");
			    printf("|        \\_____/_/    \\_\\_____|______/_____/                |\n|\t\t\t\t\t\t\t    |\n|\t\t\t\t\t\t\t    |");

		printf("\n+---------------------Matriz resolvida:---------------------+\n");
		gauss(n, n, n+1, Ag);
		printMatrix(n, n, n+1, Ag);

		printf("\n---------------------Os deslocamentos sao:-------------------\n");
		/*preencho o vetor d com os termos independentes da matriz de Gauss*/
		for (int i=1; i<=n; i++){
		    d[i] = Ag[i][n+1];
		}

		/*faço a regra de cramer e armazeno no vetor des os deslocamentos*/
		calcDesloc(n, Ag, d, des, 'g');
		printDist(n, des);

		printf("\n---------------------As amplitudes sao:----------------------\n");
		printAmp(n, des, a);

		printf("+-----------------------------------------------------------+\n");
			    printf("|         _____         _    _  _____ _____                 |\n");
			    printf("|        / ____|   /\\  | |  | |/ ____/ ____|                |\n");
			    printf("|       | |  __   /  \\ | |  | | (___ | (___    ____         |\n");
			    printf("|       | | |_ | / /\\ \\| |  | |\\___ \\ \\___ \\  |____|        |\n");
			    printf("|       | |__| |/ ____ \\ |__| |____) |___) |                |\n");
			    printf("|        \\_____/_/    \\_\\_____|______/_____/                |\n");
			    printf("|             _  ____  _____  _____          _   _          |\n");
			    printf("|            | |/ __ \\|  __ \\|  __ \\   /\\   | \\ | |         |\n");
			    printf("|            | | |  | | |__) | |  | | /  \\  |  \\| |         |\n");
			    printf("|        _   | | |  | |  _  /| |  | |/ /\\ \\ | . ` |         |\n");
			    printf("|       | |__| | |__| | | \\ \\| |__| / ____ \\| |\\  |         |\n");
			    printf("|        \\____/ \\____/|_|  \\_\\_____/_/    \\_\\_| \\_|         |\n|\t\t\t\t\t\t\t    |");

		printf("\n+---------------------Matriz resolvida:---------------------+\n");
		gaussJordan(n, n, n+1, Agj);
		printMatrix(n, n, n+1, Agj);

		printf("\n---------------------Os deslocamentos sao:-------------------\n");
		/*preencho o vetor d1 com os termos independentes da matriz de Gauss Jordan*/
		for (int i=1; i<=n; i++){
		    d1[i] = Agj[i][n+1];
		}
		/*faço a regra de cramer e armazeno no vetor des1 os deslocamentos*/
		calcDesloc(n, Agj, d1, des1, 'j');
		printDist(n, des1);

		printf("\n---------------------As amplitudes sao:----------------------\n");
		printAmp(n, des1, a);

		printf("+-----------------------------------------------------------+\n");
}}
	return(0);
}


