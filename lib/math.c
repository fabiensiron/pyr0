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

double sin(double x)
{
    static const
    double a0 =  1.0,
           a1 = -1.666666666640169148537065260055e-1,
           a2 =  8.333333316490113523036717102793e-3,
           a3 = -1.984126600659171392655484413285e-4,
           a4 =  2.755690114917374804474016589137e-6,
           a5 = -2.502845227292692953118686710787e-8,
           a6 =  1.538730635926417598443354215485e-10;
    double x2 = x * x;
    return x * (a0 + x2 * (a1 + x2 * (a2 + x2
             * (a3 + x2 * (a4 + x2 * (a5 + x2 * a6))))));
}
