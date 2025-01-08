f = open('SFU\\a5.py','r')
l = f.readlines()
f.close()
a = []
for c,i in enumerate(l):
    if len(i)>=100:
        a.append([f'Line: {c+1}',i.strip(),f'({len(i)} characters)\n'])
if a:
    for i in a:
        for n in i:
            print(n)
        print()
else:
    print('no lines past 100 characters')