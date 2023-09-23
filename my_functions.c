#include "main.h"
/************************* PRINT CHAR *************************/

/**

  print_char - Prints a char

  @types: List of arguments

  @buffer: Buffer array to handle print

  @flags: Calculates active flags

  @width: Width

  @precision: Precision specificationS

  @size: Size specifier

Return: Number of chars printed / int print_char(va_list types, char buffer[], int flags, int width, int precision, int size) { / Get the char from the argument list */ char c = va_arg(types, int);

/* Call another function to handle the write operation */
return (handle_write_char(c, buffer,
			flags, width,
			precision,
			size));
Copy
}

/************************* PRINT A STRING ***********************/ /

print_string - Prints a string

@types: List of arguments

@buffer: Buffer array to handle print

@flags: Calculates active flags

@width: Width

@precision: Precision specification

@size: Size specifier

Return: Number of chars printed / int print_string(va_list types, char buffer[], int flags, int width, int precision, int size) { / Initialize variables for length and index */ int length = 0; int i;

	/* Get the string from the argument list */
	char *str = va_arg(types,
			char *);

	/* Use a macro to mark unused parameters */
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	/* Handle null pointer case */
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	/* Calculate the length of the string */
	while (str[length] != '\0')
		length++;

	/* Adjust the length according to the precision */
	if (precision >= 0 && precision < length)
		length = precision;

	/* Handle the width case */
	if (width > length)
	{
		/* Check if the minus flag is set */
		if (flags & F_MINUS)
		{
			/* Write the string first */
			write(1,
					&str[0],
					length);

			/* Write spaces until width is reached */
			for (i = width - length; i > 0; i--)
				write(1,
						" ",
						1);

			/* Return the width as the number of chars printed */
			return (width);
		}
		else
		{
			/* Write spaces until width is reached */
			for (i = width - length; i > 0; i--)
				write(1,
						" ",
						1);

			/* Write the string after */
			write(1,
					&str[0],
					length);

			/* Return the width as the number of chars printed */
			return (width);
		}
	}

	/* Write the string and return the length as the number of chars printed */
	return (write(1,
				str,
				length));
	Copy
}

/************************* PRINT PERCENT SIGN ***********************/ /

print_percent - Prints a percent sign

@types: List of arguments

@buffer: Buffer array to handle print

@flags: Calculates active flags

@width: Width

@precision: Precision specification

@size: Size specifier

Return: Number of chars printed / int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size) { / Use a macro to mark unused parameters */ UNUSED(types); UNUSED(buffer); UNUSED(flags); UNUSED(width); UNUSED(precision); UNUSED(size);

	/* Write a percent sign and return 1 as the number of chars printed */
	return (write(1,
				"%%",
				1));
	Copy
}

/************************* PRINT INT ***********************/ /

print_int - Print int

@types: List of arguments

@buffer: Buffer array to handle print

@flags: Calculates active flags

@width: Width

@precision: Precision specification

@size: Size specifier

Return: Number of chars printed / int print_int(va_list types, char buffer[], int flags, int width, int precision, int size) { / Initialize variables for index and sign */ int i = BUFF_SIZE - 2; int is_negative = 0;

	/* Get the int from the argument list */
	long int n = va_arg(types, long int);

	/* Convert the size of the number according to the size specifier */
	n = convert_size_number(n, size);

	/* Handle zero case */
	if (n == 0)
		buffer[i--] = '0';

	/* Mark the end of the buffer with a null character */
	buffer[BUFF_SIZE - 1] = '\0';

	/* Convert the number to an unsigned long int */
	unsigned long int num = (unsigned long int)n;

	/* Handle negative case */
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	/* Convert the number to a string and store it in the buffer */
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	/* Increment the index to point to the first digit */
	i++;

	/* Call another function to handle the write operation */
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
	Copy
}

/************************* PRINT BINARY ***********************/ /

print_binary - Prints an unsigned long int in binary format

@types: List of arguments

@buffer: Buffer array to handle print

@flags: Calculates active flags

@width: Width

@precision: Precision specification

@size: Size specifier

Return: Number of chars printed / int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size) { / Initialize variables for index and count */ int i = BUFF_SIZE - 2; int count = 0;

	/* Get the unsigned long int from the argument list */
	unsigned long int n = va_arg(types, unsigned long int);

	/* Convert the size of the number according to the size specifier */
	n = convert_size_number(n, size);

	/* Handle zero case */
	if (n == 0)
		buffer[i--] = '0';

	/* Mark the end of the buffer with a null character */
	buffer[BUFF_SIZE - 1] = '\0';

	/* Convert the number to binary and store it in the buffer */
	while (n > 0)
	{
		buffer[i--] = (n % 2) + '0';
		n /= 2;
		count++;
	}

	/* Increment the index to point to the first digit */
	i++;

	/* Call another function to handle the write operation */
	return (write_number(0, i, buffer, flags, width, precision, count));
	Copy
}
