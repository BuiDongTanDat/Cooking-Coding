#include <stdio.h>
#include <string.h>
#include <math.h>
#define size 100
#define pi 3.1415926535

float ccake(int);
float gcake(int);
int amicable(int, int);
void Windcase(int, int, int, int, int *, int *, float *);
void Raincase(int, int, int, int, int *, int *, float *);
void Suncase(int, int, int, int, int *, int *, float *);
void Cloudcase(int, int, int, int, int *, int *, float *);
void Fogcase(int, int, int, int, int *, int *, float *);
int main()
{
    int n, dc, dg, ld, bc, bg;
    float nd;
    char w[size];

    FILE *fi;
    fi = fopen("input.inp", "r");
    fscanf(fi, "%d%d%d%d%s", &n, &dc, &dg, &ld, w);

    if (n < 0 || n > 1000 || ld > 300 || ld < 1)
    {
        fi = fopen("output.out", "w");
        fprintf(fi, "-1 -1 %d", n);
        return 0;
    }

    if (dc < 0)
        dc = 1000;
    if (dg < 0)
        dg = 1000;

    if (strcmp(w, "Wind") == 0)
    {
        Windcase(n, dc, dg, ld, &bc, &bg, &nd);
    }
    else if (strcmp(w, "Rain") == 0)
    {
        Raincase(n, dc, dg, ld, &bc, &bg, &nd);
    }
    else if (strcmp(w, "Sun") == 0)
    {
        Suncase(n, dc, dg, ld, &bc, &bg, &nd);
    }
    else if (strcmp(w, "Cloud") == 0)
    {
        Cloudcase(n, dc, dg, ld, &bc, &bg, &nd);
    }
    else
    {
        Fogcase(n, dc, dg, ld, &bc, &bg, &nd);
    }

    fi = fopen("output.out", "w");
    fprintf(fi, "%d %d %.3f", bc, bg, nd);
    fclose(fi);
    return 0;
}

float ccake(int dc)
{
    float num;
    num = (dc * dc);
    return num;
}

float gcake(int dg)
{
    float num;
    num = ((dg * dg * pi) / 4);
    return num;
}

int amicable(int a, int b)
{
    int suma = 0, sumb = 0, i;
    for (i = 1; i < a; i++)
    {
        if (a % i == 0)
        {
            suma += i;
        }
    }
    for (i = 1; i < b; i++)
    {
        if (b % i == 0)
        {
            sumb += i;
        }
    }
    if (a == sumb && b == suma)
    {
        return 1;
    }
    else
        return 0;
}

void Windcase(int n, int dc, int dg, int ld, int *bc, int *bg, float *nd)
{
    int d;
    *bc = n / ccake(dc);
    *bg = (n - *bc * ccake(dc)) / gcake(dg);
    d = *bc + *bg;
    if (d <= ld)
    {
        *nd = n - *bc * ccake(dc) - *bg * gcake(dg);
    }
    else
    {
        int i, j;
        float min, temp;
        min = n;
        for (i = 0; i <= ld; i++)
            for (j = 0; j <= ld - i; j++)
            {
                temp = n - i * ccake(dc) - j * gcake(dg);
                if (temp >= 0 && min > temp)
                {
                    min = temp;
                    *bc = i;
                    *bg = j;
                }
            }
        *nd = min;
    }
}

void Raincase(int n, int dc, int dg, int ld, int *bc, int *bg, float *nd)
{
    int x, d, bct, bgt, i = 0, j = 0;
    float ndt = 0, temp;
    x = n / (ccake(dc) + gcake(dg));
    d = 2 * x;
    while (d > ld)
    {
        x--;
        d = d - 2;
    }
    *bc = x;
    *bg = x;
    ndt = n - *bc * (ccake(dc)) - *bg * (gcake(dg));
    temp = ndt;
    for (bct = 0; bct <= (ld - d); bct++)
        for (bgt = 0; bgt <= (ld - d - bct); bgt++)
        {
            if (ndt - (bct * ccake(dc) + bgt * gcake(dg)) <= temp && ndt - (bct * ccake(dc) + bgt * gcake(dg)) >= 0)
            {
                temp = ndt - (bct * ccake(dc) + bgt * gcake(dg));
                i = bct;
                j = bgt;
            }
        }

    *bc = *bc + i;
    *bg = *bg + j;
    *nd = n - *bc * (ccake(dc)) - *bg * (gcake(dg));
}

void Suncase(int n, int dc, int dg, int ld, int *bc, int *bg, float *nd)
{
    int G = 0, H = 0, X = 0;

    G = dc % 6;
    H = ld % 5;

    switch (H - G)
    {
    case -5:
    case 1:
        X = 20;
        break;
    case -4:
    case 2:
        X = 15;
        break;
    case -3:
    case 3:
        X = 12;
        break;
    case -2:
    case 4:
        X = 10;
        break;
    case -1:
        X = 7;
        break;
    case 0:
        X = 5;
        break;
    }
    n += n * (X * 0.01);
    ld -= X;
    if (ld < 0)
        ld = 0;

    switch ((dg + dc) % 3)
    {
    case 0:
        Raincase(n, dc, dg, ld, bc, bg, nd);
        break;
    case 1:
        Windcase(n, dc, dg, ld, bc, bg, nd);
        break;
    case 2:
        Cloudcase(n, dc, dg, ld, bc, bg, nd);
        break;
    }
}

void Fogcase(int n, int dc, int dg, int ld, int *bc, int *bg, float *nd)
{
    *bc = dc;
    *bg = dg;
    *nd = n;
}

void Cloudcase(int n, int dc, int dg, int ld, int *bc, int *bg, float *nd)
{
    if (amicable(n, ld) == 1)
    {
        FILE *fi;
        *nd = n;
        *bc = 0;
        *bg = 0;
    }
    else
    {
        int d;
        *bg = n / gcake(dg);
        *bc = (n - *bg * gcake(dg)) / ccake(dc);
        d = *bc + *bg;
        if (d <= ld)
        {
            *nd = n - *bc * ccake(dc) - *bg * gcake(dg);
        }
        else
        {
            int i, j;
            float min, temp;
            min = n;
            for (i = 0; i <= ld; i++)
                for (j = 0; j <= ld - i; j++)
                {
                    temp = n - i * ccake(dc) - j * gcake(dg);
                    if (temp >= 0 && min > temp)
                    {
                        min = temp;
                        *bc = i;
                        *bg = j;
                    }
                }
            *nd = min;
        }
    }
}