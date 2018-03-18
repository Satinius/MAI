#include <iostream>
#include <vector>

void knapsack(uint32_t N, uint32_t W, std::vector<uint32_t> &w, std::vector<uint32_t> &c)
{
    // N - кол-во элементов, W - максимальный вес, w - массив весов, c - массив стоимостей
    std::vector<std::vector<std::vector<uint32_t> > > a(N + 1, std::vector<std::vector<uint32_t> >(N + 1, std::vector<uint32_t>(W + 1)));
    /* первый вектор - элементы, предметы левее которых мы берём
     * второй - количество элементов в множестве
     * третий - стоимости
     */
    for(size_t i = 1; i <= N; i++)
    {
        for(size_t j = 1; j <= i; j++)
        {
            for(size_t k = 1; k <= W; k++)
            {
                // если вес обрабатываемого предмета меньше либо равен вместимости
                if( w[i-1] <= k )
                {
                    /* a[i][j][k] максимальное из элемента стоящего сверху для такого же количества элементов в
                     * множестве (т. е. мы не кладем никакой элемент) и элемента a[i-1][j-1][k-w[i-1]] + c[i-1], т.е.
                     * стоимость из предыдущего ряда таблицы для элемента с длиной множества на 1 меньше
                     * и весом k к которой добавили стоимость обрабатываемого предмета
                     */
                    a[i][j][k] = std::max(a[i-1][j][k], a[i-1][j-1][k-w[i-1]] + c[i-1]);
                    if( !a[i-1][j-1][k-w[i-1]] && j != 1 && a[i][j][k] == c[i-1])
                        a[i][j][k] = a[i-1][j][k];
                }
                // если нет, предмет не кладется и итоговая стоимость остаётся такой же как при предыдущей итерации
                else
                    a[i][j][k] = a[i-1][j][k];

            }
        }
    }
    uint32_t total_cost = 0;
    uint32_t res_idx = 0;
    // максимальный элемент лежит где-то в a[N][i][W], где N - кол-во элементов, а [W] - макс. вес
    for(size_t i = 0; i <= N; i++)
        if( a[N][i][W] * i > total_cost ) {
            total_cost = a[N][i][W] * i;
            res_idx = i;
        }
    std::cout << total_cost << std::endl;

    std::vector<uint32_t> ans;
    size_t i = N;
    size_t j = res_idx;
    size_t k = W;
    while (a[i][j][k] != 0) {
        if( a[i][j][k] == a[i-1][j][k] ) {
            i -= 1;
        } else {
            ans.push_back(i);
            k -= w[i - 1];
            i -= 1;
            j -= 1;
        }
    }

    for (auto iterator = ans.rbegin(); iterator != ans.rend(); iterator++) {
        std::cout << *iterator << " ";
    }
}

int main()
{
    uint32_t N, W;
    std::cin >> N >> W;
    std::vector<uint32_t > w(N);
    std::vector<uint32_t> c(N);
    for(size_t i = 0; i < N; i++)
        std::cin >> w[i] >> c[i];
    knapsack(N, W, w, c);
    return 0;
}