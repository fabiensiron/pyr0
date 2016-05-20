def credits():
  print('Thanks to Tinypy for the base interpreter, BSDs and Apple for the library, ')
  print('and stos project for the build system.')
  print('All the remaining code was made by Fabien Siron (me).')
  print('If you want to contact me, please send me an email: fabien.siron@epita.fr')

def help(class_ = None):
  if (class_ == None):
    l = ['py2bc', 'BUILTINS', '__main__']
    print('Modules available:')
    for elt in MODULES:
      if elt not in l:
        print('  ', elt)
  else:
    print(class_.__doc__)

def contribute():
  print('If you want to contribute, its fairly simple: you have to send patch with')
  print('Github pull request feature at https://github.com/Saruta/pyr0.')

def why():
  print('Why pyr0?')
  print('> why not :-)')

