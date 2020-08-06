/*
Assigned by
Name :Shlomi Amir
ID   :311403844
and
Name :Eyal Gorfinkel
ID   :312544497
Group:61309a
Dr Ahuva Mualem
Mr Tamir Gonen
*/
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
typedef struct interval {
	int left;
	int right;
	unsigned int color;
	struct interval ** neighbors;
	int neighborsCount;
}interval;
//declaration
void greedycoloring();
void swap(interval* , interval* );
void quickSort(interval *, int , int );
int partition(interval *, int , int );
int chromaticNumber(interval * , int );

void main()
{
	//function call
	greedycoloring();
	system("pause");
}
void greedycoloring()
{
	int k, i, j, t,p;
	int eCount = 0, max = 0, min,GCedge,GCmin,GCmax, chromaticNum;
	interval ** colorSorting;
	printf("enter k (numbers of intervals)\n");
	scanf_s("%d", &k);
	assert(k > 0);
	interval *arr = (interval*)malloc(k * sizeof(interval)); // array creation
	int *degCount = (int*)calloc(k, sizeof(int));
	printf("now you will be asked to enter a family of %d intervals:\n",k);
	for (i = 0; i < k; i++)
	{
		printf("enter %dth interval:", i + 1);
		scanf_s("%d %d", &arr[i].left, &arr[i].right);
	}

	printf("your family of intervals are:  \n");
	for (i = 0; i < k; i++)
	{
		printf(" [%d,%d] ", arr[i].left, arr[i].right);
	}
	for (i = 0; i < k; i++) // intialized
	{
		arr[i].color = 0;
		arr[i].neighborsCount = 0;
	}

	quickSort(arr, 0, k - 1); // sorting
	for (i = 0, j = 1; i < k - 1; i++)
	{

		if (arr[i].right > arr[j].left) {
			eCount++;
			degCount[i]++;
			degCount[j]++;
			if (arr[i].neighborsCount == 0)
			{
				arr[i].neighbors = (interval**)malloc(k * sizeof(interval*));
			}
			arr[i].neighbors[arr[i].neighborsCount++] = &arr[j];
			if (arr[j].neighborsCount == 0)
			{
				arr[j].neighbors = (interval**)malloc(sizeof(interval*)*k);
			}
			arr[j].neighbors[arr[j].neighborsCount++] = &arr[i];
			t = ++j;
			while (t < k)
			{
				if (arr[i].right <= arr[t].left) break;
				eCount++;
				degCount[i]++;
				degCount[t]++;
				arr[i].neighbors[arr[i].neighborsCount++] = &arr[t];
				if (arr[t].neighborsCount == 0)
				{
					arr[t].neighbors = (interval*)malloc(k * sizeof(interval));
				}
				arr[t].neighbors[arr[t].neighborsCount++] = &arr[i];
				t++;
			}
		}
		else j++;
	}
	printf("\nG Edges = %d\n", eCount);
	//find max and min
	min = degCount[0];
	for (i = 0; i < k; i++)
	{
		if (max < degCount[i]) max = degCount[i];
		if (min > degCount[i]) min = degCount[i];
	}
	printf("Maximum Degree Of G = %d \n", max);
	printf("Minimum Degree Of G = %d \n", min);
	//returns the Chromatic number
	chromaticNum=chromaticNumber(arr, k);
	printf("Chromtaic Number Of G = %d\n", chromaticNum);
	//prints the G's complement status
	GCedge = ((k*(k - 1)) / 2) - eCount;
	GCmax = k - 1 - min;
	GCmin = k - 1 - max;
	printf("G's Complement Edges = %d\n", GCedge);
	printf("Maximum Degree Of G's complement = %d \n", GCmax);
	printf("Minimum Degree Of G's Complement = %d \n", GCmin);
	printf("Optinal Coloring:");// optinal coloring
	
	colorSorting = (interval**)malloc((chromaticNum + 1) * sizeof(int)); // known chromatic number  
	for (i = 1; i <=chromaticNum ; i++)//running from color no'1 (excluding zero)
	{
		t = 0;  //iterator for inserting intervals in each color 
		colorSorting[i] = (interval*)malloc(k * sizeof(interval));// max of vertices in one color is k
		for (j = 0; j < k; j++)
		{
			if (arr[j].color == i)// i=number of color 
			{
				colorSorting[i][t++] = arr[j]; // inserting to the Colorsorting array 
			}
		}
		printf(" {");
		for (p = 0;p  < t; p++) // printing the colorSorting [i] array 
		{
			if (p == t - 1)
			{
				printf("[%d,%d]", colorSorting[i][p].left, colorSorting[i][p].right); // if last interval in the specific color 
			}
			else
				printf("[%d,%d],", colorSorting[i][p].left, colorSorting[i][p].right);
		}
		if (i == chromaticNum) // if last color then prints
		{
			printf("} = %d\n", i);
		}
		else
			printf("} = %d,", i);
		
	}
	free(colorSorting);
	free(arr);
	free(degCount);
}
void swap(interval* a, interval* b)
{
	interval t = *a;
	*a = *b;
	*b = t;
}
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(interval *arr, int low, int high)
{
	interval pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot 
		if (arr[j].left < pivot.left)
		{
			i++;    // increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low  --> Starting index,
high  --> Ending index */
void quickSort(interval *arr, int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		/* Separately sort elements before 
		 partition and after partition*/ 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


int chromaticNumber(interval * arr, int k)
{
	int i, j, p, minColor, maxNum = 0;
	int * colorArray = (int*)calloc(k + 1, sizeof(int));

	for (i = 0; i < k; i++)
	{
		for (j = 0; j < arr[i].neighborsCount; j++)
		{
			colorArray[arr[i].neighbors[j]->color] = 1;
		}
		minColor = k;
		for (p = 1; p <= k; p++)
		{
			if (colorArray[p] == 0) {
				minColor = p;
				break;
			}
		}
		arr[i].color = minColor;

		for (j = 0; j < arr[i].neighborsCount; j++)
		{
			colorArray[arr[i].neighbors[j]->color] = 0;
		}
	}

	free(colorArray);

	for (i = 0; i < k; i++) {
		if (maxNum < arr[i].color) maxNum = arr[i].color;
	}
	return maxNum; // returns chromatic number
}

