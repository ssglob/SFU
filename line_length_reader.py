f = open('SFU\\a5.py','r')
l = f.readlines()
f.close()
for c,i in enumerate(l):
    if len(i)>=100:
        print(f'Line: {c+1}')
        print(i)
        print(f'({len(i)} characters)\n')