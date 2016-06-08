int	toupper(int c)
{
  if ((unsigned int)c > 255)
    return (c);
  else if (c >= 'A' && c <= 'Z')
    return (c + 'a' - 'A');
  return (c);
}
