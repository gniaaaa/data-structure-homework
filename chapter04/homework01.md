第一题

约定（与教材一致，串下标从 1 开始）：

- next[1] = 0；
- next[j]（j>=2）= t[1..j-1] 中最长相等前后缀的长度 + 1；
- nextval[1] = 0，且当 t[j] == t[next[j]] 时 nextval[j] = nextval[next[j]]，否则 nextval[j] = next[j]。

## (1) t1 = 'aaab'

| j | 1 | 2 | 3 | 4 |
|:---|:-:|:-:|:-:|:-:|
| t[j] | a | a | a | b |
| next | 0 | 1 | 2 | 3 |
| nextval | 0 | 0 | 0 | 3 |

推导：

- next[1]=0；
- next[2]：前缀串 "a" 无相等前后缀，长度 0，故 0+1=1；
- next[3]：前缀串 "aa" 最长相等前后缀 "a"，长度 1，故 1+1=2；
- next[4]：前缀串 "aaa" 最长相等前后缀 "aa"，长度 2，故 2+1=3。
- nextval：j=2 时 t[2]=a 与 t[next[2]]=t[1]=a 相等，nextval[2]=nextval[1]=0；
  j=3 时 t[3]=a 与 t[next[3]]=t[2]=a 相等，nextval[3]=nextval[2]=0；
  j=4 时 t[4]=b 与 t[next[4]]=t[3]=a 不等，nextval[4]=next[4]=3。

## (2) t2 = 'abcabaa'

| j | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|:---|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| t[j] | a | b | c | a | b | a | a |
| next | 0 | 1 | 1 | 1 | 2 | 3 | 2 |
| nextval | 0 | 1 | 1 | 0 | 1 | 3 | 2 |

推导：

- next[1]=0；
- "a"、"ab"、"abc" 都没有相等前后缀，故 next[2]=next[3]=next[4]=1；
- "abca" 的相等前后缀为 "a"（长度 1），next[5]=1+1=2；
- "abcab" 的相等前后缀为 "ab"（长度 2），next[6]=2+1=3；
- "abcaba" 的相等前后缀为 "a"（长度 1），next[7]=1+1=2。
- nextval：j=2、3 时 t[j] 与 t[next[j]]=t[1]=a 均不等，取 next 原值 1；
  j=4 时 t[4]=a 与 t[next[4]]=t[1]=a 相等，nextval[4]=nextval[1]=0；
  j=5 时 t[5]=b 与 t[next[5]]=t[2]=b 相等，nextval[5]=nextval[2]=1；
  j=6 时 t[6]=a 与 t[next[6]]=t[3]=c 不等，nextval[6]=next[6]=3；
  j=7 时 t[7]=a 与 t[next[7]]=t[2]=b 不等，nextval[7]=next[7]=2。

## (3) t3 = 'adabbadada'

| j | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|:---|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| t[j] | a | d | a | b | b | a | d | a | d | a |
| next | 0 | 1 | 1 | 2 | 1 | 1 | 2 | 3 | 4 | 3 |
| nextval | 0 | 1 | 0 | 2 | 1 | 0 | 1 | 0 | 4 | 0 |

推导要点：

- next[1]=0；
- "a"、"ad" 无相等前后缀，next[2]=next[3]=1；
- "ada" 相等前后缀 "a"，next[4]=2；
- "adab"、"adabb" 无相等前后缀，next[5]=next[6]=1；
- "adabba" 相等前后缀 "a"，next[7]=2；
- "adabbad" 相等前后缀 "ad"，next[8]=3；
- "adabbada" 相等前后缀 "ada"，next[9]=4；
- "adabbadad" 相等前后缀 "ad"（长度 2），next[10]=3。
- nextval：j=2 不等，取 1；
  j=3 相等（t[3]=a 与 t[1]=a），取 nextval[1]=0；
  j=4 不等，取 2；j=5 不等，取 1；
  j=6 相等（t[6]=a 与 t[1]=a），取 nextval[1]=0；
  j=7 相等（t[7]=d 与 t[2]=d），取 nextval[2]=1；
  j=8 相等（t[8]=a 与 t[3]=a），取 nextval[3]=0；
  j=9 不等（t[9]=d 与 t[4]=b），取 next[9]=4；
  j=10 相等（t[10]=a 与 t[3]=a），取 nextval[3]=0。
