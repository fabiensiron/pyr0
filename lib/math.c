double		pow(double x, double y)
{
    double	r = x;

    if (y <= 0)
        return (1.0);
    if (y == 1)
        return (x);

    while (y > 1)
    {
        r *= x;
        y--;
    }

    return (r);
}


double	fabs(double x)
{
    return (x < 0 ? -x : x);
}
