#include "info.h"

void usage(FILE *file)
{
	fprintf(file, "Использование: app.exe [--help]\n");
}

void help(void)
{
	usage(stdout);

	puts("\n\
Программа производит умножение длинного целого числа на длинное действительное\n\
число. Вы можете ввести числа в любом удобном для вас формате, с целой частью\n\
или без, с дробной частью или без, с показателем степени или без. При этом длина\n\
мантиссы любого введённого числа не должна превышать 30 цифр, вместе с тем длина\n\
показателя степени не должна превышать 5 цифр. Ограничения на введённое число\n\
считаются в приведённом, нормализированном виде, т. е. незначащие нули, к\n\
примеру, не подсчитываются. В случае переполнения мантиссы при умножении\n\
результат округляется.");

}

void my_perror(int errcode)
{
	if (errcode == SUCCESS)
		return;

	fprintf(stderr, "Ошибка: ");
	switch (errcode)
	{
		case EMPTY_STRING_ERROR:
			fprintf(stdout, "Пустой ввод\n");
			break;
		case INVALID_STRING_ERROR:
			fprintf(stderr, "Неправильный ввод\n");
			break;
		case BUF_OVERFLOW_ERROR:
			fprintf(stderr, "Введено слишком много символов\n");
			break;
		case MANTISSA_OVERFLOW_ERROR:
			fprintf(stderr, "Мантисса введённого числа слишком большая\n");
			break;
		case EXPONENT_OVERFLOW_ERROR:
			fprintf(stderr, "Показатель степени введённого числа больше \
допустимого по абсолютному значению\n");
			break;
		case NOT_INT_ERROR:
			fprintf(stderr, "Введено не целое число\n");
			break;
		case MULTIPLY_OVERFLOW_ERROR:
			fprintf(stderr, "Показатель степени произведения больше \
допустимого по абсолютному значению\n");
			break;
	}
}
