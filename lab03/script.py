#!/usr/bin/python3.6

def A(k):
    for i in range(1, k + 1):
        print(i, end=' ')
    print()

def IA(m, n):
    for i in range(1, m + 1):
        for j in range(n):
            print(i, end=' ')
    print()

def JA(m, n):
    for i in range(m):
        for j in range(1, n + 1):
            print(j, end=' ')
    print()

def make_full(m, n):
    A(m * n)
    IA(m, n)
    JA(m, n)

def __make_proc(m, n, a, b, prompt=True):
    mm = m // a
    nn = n // b
    if prompt:
        print(mm * nn, m, n)
    make_full(mm, nn)

def make(m, n, proc):
    if proc == '10proc':
        __make_proc(m, n, 2, 5)
    elif proc == '25proc':
        __make_proc(m, n, 2, 2)
    elif proc == '50proc':
        __make_proc(m, n, 1, 2)
    elif proc == 'full':
        __make_proc(m, n, 1, 1)
    elif proc == '5proc':
        __make_proc(m, n, 4, 5)
    elif proc == '1proc':
        __make_proc(m, n, 10, 10)

def make_x1(m, proc):
    if proc == '10proc':
        __make_proc(m, 1, 10, 1)
    elif proc == '25proc':
        __make_proc(m, 1, 4, 1)
    elif proc == '50proc':
        __make_proc(m, 1, 2, 1)
    elif proc == 'full':
        __make_proc(m, 1, 1, 1)
    elif proc == '5proc':
        __make_proc(m, 1, 20, 1)
    elif proc == '1proc':
        __make_proc(m, 1, 100, 1)

import sys

def main():
    for n in (10, 24, 50, 100, 200, 500):
        for proc in ('full', '50proc', '25proc', '10proc', '5proc', '1proc'):
            if (n < 50 and proc == '5proc'):
                break
            if (n > 50 and proc == 'full'):
                continue
            if (n >= 100 and proc == '50proc'):
                continue
            if (n >= 200 and proc in ('25proc', '10proc')):
                continue
            if (n >= 500 and proc == '5proc'):
                continue
            with open("sm/{0}x{0}_{1}".format(n, proc), 'w') as f:
                sys.stdout = f
                make(n, n, proc)
            with open("sm/{}x1_{}".format(n, proc), 'w') as f:
                sys.stdout = f
                make_x1(n, proc)

if __name__ == '__main__':
    main()
