#include "../libftprintf/includes/libft.h"
#include <stdarg.h>

char *strnjoin(int n, ...)
{
	char	*joined;
	va_list	ap;
	int		len;
	int		i;

	va_start(ap, n);
	i = 0;
	len = 0;
	while (i++ < n)
	{
		len += ft_strlen(va_arg(ap, const char *));
	}
	va_end(ap);
	joined = ft_strnew(len);
	va_start(ap, n);
	i = 0;
	while(i++ < n)
	{
		ft_strcat(joined, va_arg(ap, char *));
	}
	va_end(ap);
	return (joined);
}
