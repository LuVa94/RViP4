// rvip4.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <stdio.h> 
#include <stdlib.h> 
#include "mpi.h"

//using namespace std;
int main(int argc, char* argv[])
{
	 //7. ���������� ����� �� ������������ ��������� ������� �������  �������.

	int procs_rank, procs_count;
	int i, j, n = 5, local_n;
	double *local_a, *b, *local_c, *a, *c, *d;
	// ������������� ���������� MPI
	MPI_Init(&argc, &argv);
	// ��������� ���������� ��������� � ���������
	MPI_Comm_size(MPI_COMM_WORLD, &procs_count);
	// ��������� ����� ��������
	MPI_Comm_rank(MPI_COMM_WORLD, &procs_rank);
	local_n = n / procs_count;
	local_a = (double *)malloc((local_n * n) * sizeof(double));
	b = (double *)malloc(n * sizeof(double));
	local_c = (double *)malloc(local_n * sizeof(double));
	c = (double *)malloc(n * sizeof(double));
	a = (double *)malloc((n * n) * sizeof(double));

	d = (double *)malloc(n * sizeof(double));
	
	//�������������� ������� � ������� �������� 
	// � ��������� �� ����� �� ��������� 
	if (procs_rank == 0)
	{
		double t = 0;
		//������� ������� ������������� ��� ���������� ������ �� � ��������� i*n+j 
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				a[i*n + j] = rand() % 10;
				
			}
			
		}
		
		for (int j = 0; j < n; j++)
		{
			for (int i= 0; i < n; i++)
			{
				printf("%f ", a[i*n + j]);
			}
			printf(" \n ");
		}

		
	}
	
	//��������� ������� �� �������������� ������  (�����)
	//������� local_a � ��������� ��������� 
	
	MPI_Scatter(a, n * local_n, MPI_DOUBLE, local_a, n * local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	for (i = 0; i < local_n; i++)
	{
		d[i] = 1;
		for (j = 0; j < n; j++)
		{
			d[i] = d[i] * local_a[i*n + j];
		}
			
	}
	//�������� ����� ��������� � ������� �������� 
	MPI_Gather(d, local_n, MPI_DOUBLE, c, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if (procs_rank == 0)
	{
		double sum = 0;
		printf(" \n ");
		for (i = 0; i < n; i++)
		{
		
			printf("%f ", c[i]);
		sum = sum + c[i];
	}
		printf(" \n ");
		printf("%f ", sum);
	}
	// ���������� ���������� MPI
	MPI_Finalize();
	return 0;
}

