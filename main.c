#include <stdio.h>
#include <stdlib.h>

int writeToBin(FILE *filePointer,int x1,int x2,int N,int delta)
{
    int i,y,n = 0;
    for(i = 0; i<=N; i++)
    {
        n++;
        y=x1*3;
        fwrite(&x1,sizeof(int),1,filePointer);// Nie formalny wkład
        fwrite(&y,sizeof(int),1,filePointer);// Nie formalny wkład
        if(x1==x2)
        break;
        x1+=delta;
    }
   fclose(filePointer);
   return n;
}

void readFromBin(FILE *filePointer,unsigned int n,int x1,int x2)
{
    int f,x,y;
    printf("               BIN FILE (result.bin)  \n");
    printf("*************************************************\n");
    printf("*       N       *       X       *      F(X)     *\t\n");
    printf("*************************************************\n");
    for(f = 1; f < n+1;f++)
    {
        fread(&x,sizeof(int),1,filePointer);//Czytanie
        fread(&y,sizeof(int),1,filePointer);//Czytanie
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",f,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
    printf("\n");
    fclose(filePointer);
}

int writeToTxt(FILE *filePointer,int x1,int x2,int N,int delta)
{
    int i,x3,n = 0;
    for(i = 0; i<=N; i++)
    {
        n++;
        x3=x1*3;;
        fprintf(filePointer,"%d %d\n",x1,x3);//Czytanie
        if(x1>=x2)
        {
            return n;
        }
        x1+=delta;
    }
    fclose(filePointer);
    return n;
}

void readFromTxt(FILE *filePointer,unsigned int n,int x1,int x2)
{
    int i,x,y;
    printf("                TXT FILE (result.txt)  \n");
    printf("     Start: %d    Finish: %d   Count of steps: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("*       N       *       X       *      F(X)     *\t\n");
    printf("*************************************************\n");
    for(i = 1; i < n+1;i++)
    {
        fscanf(filePointer,"%d",&x);// Nie formalny wkład
        fscanf(filePointer,"%d",&y);// Nie formalny wkład
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");

    }
    printf("\n");
    fclose(filePointer);
}

void saveResultToArray(FILE *filePointer,int n)
{
   int i,j,k;
   int **arr = (int **)malloc(n*sizeof(int*));
   for( i = 0; i < n; i++)
   {
      arr[i] = (int *)malloc(2*sizeof(int));
   }
   printf("---------------\n");
   printf("Array content :\n");
   for(i = 0;i<n;i++)
   {
       for(j = 0;j<2;j++)
       {
           fscanf(filePointer,"%d",&k);
           arr[i][j] = k;
       }
   }
   for(i = 0;i<n;i++)
   {
       for(j = 0;j<1;j++)
       {
            printf("x: %d | y: %d \n",arr[i][j],arr[i][j+1]);
       }
   }
   for(i = 0; i < n; i++)
    {
        free(arr[i]);
    }
     printf("---------------");
    free(arr);
}

int main()
{
    //moja funkcja F(x)=x1*3;
    //Rozmiar Bin pliku  88 byte
    //Txt pliku rozmiar 69 byte
    unsigned int N,delta,n;
    int x1,x2;
    char group[50];
    FILE *file_Input;//стандартнa структурa FILE
    FILE *file_ReadTxt, *file_WriteTxt;
    FILE *file_ReadBin, *file_WriteBin;
//--------------------------------------------------------------------------------------------------------------------------------------------
    file_Input = fopen("input.dat","r");
    fscanf(file_Input,"%s%d%d%u%u",&group,&x1,&x2,&N,&delta);
    fclose(file_Input);
//--------------------------------------------------------------------------------------------------------------------------------------------
    if(N==0){N = delta;}
    printf("   Group = %s  |\n",group);
    printf("x1 = %d ",x1);
    printf("   x2 = %d |\n",x2);
    printf("N = %u ",N);
    printf("   Step = %u |\n",delta);
    printf("-------------------\n\n");
//--------------------------------------------------------------------------------------------------------------------------------------------
    file_WriteTxt = fopen("result.txt","w");
    n = writeToTxt(file_WriteTxt,x1,x2,N,delta);
    fclose(file_WriteTxt);
//--------------------------------------------------------------------------------------------------------------------------------------------
    file_ReadTxt  = fopen("result.txt","r");
    readFromTxt(file_ReadTxt,n,x1,x2);
    fclose(file_ReadTxt);
//--------------------------------------------------------------------------------------------------------------------------------------------
    file_WriteBin = fopen("result.bin","wb");
    n = writeToBin(file_WriteBin,x1,x2,N,delta);
    fclose(file_WriteBin);
//--------------------------------------------------------------------------------------------------------------------------------------------
    file_ReadBin  = fopen("result.bin","rb");
    readFromBin(file_ReadBin,n,x1,x2);
    fclose(file_ReadBin);
//--------------------------------------------------------------------------------------------------------------------------------------------
    file_ReadTxt  = fopen("result.txt","r");
    saveResultToArray(file_ReadTxt,n);
    fclose(file_ReadTxt);
    return 0;
}
