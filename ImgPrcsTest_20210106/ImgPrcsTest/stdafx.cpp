
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// ImgPrcsTest.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"


long double fmaxl(long double a,long double b )
{
	return (long double) a>b ? a:b;
}
double fmax(double a,double b )
{
	return (double) a>b ? a:b;
}

double fminl(double a,double b )
{
	return (double) a<b ? a:b;
}

int isnan(double nan)
{
	return nan == NAN;
}
