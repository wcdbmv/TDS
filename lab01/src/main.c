#include "interface.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	int rc;

	if (argc == 1)
	{
		BigFloat a;
		if ((rc = input_int(&a)) == SUCCESS)
		{
			BigFloat b;
			if ((rc = input_float(&b)) == SUCCESS)
			{
				BigFloat c;
				if ((rc = multiply(&a, &b, &c)) == SUCCESS)
				{
					print_multiply(&c);
					return SUCCESS;
				}
			}
		}
	}
	else
	{
		rc = check_args(argc, argv);
	}

	my_perror(rc);
	return rc;
}
