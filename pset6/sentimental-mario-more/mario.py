height = 0
while True:
  try:
    height = int(input('Height: '))
  except ValueError:
    continue
  if 1 <= height <= 8:
    break
for c in range(1, height + 1):
  for _ in range(height - c):
    print(' ', end='')
  for _ in range(c):
    print('#', end='')
  print('  ', end='')
  for _ in range(c):
    print('#', end='')
  print()
