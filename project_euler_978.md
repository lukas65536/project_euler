## Skewed Fibonacci Random Walk


$X_0=0, \quad X_1=1\quad$ and $\quad X_t = X_{t-1} \pm |X_{t-2}|$

$$
\mathbb EX^i =m_i,\quad \text{Skew}(X) = \mathbb E\left[\left(\frac{X-m_1}{\sigma}\right)^3\right] $$

$$=\sigma^{-3}\mathbb E \left[X^3 - 3X^2m_1 + 3Xm_1^2 -m_1^3\right]$$

$$=\sigma^{-3}(m_3 - 3m_2m_1 + 3m_1^3 - m_1^3)$$

$$=\sigma^{-3}(m_3 - 3m_2m_1 + 2m_1^3)$$

And $\sigma = \sqrt {\text{Var}(X)} =\sqrt{\mathbb EX^2 - (\mathbb E X)^2} =\sqrt{m_2-m_1^2}$

### Subwalk Lemma

When $X_j=s$ and $X_{j-1}=0$ the distribution is $X_j=sX_1=s$. And for all $k>0$

$$X_{j+k-1}=sX_k$$

### Moment Relation Lemma

Let $\nu\sim\text{Rademacher}$

$m_{i,k} = \mathbb E X_k^i$ where $k$ denotes the length of the random walk and $i$ the moment.

$$m_{1,k+1}=\mathbb E X_{k+1}=\mathbb E[X_k + \nu X_{k-1}] = \mathbb E[X_k] + \mathbb EX_{k-1}\mathbb E\nu=m_{1,k}$$

And for $m_2$
$$m_{2,k+1} = \mathbb EX^2_{k+1} = \mathbb E[X_k^2 + (\nu X_{k-1})^2+2\nu X_kX_{k-1}]$$
$$=m_{2,k} + \mathbb EX_{k-1}^2 =m_{2,k} + m_{2,k-1}$$

Lastly

$$m_{3,k+1} = \mathbb EX^3_{k+1} = \mathbb E[X_k^3 + 3X_k^2\nu X_{k-1} + 3X_k\nu^2 X_{k-1}^2+\nu^3 X_{k-1}^3]$$
$$=m_{3,k} + 3\mathbb EX_kX_{k-1}^2$$

Wait, not so fast!

$$\mathbb EX_kX_{k-1}^2 = \mathbb E[(X_{k-1} + \nu X_{k-2})X_{k-1}^2] = \mathbb EX_{k-1}^3 + \mathbb E\nu X_{k-2}X_{k-1}^2$$
$$=m_{3,k-1}$$

Thus $ m_{3,k+1} = m_{3,k} + 3m_{3,k-1}$

The solution follows from recursivly calculating the moments and substituting them into $\text{Skew}(X_{50})$!
