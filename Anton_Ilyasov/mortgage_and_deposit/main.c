#include <stdio.h>
int main(void)
{
	int m, i, ost;
	double sum, p = 50000., g, kv_price=10000000., perv_platezh=1000000., vsego, arenda=20000.;
	m = 240; //мес€цев
	printf("god\tna balanse\n");
	for (sum = 1000000., i = 1; i <= m; i++) //с 1-го мес€ц по 240 мес€ц
	{
		sum = sum + sum * 8. / 1200. + (p-arenda); //денег на балансе в конце каждого мес€ца
		kv_price = kv_price * 1.00625; //ежемес€чный рост цены квартиры
		arenda *= 1.00625; //ежемес€чный рост арендной платы
		g = i / 12.;
		ost = i % 12; //остаток от делени€ i на 12
		if (ost == 0)
		{
			p*= 1.075; //рост зарплаты раз в год
			printf("%.0f\t%.2f\n", g, sum); //вывод суммы в конце каждого года
		}
	}
	printf("kv_price: %.2f\n", kv_price);
	printf("\nCredit:\n");
	double k, kn, pl;
	kn = (1. + 14. / 1200.);
	for (k = kn, i = 2; i <= m; i++)
		k *= kn; //коэффициент
	pl = 9000000. * (14. / 1200. + (14. / 1200.) / (k - 1)); //ежемес€чный платеж
	vsego = m * pl; //всего заплатит
	printf("Ezhemesyachniy platezh: %.2f\tVsego: %.2f\n", pl,vsego);
	printf("pribil': %.2f\n", kv_price-vsego);

	return 0;
}
