#include <iostream>
#include <fstream>

#define min(x, y) ((x > y) ? x : y)
#define max(x, y) ((x < y) ? x : y)

using namespace std;

//���� ������
float F_t(float v)
{
	if (v > 0) return 1;
	else return 0;
}

int main()
{
	float v = 0; //�������� � ������� ������� ���� � ������ ������
	float V_o = 20; //�������� �������� (���������� � 1/4 �������)
	float dt = 0.25; //��������, �� ������� ���� ���������� ��������
	float T = 0; //����� ����� ������ ������
	float m = 0.2; //����� �������
	float e = 0; //���������������� ����� ������
	float Ie = 0; //������������ ����� ������
	float de = 0; //���������������� ����� ������
	float Kp = 7; //����������� ������������������
	float Ki = 0.1; //����������� ��������������
	float Kd = 30; //����������� �����������������
	float pwm_speed; //�������� ����� ���
	float F_e; //���� ����
	float F; //����, ��������� ��������� �������
	float a; //���������

	ofstream f("data.txt", ios::out);
	printf("i\t\te\t\tIe\t\tde\t\tF_e\t\tF\t\ta\t\tv\n");
	for (int i = 0; i < 100; i++)
	{

		e = V_o - v;

		Ie += e;

		T = i + 1;
		de = e / T;

		pwm_speed = min(max(Kp * e + Ki * Ie + Kd * de, 20), 0);

		F_e = 0.05 * pwm_speed;

		F = F_e - F_t(v);


		a = F / m;
		v += a * dt;

		printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", i, e, Ie, de, F_e, F, a, v);
		//f << i << "\t\t" << e << "\t\t" << F_e << "\t\t" << F << "\t\t" << a << "\t\t" << v << '\n';
		f << i << '\t' << v << '\n';
		//printf("%d\t%f\n", i, v);
		//va = V(v, dt, m, K, va, Kp);
	}



	system("pause");
	return 0;
}