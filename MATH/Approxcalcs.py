import math
def replace(string,skip,replace):
    a = string.split(skip)
    r = replace.split('.')
    result = ''
    for cc,i in enumerate(a):
        replacement = ''.join([ii + i if c < len(r)-1 else ii for c,ii in enumerate(r)])
        if cc < len(a)-1:
            result += replacement + skip
        else:
            result += replacement
    return result
def add(dx,n):
    dxx = dx.split('i')
    r = ""
    for i in range(n):
        r += ''.join([ii + str(i) if c < len(dxx)-1 else ii for c,ii in enumerate(dxx)])
        if i < n-1:
            r += '+'
    return r
def removew(string,replace,replacew):
    return ''.join([i if i != replace else replacew for i in string])
def simp(string):
    s = ''
    c = 0
    for i in string:
        if i == 'a':
            if c == 0 or c == string.count('a')-1:
                s += ''
            elif c%2!=0:
                s += '4'
            else:
                s += '2'
            c += 1
        else:
            s += i
    return s
aa = add('ib/6',7)
aa = replace(aa,'+','2sqrt(1+cos(.)^2)')
aa = removew(aa,'b','pi')
print(aa)