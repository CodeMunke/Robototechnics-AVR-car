#include <iostream>
#include <fstream>

#define min(x, y) ((x > y) ? x : y)
#define max(x, y) ((x < y) ? x : y)

using namespace std;

//Сила трения
float F_t(float v)
{
	if (v > 0) return 1;
	else return 0;
}

int main()
{
	float v = 0; //Скорость с которой машинка едет в данный момент
	float V_o = 20; //Желаемая скорость (прерывания в 1/4 секунды)
	float dt = 0.25; //Интервал, на котором идет считывание скорости
	float T = 0; //общее время работы машины
	float m = 0.2; //Масса машинки
	float e = 0; //Пропорциональная часть ошибки
	float Ie = 0; //Интегральная часть ошибки
	float de = 0; //Дифференциальная часть ошибки
	float Kp = 7; //Коэффициент пропорциональность
	float Ki = 0.1; //Коэффициент интегрирование
	float Kd = 30; //Коэффициент дифференцирования
	float pwm_speed; //Скорость через ШИМ
	float F_e; //Сила тяги
	float F; //Сила, создающая ускорение машинки
	float a; //Ускорение

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