r = '    '
n = int(input('Up to what number '))
for i in range(n):
    r += f' {i+1:3}'
r += f'\n{'-'*len(r)}'
for i in range(1,n+1):
    r += '\n'
    r += f'{i:2} |'
    for ii in range(1,n+1):
        r += f' {i*ii:3}'
print(r)